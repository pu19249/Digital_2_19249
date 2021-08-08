/* 
 * File:  config_ADC
 * Author: Jonathan Pu
 * Comments: configuracion de ADC
 * Revision history: 18.07.202
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#pragma config FOSC = INTRC_NOCLKOUT
#include <xc.h> // include processor files - each processor file is guarded.  

//defino el prototipo de la funcion
void config_ADC(char frec); //tomara el valor que deseamos de la frecuencia
#endif	/* XC_HEADER_TEMPLATE_H */

