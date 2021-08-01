/*
 * Archivo:   lab_03.c
 * Autor: Jonathan Pu c.19249
 * Descripcion de hardware: 2 PIC, uart, 2 pot y contador con leds
 * Descripcion de software: lector de voltaje en pots, incrementar contador con 
 * USART y comunicacion SPI entre master y slave
 * Creado: 29 de julio de 2021
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h> //para que funcione el sprintf
#include <stdlib.h>
#include <string.h>
#include <pic16f887.h> 
#define _XTAL_FREQ 4000000

#include "config_USART.h" //libreria para configurar USART
#include "SPI.h" //libreria para controlar LCD

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
uint8_t voltaje_a, voltaje_b;
uint8_t centenas, decenas, unidades, residuo;
uint8_t c1, d1, u1;
char s1[10];
char s2[10];
char s3[10];

/*==============================================================================
                        INTERRUPCIONES Y PROTOTIPOS
 =============================================================================*/

void setup(void);
void mensaje1(void);
void mensaje2(void);
void putch(char dato);
void division(char dividendo);
void defensa(void);
void defensa1(void);
void defensa2(void);

/*==============================================================================
                             LOOP PRINCIPAL
 =============================================================================*/

void main(void){
    setup();
    
    while(1){
        PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(0x0A);
       voltaje_a = spiRead();
       __delay_ms(1);
       
       spiWrite(0x0A);
       voltaje_b = spiRead();
       __delay_ms(1);
       
       PORTCbits.RC2 = 1;       //Slave Deselect 
       
       __delay_ms(50);
       division(voltaje_a);
       mensaje1();
       __delay_ms(50);
       division(voltaje_b);
       mensaje2();
       __delay_ms(50);
       
       printf("Por favor ingrese la centena, si es <100 colocar 0\r");
       while(RCIF == 0); //esta secuencia va a recibir tres valores seguidos
       c1 = RCREG -48; //sin desplegar nada en ninguna parte 
       
       while(RCREG > '2'){ 
           defensa();
       }
       
       printf("Por favor ingrese la decena\r");
       while(RCIF == 0); //al restar -48 lo recibimos como decimal
       d1 = RCREG -48; //tenemos tres variables que nos serviran para armar
       
       if(c1 == 2){
           while(RCREG > '5'){
               defensa1();
           }
       }
       
       printf("Por favor ingrese la unidad\r");
       while(RCIF == 0); //el numero completo
       u1 = RCREG -48;
       
       if(c1 == 2 && d1 == 5){
           while(RCREG > '5'){
               defensa2();
           }
       }
       
       sprintf(s1, "%d", c1); //con esto lo convertimos primero a decimal 
       sprintf(s2, "%d", d1); //y lo almacenamos como strings en los buffer
       sprintf(s3, "%d", u1);
       strcat(s1, s2); //concatenamos s2 con s1, ahora estan en s1
       strcat(s1, s3); //concatenamos s3 con s1 = (s1+s2)
       int completo = atoi(s1); //ahora lo pasamos a un entero
       division(completo); //y lo dividimos para verificar su valor en el UART
       __delay_ms(100);
       TXREG = centenas;
       __delay_ms(100);
       TXREG = decenas;
       __delay_ms(100);
       TXREG = unidades;
       __delay_ms(100);
       PORTD = completo; //ahora lo despliega ya con su correspondiente en bin.
       
}
    return;
}
/*==============================================================================
                             FUNCIONES
 =============================================================================*/
void putch(char dato){      //para la transmision
    while(TXIF == 0);
    TXREG = dato; //transmite los datos al recibir un printf en alguna  parte 
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

void mensaje1(void){
    printf("\rVoltaje1: ");
    __delay_ms(50);
    TXREG = centenas;
    __delay_ms(50);
    printf(".");
    __delay_ms(50);
    TXREG = decenas;
    __delay_ms(50);
    TXREG = unidades;
    __delay_ms(50);
    printf("\r\r");
    
    return;
}

void mensaje2(void){
    printf("\rVoltaje2: ");
    __delay_ms(50);
    TXREG = centenas;
    __delay_ms(50);
    printf(".");
    __delay_ms(50);
    TXREG = decenas;
    __delay_ms(50);
    TXREG = unidades;
    __delay_ms(50);
    printf("\r\r");
    
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
    //configurar pines de salida de contador
    TRISD = 0x00;
    TRISB = 0x00;
    //oscilador interno
    OSCCONbits.IRCF0 = 0;        //reloj interno de 4mhz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.SCS = 1;  //internal oscillator is used for system clock
    
    //configuracion de SPI master
    //TRISCbits.TRISC5 = 0; //SDO 
    //TRISCbits.TRISC3 = 0; //SCK master debe ser configurado como salida
    TRISCbits.TRISC2 = 0; //Pin para seleccionar
    
    //SPI MASTER
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW,
            SPI_IDLE_2_ACTIVE);
    //configurar uart con la libreria
    config_USART();    
    
    //limpiar puertos
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    
    return;
}