/* 
 * Archivo:   main03.c
 * Autor: Jonathan Pu c.19249
 * Descripcion de hardware: un uC maestro, dos esclavos y un dispositivo i2C,
 * pantalla LCD, leds y actuadores analogicos
 * Descripcion de software: este archivo corresponde al slave2 que tiene un cont
 * Creado: 05 de agosto de 2021
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h> //libreria para mandar str en comunicacion serial
#include <pic16f887.h> 

#include "I2C.h"
#define _XTAL_FREQ 4000000
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
uint8_t contador, z;
/*==============================================================================
                               INTERRUPCIONES Y PROTOTIPOS
 =============================================================================*/
void setup(void);

void __interrupt() isr(void){
    if (RBIF == 1){
        if (RB0 == 0){
            PORTD++;
            
            
        }
        if (RB1 == 0){
            PORTD--;
            
        }
        RBIF = 0;
    }
    /////////////////////////////////
    if(PIR1bits.SSPIF == 1){ 

        SSPCONbits.CKP = 0;
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7);
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupci??n recepci??n/transmisi??n SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepci??n se complete
            contador = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepci??n
            __delay_us(250);
            //z = SSPBUF;
            
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            SSPBUF = contador;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);           
        }
       
        PIR1bits.SSPIF = 0;  
    }
    
}
/*==============================================================================
                                LOOP PRINCIPAL
 =============================================================================*/
void main(void){
    setup();
    
    while(1){
        contador = PORTD;
    }
    return;
}
/*==============================================================================
                                    FUNCIONES
 =============================================================================*/


/*==============================================================================
                            CONFIGURACION DE PIC
 =============================================================================*/

void setup(void){
    //configurar leds de salida
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    ANSELH = 0x00;
    PORTD = 0X00;
    PORTB = 0x00;
    
    //configuracion de internal pullups y iocb
    OPTION_REGbits.nRBPU = 0; //internal pull-ups are enabled
    WPUB = 0b00000011;
    IOCBbits.IOCB0 = 1;     //Boton de inc
    IOCBbits.IOCB1 = 1;     //Boton de dec
    
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;    //limpiar bandera de interrupcion
    INTCONbits.GIE = 1;     //habilita las interrupciones globales
    INTCONbits.PEIE = 1;    //periferical interrupts
    
    //Configurar reloj interno
    OSCCONbits.IRCF0 = 0;        //reloj interno de 4mhz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.SCS = 1;  //internal oscillator is used for system clock
    
    //Inicializar I2C en esclavo
    I2C_Slave_Init(0x60); //se le asigna esta direccion al primer esclavo
    
    return;
}
