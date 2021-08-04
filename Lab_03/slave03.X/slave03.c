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
#include <pic16f887.h> 
#define _XTAL_FREQ 4000000

#include "config_ADC.h" //libreria para configurar USART
#include "SPI.h"

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
uint8_t voltaje1, voltaje2;
uint8_t temporal1, temporal2;
/*==============================================================================
                        INTERRUPCIONES Y PROTOTIPOS
 =============================================================================*/
void setup (void);
//con la interrupcion se obtendra el valor del potenciometro
void __interrupt() isr(void){
    if(ADIF){
        if(ADCON0bits.CHS == 0){
            ADCON0bits.CHS = 1;
            voltaje2 = ADRESH;
             //ADIF = 0;
            }
        else if(ADCON0bits.CHS == 1){
            ADCON0bits.CHS = 0;
            voltaje1 = ADRESH;
             //ADIF = 0;
            
        }
    }
    ADIF = 0;
    
    
    if(SSPIF == 1){
        temporal1 = spiRead();
        spiWrite(voltaje1);
        temporal2 = spiRead();
        spiWrite(voltaje2);
        SSPIF = 0;
    }
   
}

/*==============================================================================
                             LOOP PRINCIPAL
 =============================================================================*/
void main(void){
    setup();
    
    while(1){
        //PORTB--;
        if (ADCON0bits.GO == 0){ //se apaga automaticamente entonces hay que
            __delay_us(100);     //volver a encenderlo
            ADCON0bits.GO = 1;
        }
    
    }
    
    
    return;
}
/*==============================================================================
                             FUNCIONES
 =============================================================================*/

/*==============================================================================
                         CONFIGURACION DEL PIC
 =============================================================================*/

void setup(void){
    //configurar las entradas de los potenciometros
    ANSEL = 0b00000011;
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISB = 0X00;
    
    //configuracion de interrupciones
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
    //configuracion de slave
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, 
            SPI_IDLE_2_ACTIVE);

    
//    configurar los pines de entradas y salidas para SPI
//    TRISCbits.TRISC3 = 1; //sck slave mode trisc3 bit must be set
//    TRISAbits.TRISA5 = 1; // Slave Select
//    TRISCbits.TRISC5 = 0; //SDO
//    
//    ADC
      config_ADC(1); //de la libreria
//    
//    SPI Slave
//    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW,
//            SPI_IDLE_2_ACTIVE);
//    SSPCON 0100 SPI Slave mode, clock = SCK pin, SS pin control enabled
//    
//    habiitar interrupciones
//    PIE1bits.ADIE = 1;      //enable de la int del ADC
//    PIR1bits.ADIF = 0;      //limpiar la interrupcion del ADC
//    INTCONbits.GIE = 1;         // Habilitamos interrupciones
//    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
//    PIR1bits.SSPIF = 0;         // Borramos bandera interrupcion MSSP
//    PIE1bits.SSPIE = 1;         // Habilitamos interrupcion MSSP
    
    //limpiar puertos
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    
    return;
}