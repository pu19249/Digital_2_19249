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
#include "tabla.h"
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


char pot1, pot2, pot3;
char contador;
char transistores = 0;
/*==============================================================================
                               INTERRUPCIONES Y PROTOTIPOS
 =============================================================================*/
void setup(void);
char swap(char variable);
void multiplexado(void);
void display1(void);
void display2(void);

void __interrupt() isr(void){
    //interrupcion del puerto B
    if (RBIF){
        if(RB0 == 0){
            PORTC++;
            
        }
        if(RB1 == 0){
            PORTC--;
            
        }
            RBIF = 0; //apagar la bandera fuera de la int para asegurar que baje
    }
    //interrupcion ADC
    if(ADIF){
        if(ADCON0bits.CHS == 0){ //para que sea el pin A0 donde esta el pot
            pot1 = ADRESH; //tomo los 8 msb y los paso a una variable
            
        }
        ADIF = 0;           //apaga la bandera
        //__delay_us(100); //no delay en las int
    }
    //interrupcion del TMR0
    if(T0IF){
        //aqui debo llamar al multiplexado o inc una variable como bandera
        T0IF = 0;
        TMR0 = 56;
        
        RE0 = 0;
        RE2 = 0;
        if (transistores == 0){
            PORTD = 0x00;
            RE2 = 0;
            RE1 = 1;
            PORTD = traducir(pot2);
            transistores = 1;
           
        } else{
            PORTD = 0x00;
            RE2 = 1;
            //RE1 = 0;
            PORTD = traducir(pot3);
            transistores = 0;
            
            
        }
        
        
        INTCONbits.T0IF = 0;
    }
}

/*==============================================================================
                                LOOP PRINCIPAL
 =============================================================================*/
void main(void){
    setup();
    while(1){
        pot2 = pot1 & 0b00001111;
        pot3 = swap(pot1) & 0b00001111;
        if (ADCON0bits.GO == 0){ //se apaga automaticamente entonces hay que
            __delay_us(100);     //volver a encenderlo
            ADCON0bits.GO = 1;
        }
        if(pot1 > PORTC) {
            PORTBbits.RB7 = 1;}
        else {
            RB7 = 0;
        }
    }   
}
/*==============================================================================
                                    FUNCIONES
 =============================================================================*/
//
//void multiplexado(void){
// 
//    //PORTE = 0x00; //Para limpiar el puerto de transistores
//    transistores = 0b00000000; //para que se vaya al disp1
//    if (transistores == 0b00000000){
//        display1();
//    }
//    else { //para que se vaya al disp2
//       display2();
//    }
//    return;
//}
//
//void display1(void){
//    PORTEbits.RE0 = 1; //apagar y encender los bits correspondientes
//    PORTEbits.RE1 = 0;
//    //PORTD = 0x00;  //para inicializar el puertoa
//    //PORTD = tabla_7seg[pot1]; //traducir las centenas llamando la pos del
//    transistores = 0b00000001; //array, ahi cambia de transistor para el disp2
//    return;
//}
//
//void display2(void){
//    PORTEbits.RE0 = 0;
//    PORTEbits.RE1 = 1;
//    //pot2 = swap(pot1);
//    //PORTD = tabla_7seg[pot2];
//    transistores = 0b00000000;
//    return;
//}

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
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE1 = 0;
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
    
    //configuramos el TMR0 para hacer el encendido y apagado rapido de los 7seg
    OPTION_REGbits.T0CS = 0;     //oscilador interno
    OPTION_REGbits.PSA = 0;      //prescaler asignado al timer0
    OPTION_REGbits.PS0 = 1;      //prescaler tenga un valor 1:256
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS2 = 1;
    TMR0 = 56;
    
     //configurar interrupciones
    PIE1bits.ADIE = 1;      //enable de la int del ADC
    PIR1bits.ADIF = 0;      //limpiar la interrupcion del ADC
    INTCONbits.GIE = 1;     //habilita las interrupciones globales
    INTCONbits.PEIE = 1;    //periferical interrupts
    //interrupcion del timer0
    INTCONbits.T0IE = 1;    //habilita la interrupcion del timer0
    INTCONbits.T0IF = 0;    //limpia bit de int del timer 0
    //Configuracion de interrupcion del puerto B
    IOCBbits.IOCB0 = 1;     //Boton de escritura
    IOCBbits.IOCB1 = 1;     //Boton de lectura
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;    //limpiar bandera de interrupcion
    
     //configurar el modulo ADC
    config_ADC(1);
    transistores = 0;
    
    
    return;
}


