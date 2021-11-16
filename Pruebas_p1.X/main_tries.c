#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 8000000
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
#pragma config LVP = OFF         // Low Voltage Programming Enable bit 
//(RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit 
//(Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits 
//(Write protection off)


/*==============================================================================
                                VARIABLES
 =============================================================================*/
uint8_t quetzal;

/*==============================================================================
                               INTERRUPCIONES Y PROTOTIPOS
 =============================================================================*/
void setup(void);
void servo_1_1(void);
void servo_1_2(void);
void servo_1_3(void);
void servo_1_4(void);
void servo_1_5(void);


void __interrupt() isr(void){
//    if(RBIF){
//        if(RB1 == 0){
//            servo_1_5();
//            __delay_ms(2000);
//            servo_1_1();
//            quetzal++;
//        }
//       
//        RBIF = 0;
//    }
    
    if (ADIF == 1){
        if (ADCON0bits.CHS == 0){
            CCPR1L = (ADRESH>>1)+124;  //para que tome el rango desde el centro
            CCP1CONbits.DC1B1 = ADRESH & 0b01; //toma uno de los b que falta
            CCP1CONbits.DC1B0 = ADRESL>>7; //para el otro bit

            }

        
            ADIF = 0;           //apaga la bandera
    }
}


/*==============================================================================
                                LOOP PRINCIPAL
 =============================================================================*/

void main(void) {
    setup();
  
    while(1){
       // PORTA = quetzal;

        //if (ADCON0bits.GO == 0){       //si estaba en el canal0
        __delay_us(100);
        ADCON0bits.GO = 1; //inicia la conversion otra vez
        //}
    }
    return;
}


/*==============================================================================
                            CONFIGURACION DE PIC
 =============================================================================*/
void setup(void){
    //estos dos son los de mis pot
    ANSEL = 0B00000001;
//    ANSELbits.ANS1 = 1;
    ANSELH = 0x00;
    //en estos dos puertos estan mis servomotores
    // TRISA = 0x00;
    TRISA0 = 1;
    //TRISC2 = 0;
    TRISAbits.TRISA7 = 1;
    //configurar el oscilador interno  
    OSCCONbits.IRCF0 = 1;        //reloj interno de 8mhz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.SCS = 1;      
     
    //configurar el modulo ADC
    ADCON0bits.CHS = 0;     //canal 0
    __delay_us(100);
    
    ADCON0bits.ADCS0 = 0;   //para que el clock select sea FOSC/32
    ADCON0bits.ADCS1 = 1;   //que tiene el osc int hasta 500kHz maximo
    ADCON0bits.ADON = 1;    //ADC enable bit
    ADCON1bits.ADFM = 0;    //left justified
    ADCON1bits.VCFG1 = 0;   //5 voltios
    ADCON1bits.VCFG0 = 0;   //tierra
    
    
    //configuracion del PWM junto con el TMR2
    TRISCbits.TRISC2 = 1;   //habilitar momentaneamente el pin de salida
    TRISCbits.TRISC1 = 1;
    PR2 = 250;               //queremos que sea de 20ms por el servo
    CCP1CONbits.P1M = 0;    //modo PWM single output     
    CCP2CONbits.CCP2M = 0b1111; //para que sea PWM
    CCP1CONbits.CCP1M = 0b00001100; //PWM mode, P1A, P1C active-high
    
    
    CCPR1L = 0x0F;          //ciclo de trabajo
    CCP1CONbits.DC1B = 0;   //los bits menos significativos
    CCPR2L = 0x0F;
    CCP2CONbits.DC2B0 = 0; 
    CCP2CONbits.DC2B1 = 0;
    
    
    PIR1bits.TMR2IF = 0;    //limpiar la interrupcion del timer2
    T2CONbits.T2CKPS0 = 0;   //configurar el prescaler a 16
    T2CONbits.T2CKPS1 = 1;        
    T2CONbits.TMR2ON = 1;   //habilitar el tmr2on
    while (PIR1bits.TMR2IF == 0);
    PIR1bits.TMR2IF = 0;    //limpiar nuevamente
    TRISCbits.TRISC2 = 0;   //regresar el pin a salida
    TRISCbits.TRISC1 = 0;
    PIE1bits.ADIE = 1;      //enable de la int del ADC
    PIR1bits.ADIF = 0;      //limpiar la interrupcion del ADC
//    configurar interrupciones
    INTCONbits.GIE = 1;     //habilita las interrupciones globales
    INTCONbits.PEIE = 1;    //periferical interrupts
    
    TRISB1 = 1; //Boton para probar paso de infrarrojo
        //TRISB2 = 1;
    TRISD0 = 0;
    OPTION_REGbits.nRBPU = 0; //internal pull-ups are enabled
    WPUB = 0b00000110;
    IOCBbits.IOCB1 = 1;     //Boton de inc
    
    
    // configuracion del oscilador 
    
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;    //limpiar bandera de interrupcion
    
    //limpiar puertos
    PORTA = 0x00;
    PORTC = 0x00;
    PORTB = 0X00;
    PORTD = 0x00;
}
/*==============================================================================
                                    FUNCIONES
 =============================================================================*/

void servo_1_1(void){           //rango de posicion 1 para el servo1
    RD0 = 1;
    __delay_ms(0.7);            //siempre suman 20ms el periodo del servo
    RD0 = 0;
    __delay_ms(19.3);
}

void servo_1_2(void){           //rango de posicion 2 para el servo1
    RD0 = 1;
    __delay_ms(1.25);
    RD0 = 0;
    __delay_ms(18.75);
}

void servo_1_3(void){           //rango de posicion 3 para el servo1
    RD0 = 1;
    __delay_ms(1.5);
    RD0 = 0;
    __delay_ms(18.5);
}

void servo_1_4(void){           //rango de posicion 4 para el servo1
    RD0 = 1;
    __delay_ms(1.75);
    RD0 = 0;
    __delay_ms(18.25);
}

void servo_1_5(void){           //rango de posicion 5 para el servo1
    RD0 = 1;
    __delay_ms(2);
    RD0 = 0;
    __delay_ms(18);
}