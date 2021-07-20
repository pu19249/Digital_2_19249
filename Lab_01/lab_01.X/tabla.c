/*
 * File:   tabla_7.c
 * Author: Jonny Pu
 *
 * Created on July 19, 2021, 9:07 PM
 */


#include <xc.h>
#include <pic16f887.h> 


char tabla_7seg [16] = {0b00111111, 0b00000110, 0b01011011, 
                       0b01001111, 0b01100110, 0b01101101,
                       0b01111101, 0b00000111, 0b01111111,
                       0b01101111, 0b01110111, 0b01111100,
                       0b00111001, 0b01011110, 0b01111001, 0b01110001};

char traducir(char variable){
    
    char traduccion = tabla_7seg[variable];
    return traduccion;
}