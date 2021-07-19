/*
 * Archivo:   carreras_00.c
 * Autor: Jonathan Pu c.19249
 * Descripcion de hardware: leds, 2 7 segmentos, botones , potenciometro
 * Descripcion de software: contador de 8 bits y 2 7 segmentos para mostrar
 * el valor de referencia cambiando por un potenciometro en ADC
 * Creado: 16 de julio de 2021
 */

#include <xc.h>
#include <stdint.h>
#include <pic16f887.h> 
#define _XTAL_FREQ 4000000

#include "config_ADC.h" //ya puedo usar mis funciones
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
char tabla_7seg [16] = {0b00111111, 0b00000110, 0b01011011, 
                       0b01001111, 0b01100110, 0b01101101,
                       0b01111101, 0b00000111, 0b01111111,
                       0b01101111, 0b01110111, 0b01111100,
                       0b00111001, 0b01011110, 0b01111001, 0b01110001};

char pot1;
/*==============================================================================
                               INTERRUPCIONES Y PROTOTIPOS
 =============================================================================*/
void setup(void);
char swap(char variable);

void __interrupt() isr(void){
    //interrupcion del puerto B
    if (RBIF){
        if(RB0 == 0){
            PORTC++;
            RBIF = 0;
        }
        if(RB1 == 0){
            PORTC--;
            RBIF = 0;
        }
    }
    //interrupcion ADC
    if(ADC){
        if(ADCON0bits.CHS == 0){ //para que sea el pin A0 donde esta el pot
            pot1 = ADRESH; //tomo los 8 msb y los paso a una variable
        }
    }
}

/*==============================================================================
                                LOOP PRINCIPAL
 =============================================================================*/
void main(void){
    setup();
    while(1){
        
    }   
}
/*==============================================================================
                                    FUNCIONES
 =============================================================================*/

void multiplexado(void){
 
    PORTE = 0x00; //Para limpiar el puerto de transistores
    transistores = 0b00000000; //para que se vaya al disp1
    if (transistores == 0b00000000){
        display1();
    }
    if (transistores == 0b00000001){ //para que se vaya al disp2
        display2();
    }
    return;
}

char swap(char variable){
    return ((variable & 0x0F)<<4 | (variable & 0xF0)>>4);
} /*la primera expresion nos da los ultimos cuatro bits de la variable
   * con el operador "<<" hacemos cuatro corrimientos a la izquierda, la otra 
   * expresion nos da los primeros cuatro bits, y los corremos a la derecha
   * por ultimo se hace un OR de bits para hacer el swap*/

/*==============================================================================
                            CONFIGURACION DE PIC
 =============================================================================*/
void setup(void){
    //entradas de botones
    TRISB0 = 1;
    TRISB1 = 1;
    ANSELH = 0;
    //entrada de potenciometro
    ANSELbits.ANS0 = 1;
    TRISA0 = 1;
    //salida de leds
    TRISB7 = 0;
    TRISC = 0x00;
    TRISD = 0x00;
    
    //limpiar puertos
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    
    //Configuracion de internal pull-ups para los botones
    OPTION_REGbits.nRBPU = 0; //internal pull-ups are enabled
    WPUBbits.WPUB = 0b00000011;
    
    //Configurar reloj interno
    OSCCONbits.IRCF0 = 0;        //reloj interno de 4mhz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.SCS = 1;  //internal oscillator is used for system clock
    
     //configurar interrupciones
    PIE1bits.ADIE = 1;      //enable de la int del ADC
    PIR1bits.ADIF = 0;      //limpiar la interrupcion del ADC
    INTCONbits.GIE = 1;     //habilita las interrupciones globales
    INTCONbits.PEIE = 1;    //periferical interrupts

    
    //Configuracion de interrupcion del puerto B
    IOCBbits.IOCB0 = 1;     //Boton de escritura
    IOCBbits.IOCB1 = 1;     //Boton de lectura
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;    //limpiar bandera de interrupcion
    
     //configurar el modulo ADC
    config_ADC(1);
    return;
}


