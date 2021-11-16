/*
 * Alejandro Duarte y Jonathan Pu
 * 19446 - 19249
 * -ESTACIONAMIENTO-
 * Descripcion:
 * Se realiza el sistema de control de dos grupos de 4 parqueos cada uno
 * utilizando actuadores para detectar si 'hay' algun carro o no
 * y desplegandolo en un 7seg, con comunicacion UART se envia la informacion
 * a un ESP32 para desplegarlo en un monitor en tiempo real
 */

//***************************************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

void setup(){
  
}

void loop(){
  
}
