/*
 * Archivo:   main_05.c
 * Autor: Jonathan Pu c.19249
 * Descripcion de hardware: botones y leds para contador, FTDI
 * Descripcion de software: contador con botones enviados a PC por medio de UART
 * y comunicacion con Adafruit IO
 * Creado: 15 de agosto de 2021
 */


#include <xc.h>
#include <pic16f887.h> 
#define _XTAL_FREQ 4000000
#include <stdint.h>
#include <stdlib.h>

#include <string.h>
#include <stdio.h> //para que funcione el sprintf
#include "config_USART_1.h" //libreria para configurar USART

/*=============================================================================
                        BITS DE CONFIGURACION
 =============================================================================*/
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO 
//oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/
//CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and 
//can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR 
//pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code 
//protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code 
//protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal
///External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit 
//(Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit 
//(RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit 
//(Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits 
//(Write protection off)

/*==============================================================================
                               VARIABLES
 =============================================================================*/
uint8_t contador, centenas, decenas, unidades, residuo, dividendo;
uint8_t c1, d1, u1;
char s1[10];
char s2[10];
char s3[10];

/*==============================================================================
                              PROTOTIPOS
 =============================================================================*/
void setup(void);
void putch(char data);
void division(char dividendo);
void defensa(void);
void defensa1(void);
void defensa2(void);


/*==============================================================================
                              INTERRUPCIONES
 =============================================================================*/
void __interrupt() isr(void){
    if (RBIF == 1){
        if (RB0 == 0){
            contador++;
            
            
        }
        if (RB1 == 0){
            contador--;
            
        }
        RBIF = 0;
    }
}


/*==============================================================================
                             LOOP PRINCIPAL
 =============================================================================*/

void main(void){
    setup();
    
    while(1){
        //PORTA = contador;
        if(RCREG == 'b'){
        division(contador);
//        printf("\rContador: ");
        TXREG = centenas;
        __delay_ms(50);
        TXREG = decenas;
        __delay_ms(50);
        TXREG = unidades;
        }
      
       while(RCIF == 0); //esta secuencia va a recibir tres valores seguidos
       c1 = RCREG -48; //sin desplegar nada en ninguna parte
        while(RCIF == 0); 
       d1 = RCREG -48; //tenemos tres variables que nos serviran para armar
        while(RCIF == 0); 
       u1 = RCREG -48;
       
       
       sprintf(s1, "%d", c1); //con esto lo convertimos primero a decimal 
       sprintf(s2, "%d", d1); //y lo almacenamos como strings en los buffer
       sprintf(s3, "%d", u1);
       strcat(s1, s2); //concatenamos s2 con s1, ahora estan en s1
       strcat(s1, s3); //concatenamos s3 con s1 = (s1+s2)
       int completo = atoi(s1); //ahora lo pasamos a un entero
       PORTD = completo; 

        
    }
}

/*==============================================================================
                             FUNCIONES
 =============================================================================*/

void putch(char data){
    while(TXIF == 0);
    TXREG = data; //transmite los datos al recibir un printf en alguna  parte 
    return;
}

void division (char dividendo){
    
    centenas = (dividendo)/100;//esto me divide entre 100 y se queda con el entero
    residuo = dividendo%100; //el residuo de lo que estoy operando
    decenas = residuo/10; 
    unidades = residuo%10; //se queda con las unidades de las decenas
    //las variables estan en todo el codigo entonces no necesito el return
    centenas += 48;
    decenas += 48;
    unidades += 48;
    return;
} 

void defensa(void){
    if(RCREG > 2){
           printf("Introduzca un valor valido de 0 a 2\r");   
       }
       while(RCIF == 0);
       c1 = RCREG -48;
}

void defensa1(void){
    if(RCREG > 5){
           printf("Introduzca un valor menor o igual a 5\r");   
       }
       while(RCIF == 0);
       d1 = RCREG -48;
}

void defensa2(void){
    if(RCREG > 5){
           printf("Introduzca un valor menor o igual a 5\r");   
       }
       while(RCIF == 0);
       u1 = RCREG -48;
}


/*==============================================================================
                         CONFIGURACION DEL PIC
 =============================================================================*/
void setup(void){
    TRISA = 0X00;
    ANSEL = 0X00;
    ANSELH = 0X00;
    TRISB = 0b00000011;
    
    TRISD = 0x00;
    
    PORTA = 0X00;
    PORTB = 0X00;
    PORTC = 0X00;
    PORTD = 0x00;
    
    //oscilador interno
    OSCCONbits.IRCF0 = 0;        //reloj interno de 4mhz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.SCS = 1;  //internal oscillator is used for system clock
    
     //configuracion de internal pullups y iocb
    OPTION_REGbits.nRBPU = 0; //internal pull-ups are enabled
    WPUB = 0b00000011;
    IOCBbits.IOCB0 = 1;     //Boton de inc
    IOCBbits.IOCB1 = 1;     //Boton de dec
    
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;    //limpiar bandera de interrupcion
    INTCONbits.GIE = 1;     //habilita las interrupciones globales
    INTCONbits.PEIE = 1;    //periferical interrupts
    
    
    config_USART();
    
    return;
}

