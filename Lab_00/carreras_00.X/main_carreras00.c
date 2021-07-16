/*
 * Archivo:   carreras_00.c
 * Autor: Jonathan Pu c.19249
 * Descripcion de hardware: leds, 7 segmentos, botones 
 * Descripcion de software: contador de decadas para carreras de botones
 * que comienza una secuencia de semaforo
 * Creado: 12 de julio de 2021
 */

#include <xc.h>
#include <stdint.h>
#include <pic16f887.h> 
#define _XTAL_FREQ 125000
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
char tabla_7seg [4] = {0b00111111, 0b00000110, 0b01011011, 
                       0b01001111};
char avanzar = 0;
/*==============================================================================
                               INTERRUPCIONES Y PROTOTIPOS
 =============================================================================*/
void setup(void);

void __interrupt() isr(void){
    //if(RBIF){
        //if(RB0 == 0){
            //avanzar = 1;
            //RBIF = 0;
        //}
    //}
}
/*==============================================================================
                                LOOP PRINCIPAL
 =============================================================================*/

void main(void){
    setup();
    
    while(1){  
         
        if(avanzar == 1){
            RB5 = 1;
            PORTA = tabla_7seg[3];
            __delay_ms(1000);
            PORTA = tabla_7seg[2];
            __delay_ms(1000);
            RB5 = 0;
            RB6 = 1;
            PORTA = tabla_7seg[1];
            __delay_ms(1000);
            RB6 = 0;
            RB7 = 1;         
            PORTA = tabla_7seg[0];
            avanzar = 0;
        }
    }
}


/*==============================================================================
                                    FUNCIONES
 =============================================================================*/

//void inicio(void){
    
//}

/*==============================================================================
                            CONFIGURACION DE PIC
 =============================================================================*/

void setup(void){
    //pines para entradas
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    //pines para salidas
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA6 = 0;
    TRISAbits.TRISA7 = 0;
    
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    
    TRISC = 0X00;
    TRISD = 0X00;
    
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    
    ANSELH = 0x00;
    ANSEL = 0x00;
    //configurar el oscilador interno  
    OSCCONbits.IRCF0 = 0;        //reloj interno de 125khz
    OSCCONbits.IRCF1 = 0;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.SCS = 1;   
    
    //configurar el timer0
    OPTION_REGbits.T0CS = 0;     //oscilador interno
    OPTION_REGbits.PSA = 0;      //prescaler asignado al timer0
    OPTION_REGbits.PS0 = 1;      //prescaler tenga un valor 1:256
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS2 = 1;
    TMR0 = 133;
    
    //configurar interrupciones
    IOCBbits.IOCB0 = 1;      //interrupciones para los botones en el portb
    IOCBbits.IOCB1 = 1;
    INTCONbits.RBIF = 0;    //limpia bit de int del puertoB
    INTCONbits.GIE = 1;     //habilita las interrupciones globales
    INTCONbits.RBIE = 1;    //habilita la interuupcion del puertoB
    INTCONbits.T0IE = 1;    //habilita la interrupcion del timer0
    INTCONbits.T0IF = 0;    //limpia bit de int del timer 0
    
     //Configuracion de internal pull-ups para los botones
    OPTION_REGbits.nRBPU = 0; //internal pull-ups are enabled
    WPUBbits.WPUB0 = 1;   //boton1
    WPUBbits.WPUB1 = 1;   //boton2
    WPUBbits.WPUB2 = 1;   //boton3
    WPUBbits.WPUB3 = 0;   //
    WPUBbits.WPUB4 = 0;   //
    WPUBbits.WPUB7 = 0;   //para que no se encienda el rb7  
    
    
    //limpiar puertos
    PORTA = 0X00;
    PORTB = 0X00;
    PORTC = 0X00;
    PORTD = 0X00;
    PORTE = 0X00;
    
    return;
}