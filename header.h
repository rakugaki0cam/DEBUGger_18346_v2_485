/*  
 *  header.h
 * 
 * 
 *  2019.09.02
 * 
 */

#ifndef HEADER_H
#define HEADER_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "colorLCD.h"
#include "font.h"
#include "matrixKey.h"
#include "mcc_generated_files/mcc.h"
#include "printESC.h"
#include "printTEXT.h"


extern uint8_t title[];



void overrun_error(void);
void RS485_Write(uint8_t);

#endif //HEADER_H