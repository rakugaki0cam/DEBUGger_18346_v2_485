/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F18346
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB             :  MPLAB X 5.20

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "pin_manager.h"




void (*IOCAF5_InterruptHandler)(void);
void (*IOCCF3_InterruptHandler)(void);
void (*IOCCF5_InterruptHandler)(void);
void (*IOCCF7_InterruptHandler)(void);


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x00;
    LATB = 0x60;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0x23;
    TRISB = 0x00;
    TRISC = 0xA9;

    /**
    ANSELx registers
    */
    ANSELC = 0x54;
    ANSELB = 0xF0;
    ANSELA = 0x13;

    /**
    WPUx registers
    */
    WPUB = 0x00;
    WPUA = 0x20;
    WPUC = 0xAE;

    /**
    ODx registers
    */
    ODCONA = 0x10;
    ODCONB = 0x80;
    ODCONC = 0x50;

    /**
    SLRCONx registers
    */
    SLRCONA = 0x37;
    SLRCONB = 0xE0;
    SLRCONC = 0xF9;

    /**
    INLVLx registers
    */
    INLVLA = 0x3F;
    INLVLB = 0xF0;
    INLVLC = 0xFF;


    /**
    IOCx registers 
    */
    //interrupt on change for group IOCAF - flag
    IOCAFbits.IOCAF5 = 0;
    //interrupt on change for group IOCAN - negative
    IOCANbits.IOCAN5 = 1;
    //interrupt on change for group IOCAP - positive
    IOCAPbits.IOCAP5 = 1;
    //interrupt on change for group IOCCF - flag
    IOCCFbits.IOCCF3 = 0;
    //interrupt on change for group IOCCF - flag
    IOCCFbits.IOCCF5 = 0;
    //interrupt on change for group IOCCF - flag
    IOCCFbits.IOCCF7 = 0;
    //interrupt on change for group IOCCN - negative
    IOCCNbits.IOCCN3 = 1;
    //interrupt on change for group IOCCN - negative
    IOCCNbits.IOCCN5 = 1;
    //interrupt on change for group IOCCN - negative
    IOCCNbits.IOCCN7 = 1;
    //interrupt on change for group IOCCP - positive
    IOCCPbits.IOCCP3 = 1;
    //interrupt on change for group IOCCP - positive
    IOCCPbits.IOCCP5 = 1;
    //interrupt on change for group IOCCP - positive
    IOCCPbits.IOCCP7 = 1;



    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCAF5_SetInterruptHandler(IOCAF5_DefaultInterruptHandler);
    IOCCF3_SetInterruptHandler(IOCCF3_DefaultInterruptHandler);
    IOCCF5_SetInterruptHandler(IOCCF5_DefaultInterruptHandler);
    IOCCF7_SetInterruptHandler(IOCCF7_DefaultInterruptHandler);
   
    // Enable IOCI interrupt 
    PIE0bits.IOCIE = 1; 
    
	
    RXPPS = 0x10;   //RC0->EUSART:RX;    
    SSP1CLKPPS = 0x11;   //RC1->MSSP1:SCK1;    
    RC1PPS = 0x18;   //RC1->MSSP1:SCK1;    
    RC2PPS = 0x19;   //RC2->MSSP1:SDO1;    
    RA2PPS = 0x14;   //RA2->EUSART:TX;    
}
  
void PIN_MANAGER_IOC(void)
{   
	// interrupt on change for pin IOCAF5
    if(IOCAFbits.IOCAF5 == 1)
    {
        IOCAF5_ISR();  
    }	
	// interrupt on change for pin IOCCF3
    if(IOCCFbits.IOCCF3 == 1)
    {
        IOCCF3_ISR();  
    }	
	// interrupt on change for pin IOCCF5
    if(IOCCFbits.IOCCF5 == 1)
    {
        IOCCF5_ISR();  
    }	
	// interrupt on change for pin IOCCF7
    if(IOCCFbits.IOCCF7 == 1)
    {
        IOCCF7_ISR();  
    }	
}

/**
   IOCAF5 Interrupt Service Routine
*/
void IOCAF5_ISR(void) {

    // Add custom IOCAF5 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF5_InterruptHandler)
    {
        IOCAF5_InterruptHandler();
    }
    IOCAFbits.IOCAF5 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF5 at application runtime
*/
void IOCAF5_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF5_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF5
*/
void IOCAF5_DefaultInterruptHandler(void){
    // add your IOCAF5 interrupt custom code
    // or set custom function using IOCAF5_SetInterruptHandler()
}

/**
   IOCCF3 Interrupt Service Routine
*/
void IOCCF3_ISR(void) {

    // Add custom IOCCF3 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCCF3_InterruptHandler)
    {
        IOCCF3_InterruptHandler();
    }
    IOCCFbits.IOCCF3 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF3 at application runtime
*/
void IOCCF3_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCCF3_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF3
*/
void IOCCF3_DefaultInterruptHandler(void){
    // add your IOCCF3 interrupt custom code
    // or set custom function using IOCCF3_SetInterruptHandler()
}

/**
   IOCCF5 Interrupt Service Routine
*/
void IOCCF5_ISR(void) {

    // Add custom IOCCF5 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCCF5_InterruptHandler)
    {
        IOCCF5_InterruptHandler();
    }
    IOCCFbits.IOCCF5 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF5 at application runtime
*/
void IOCCF5_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCCF5_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF5
*/
void IOCCF5_DefaultInterruptHandler(void){
    // add your IOCCF5 interrupt custom code
    // or set custom function using IOCCF5_SetInterruptHandler()
}

/**
   IOCCF7 Interrupt Service Routine
*/
void IOCCF7_ISR(void) {

    // Add custom IOCCF7 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCCF7_InterruptHandler)
    {
        IOCCF7_InterruptHandler();
    }
    IOCCFbits.IOCCF7 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF7 at application runtime
*/
void IOCCF7_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCCF7_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF7
*/
void IOCCF7_DefaultInterruptHandler(void){
    // add your IOCCF7 interrupt custom code
    // or set custom function using IOCCF7_SetInterruptHandler()
}

/**
 End of File
*/