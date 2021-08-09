/* 
 * Archivo:   main01.c
 * Autor: Jonathan Pu c.19249
 * Descripcion de hardware: un uC maestro, dos esclavos y un dispositivo i2C,
 * pantalla LCD, leds y actuadores analogicos
 * Descripcion de software: este archivo corresponde al master el cual recibe
 * los valores de los otros dos/tres dispositivos
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
uint8_t voltaje;
/*==============================================================================
                               INTERRUPCIONES Y PROTOTIPOS
 =============================================================================*/
void setup(void);
/*==============================================================================
                                LOOP PRINCIPAL
 =============================================================================*/
void main(void){
    setup();
    while(1){
        //Obtener informacion del primer slave
        I2C_Master_Start();
        I2C_Master_Write(0x51); //51, el 1 para que lea
        PORTB = I2C_Master_Read(0); //lo escribo en el puerto de leds
        I2C_Master_Stop();
        __delay_ms(200);
       //Obtener informacion del sensor de temperatura
        //Direccion 0x90 porque A0 A1 y A2 estan a tierra
        I2C_Master_Start();
        I2C_Master_Write(0x80); //seleccionar el sensor y se escribe
        I2C_Master_Write(0xF3); //read temperature
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0x81); //para que ahora lea
        PORTA = I2C_Master_Read(0); //read temperature
        //voltaje = I2C_Master_Read(1);
        //I2C_Master_Write(0x22); //Stop convert
        I2C_Master_Stop();
        //I2C_Master_RepeatedStart();
        //PORTA = I2C_Master_Read(0);
        //I2C_Master_Stop();
        __delay_ms(200);
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
    //Salidas digitales para los leds del master
    TRISB = 0x00; //despliega lectura de pot
    ANSELH = 0x00;
    TRISA = 0x00; //para desplegar lectura de ds1621

     //Configurar reloj interno
    OSCCONbits.IRCF0 = 0;        //reloj interno de 4mhz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.SCS = 1;  //internal oscillator is used for system clock

    
    //Inicializar puertos
    PORTA = 0x00;
    PORTB = 0X00;
    PORTC = 0X00;
    PORTD = 0X00;
    
    //Inicializar la comunicacion I2C con la libreria
    I2C_Master_Init(100000); //Frecuencia recomendada tipica
    
    
    return;
}