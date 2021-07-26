/*
 * Archivo:   lab_02.c
 * Autor: Jonathan Pu c.19249
 * Descripcion de hardware: LCD, 2 pot, una terminal virtual
 * Descripcion de software: lector de voltaje en pots, incrementar contador con 
 * USART y desplegar todo en LCD
 * Creado: 23 de julio de 2021
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h> //para que funcione el sprintf
#include <stdlib.h>
#include <pic16f887.h> 
#define _XTAL_FREQ 4000000

#define RS RE0
#define EN RE2
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include "config_ADC.h" //libreria para configurar ADC
#include "config_USART.h" //libreria para configurar USART
#include "LCD_8b.h" //libreria para controlar LCD

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

char voltaje1, voltaje2;
char voltaje_b, voltaje_c;
char dividendo, centenas, residuo, decenas, unidades;
//char buffer[20];
//char dato;

/*==============================================================================
                        INTERRUPCIONES Y PROTOTIPOS
 =============================================================================*/
void setup(void);
char division (char dividendo);
char voltajes (char voltajes_1);

void __interrupt() isr(void){
    //interrupcion del ADC para los dos pot
    if (ADIF){
        if(ADCON0bits.CHS == 0){
            ADCON0bits.CHS = 1;
            voltaje1 = ADRESH;
        }
        else if(ADCON0bits.CHS == 1){
            ADCON0bits.CHS = 0;
            voltaje2 = ADRESH; 
        }
    }
    ADIF = 0;
}

/*==============================================================================
                             LOOP PRINCIPAL
 =============================================================================*/


/*==============================================================================
                             FUNCIONES
 =============================================================================*/
void main(void){
    setup();
    //char a;
    Lcd_Init(); //aqui la LCD aun esta apagada
    Lcd_Clear(); //limpio lo que tenga la LCD siempre llamandolo de la lib
    char buffer[20]; //esta variable almacenara mi voltaje en un string
    char dato; //el dato que deseo almacenar en un str
    
    while(1){   
    dato = voltaje1; //obtengo el valor del ADRESH en la int
    sprintf(buffer, "%d", voltaje1); //aqui obtengo el valor en decimal
           
    Lcd_Set_Cursor(1,1); //ir a la primera linea en la posicion 1
    Lcd_Write_String("S_1:  S_2:  S_3:"); //imprimir los indicadores de voltaje
    Lcd_Set_Cursor(2,1); //ahora ir a la segunda linea
    Lcd_Write_Char(buffer); //mostrar lo que esta en mi string anterior
    __delay_ms(2000); //un delay para asegurar que la busy flag permita recibir
         
    if (ADCON0bits.GO == 0){ //se apaga automaticamente entonces hay que
            __delay_us(100);     //volver a encenderlo
            ADCON0bits.GO = 1;
        }
    }
        
    return;
}

char division (char dividendo){
    centenas = dividendo/100;//esto me divide entre 100 y se queda con el entero
    residuo = dividendo%100; //el residuo de lo que estoy operando
    decenas = residuo/10; 
    unidades = residuo%10; //se queda con las unidades de las decenas
    //las variables estan en todo el codigo entonces no necesito el return
    return dividendo;
} 

char voltajes(char voltaje_1){
    char voltaje_a;
    return voltaje_a = division(voltaje_1);
}

/*==============================================================================
                         CONFIGURACION DEL PIC
 =============================================================================*/
void setup(void){
    //configuracion de pines para potenciometros
    ANSEL = 0b00000011;
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    
    //salidas digitales para controlar LCD
    TRISD = 0x00;
    TRISE = 0x00;
    
    
    //Configurar reloj interno
    OSCCONbits.IRCF0 = 0;        //reloj interno de 4mhz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.SCS = 1;  //internal oscillator is used for system clock
    
    //configuracion de interrupciones
    PIE1bits.ADIE = 1;      //enable de la int del ADC
    PIR1bits.ADIF = 0;      //limpiar la interrupcion del ADC
    INTCONbits.GIE = 1;     //habilita las interrupciones globales
    INTCONbits.PEIE = 1;    //periferical interrupts
    
    //limpiar puertos
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    
    //configuracion de USART
    config_USART();
    //configuracion de ADC
    config_ADC(1);
    return;
}
