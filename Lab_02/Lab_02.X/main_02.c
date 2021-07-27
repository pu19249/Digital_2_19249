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
//char dividendo, centenas, residuo, decenas, unidades;
//char buffer[20];
//char dato;

char dato1;
char dato; //el dato que deseo almacenar en un str
char buffer[20]; //esta variable almacenara mi voltaje en un string
char buffer1[20];
char buffer2[2];
char buffer3[2];
char buffer4[2];
char buffer5[2];
char buffer6[2];
char buffer7[2];
/*==============================================================================
                        INTERRUPCIONES Y PROTOTIPOS
 =============================================================================*/
void setup(void);
char division1 (char dividendo);
char division2 (char dividendo);
char division3 (char dividendo);

char voltajes (char voltajes_1);
void mensaje(void);
void putch(char dato);


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
//    char buffer[20]; //esta variable almacenara mi voltaje en un string
//    char buffer1[20];
//    char dato1;
//    char dato; //el dato que deseo almacenar en un str
    Lcd_Set_Cursor(1,1); //ir a la primera linea en la posicion 1
    Lcd_Write_String("S_1:  S_2:  S_3:"); //imprimir los indicadores de voltaje
    
    while(1){   
    dato = voltaje1*0.0196; //obtengo el valor del ADRESH en la int
    dato1 = voltaje2*0.0196;
    sprintf(buffer, "%d", dato); //aqui obtengo el valor en decimal
    sprintf(buffer1, "%d", dato1);
    
    
    
    char centenas1 = division1(dato);
    char decenas1 = division2(dato);
    char unidades1 = division3(dato);
    
    char centenas2 = division1(dato1);
    char decenas2 = division2(dato1);
    char unidades2 = division3(dato1);
    sprintf(buffer2, "%d", centenas1);
    sprintf(buffer3, "%d", decenas1);
    sprintf(buffer4, "%d", unidades1);
    sprintf(buffer5, "%d", centenas2);
    sprintf(buffer6, "%d", decenas2);
    sprintf(buffer7, "%d", unidades2);
    
        
    Lcd_Set_Cursor(2,1); //ahora ir a la segunda linea
    Lcd_Write_String(buffer4); //mostrar lo que esta en mi string anterior
    Lcd_Write_String(".");
    Lcd_Write_String(buffer3);
    Lcd_Write_String(buffer2);
    Lcd_Write_String("   ");
    Lcd_Write_String(buffer7);
    Lcd_Write_String(".");
    Lcd_Write_String(buffer6);
    Lcd_Write_String(buffer5);
    
    
    
    //__delay_ms(1000); //un delay para asegurar que la busy flag permita recibir
         
    if (ADCON0bits.GO == 0){ //se apaga automaticamente entonces hay que
            __delay_us(100);     //volver a encenderlo
            ADCON0bits.GO = 1;
        }
    mensaje();
    }
    
    return;
}

char division1 (char dividendo){
    char centenas1 = dividendo/100;//esto me divide entre 100 y se queda con el entero
    char residuo1 = dividendo%100; //el residuo de lo que estoy operando
    char decenas1 = residuo1/10; 
    char unidades1 = residuo1%10; //se queda con las unidades de las decenas
    //las variables estan en todo el codigo entonces no necesito el return
    return centenas1;
} 

char division2 (char dividendo){
    char centenas2 = dividendo/100;//esto me divide entre 100 y se queda con el entero
    char residuo2 = dividendo%100; //el residuo de lo que estoy operando
    char decenas2 = residuo2/10; 
    char unidades2 = residuo2%10; //se queda con las unidades de las decenas
    //las variables estan en todo el codigo entonces no necesito el return
    return decenas2;
} 

char division3 (char dividendo){
    char centenas3 = dividendo/100;//esto me divide entre 100 y se queda con el entero
    char residuo3 = dividendo%100; //el residuo de lo que estoy operando
    char decenas3 = residuo3/10; 
    char unidades3 = residuo3%10; //se queda con las unidades de las decenas
    //las variables estan en todo el codigo entonces no necesito el return
    return unidades3;
} 


char voltajes(char voltaje_1){
    char voltaje_a;
    return voltaje_a = division(voltaje_1);
}

void mensaje(void){
    __delay_ms(500);
    printf("\rVoltaje1: ");
    printf(buffer4);
    printf(".");
    printf(buffer3);
    printf(buffer2);
    printf("\r\r");
    __delay_ms(500);
    printf("Voltaje2: ");
    printf(buffer7);
    printf(".");
    printf(buffer6);
    printf(buffer5);
    printf("\r-----------");
    __delay_ms(500);
    while (RCIF == 0);      //espera una respuesta de la seleccion
    
    return;
}
void putch(char dato){      //para la transmision
    while(TXIF == 0);
    TXREG = dato; //transmite los datos al recibir un printf en alguna  parte 
    return;
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
