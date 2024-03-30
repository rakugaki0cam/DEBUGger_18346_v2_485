/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F18346
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA2 procedures
#define RA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RA2_GetValue()              PORTAbits.RA2
#define RA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RA2_SetPullup()             do { WPUAbits.WPUA2 = 1; } while(0)
#define RA2_ResetPullup()           do { WPUAbits.WPUA2 = 0; } while(0)
#define RA2_SetAnalogMode()         do { ANSELAbits.ANSA2 = 1; } while(0)
#define RA2_SetDigitalMode()        do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set matrixX0 aliases
#define matrixX0_TRIS                 TRISAbits.TRISA4
#define matrixX0_LAT                  LATAbits.LATA4
#define matrixX0_PORT                 PORTAbits.RA4
#define matrixX0_WPU                  WPUAbits.WPUA4
#define matrixX0_OD                   ODCONAbits.ODCA4
#define matrixX0_ANS                  ANSELAbits.ANSA4
#define matrixX0_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define matrixX0_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define matrixX0_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define matrixX0_GetValue()           PORTAbits.RA4
#define matrixX0_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define matrixX0_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define matrixX0_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define matrixX0_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define matrixX0_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define matrixX0_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define matrixX0_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define matrixX0_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set matrixY0 aliases
#define matrixY0_TRIS                 TRISAbits.TRISA5
#define matrixY0_LAT                  LATAbits.LATA5
#define matrixY0_PORT                 PORTAbits.RA5
#define matrixY0_WPU                  WPUAbits.WPUA5
#define matrixY0_OD                   ODCONAbits.ODCA5
#define matrixY0_ANS                  ANSELAbits.ANSA5
#define matrixY0_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define matrixY0_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define matrixY0_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define matrixY0_GetValue()           PORTAbits.RA5
#define matrixY0_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define matrixY0_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define matrixY0_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define matrixY0_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define matrixY0_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define matrixY0_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define matrixY0_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define matrixY0_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set TXDE aliases
#define TXDE_TRIS                 TRISBbits.TRISB4
#define TXDE_LAT                  LATBbits.LATB4
#define TXDE_PORT                 PORTBbits.RB4
#define TXDE_WPU                  WPUBbits.WPUB4
#define TXDE_OD                   ODCONBbits.ODCB4
#define TXDE_ANS                  ANSELBbits.ANSB4
#define TXDE_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define TXDE_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define TXDE_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define TXDE_GetValue()           PORTBbits.RB4
#define TXDE_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define TXDE_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define TXDE_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define TXDE_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define TXDE_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define TXDE_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define TXDE_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define TXDE_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set LCD_DC aliases
#define LCD_DC_TRIS                 TRISBbits.TRISB5
#define LCD_DC_LAT                  LATBbits.LATB5
#define LCD_DC_PORT                 PORTBbits.RB5
#define LCD_DC_WPU                  WPUBbits.WPUB5
#define LCD_DC_OD                   ODCONBbits.ODCB5
#define LCD_DC_ANS                  ANSELBbits.ANSB5
#define LCD_DC_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define LCD_DC_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define LCD_DC_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define LCD_DC_GetValue()           PORTBbits.RB5
#define LCD_DC_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define LCD_DC_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define LCD_DC_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define LCD_DC_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define LCD_DC_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define LCD_DC_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define LCD_DC_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define LCD_DC_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set LCD_CS aliases
#define LCD_CS_TRIS                 TRISBbits.TRISB6
#define LCD_CS_LAT                  LATBbits.LATB6
#define LCD_CS_PORT                 PORTBbits.RB6
#define LCD_CS_WPU                  WPUBbits.WPUB6
#define LCD_CS_OD                   ODCONBbits.ODCB6
#define LCD_CS_ANS                  ANSELBbits.ANSB6
#define LCD_CS_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define LCD_CS_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define LCD_CS_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define LCD_CS_GetValue()           PORTBbits.RB6
#define LCD_CS_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define LCD_CS_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define LCD_CS_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define LCD_CS_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define LCD_CS_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define LCD_CS_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define LCD_CS_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define LCD_CS_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set matrixX3 aliases
#define matrixX3_TRIS                 TRISBbits.TRISB7
#define matrixX3_LAT                  LATBbits.LATB7
#define matrixX3_PORT                 PORTBbits.RB7
#define matrixX3_WPU                  WPUBbits.WPUB7
#define matrixX3_OD                   ODCONBbits.ODCB7
#define matrixX3_ANS                  ANSELBbits.ANSB7
#define matrixX3_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define matrixX3_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define matrixX3_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define matrixX3_GetValue()           PORTBbits.RB7
#define matrixX3_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define matrixX3_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define matrixX3_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define matrixX3_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define matrixX3_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define matrixX3_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define matrixX3_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define matrixX3_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set RC0 procedures
#define RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RC0_GetValue()              PORTCbits.RC0
#define RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RC0_SetPullup()             do { WPUCbits.WPUC0 = 1; } while(0)
#define RC0_ResetPullup()           do { WPUCbits.WPUC0 = 0; } while(0)
#define RC0_SetAnalogMode()         do { ANSELCbits.ANSC0 = 1; } while(0)
#define RC0_SetDigitalMode()        do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set SCK1 aliases
#define SCK1_TRIS                 TRISCbits.TRISC1
#define SCK1_LAT                  LATCbits.LATC1
#define SCK1_PORT                 PORTCbits.RC1
#define SCK1_WPU                  WPUCbits.WPUC1
#define SCK1_OD                   ODCONCbits.ODCC1
#define SCK1_ANS                  ANSELCbits.ANSC1
#define SCK1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define SCK1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define SCK1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define SCK1_GetValue()           PORTCbits.RC1
#define SCK1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define SCK1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define SCK1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define SCK1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define SCK1_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define SCK1_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define SCK1_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define SCK1_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set SDO1 aliases
#define SDO1_TRIS                 TRISCbits.TRISC2
#define SDO1_LAT                  LATCbits.LATC2
#define SDO1_PORT                 PORTCbits.RC2
#define SDO1_WPU                  WPUCbits.WPUC2
#define SDO1_OD                   ODCONCbits.ODCC2
#define SDO1_ANS                  ANSELCbits.ANSC2
#define SDO1_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SDO1_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SDO1_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SDO1_GetValue()           PORTCbits.RC2
#define SDO1_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SDO1_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SDO1_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define SDO1_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define SDO1_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define SDO1_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define SDO1_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define SDO1_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set matrixY2 aliases
#define matrixY2_TRIS                 TRISCbits.TRISC3
#define matrixY2_LAT                  LATCbits.LATC3
#define matrixY2_PORT                 PORTCbits.RC3
#define matrixY2_WPU                  WPUCbits.WPUC3
#define matrixY2_OD                   ODCONCbits.ODCC3
#define matrixY2_ANS                  ANSELCbits.ANSC3
#define matrixY2_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define matrixY2_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define matrixY2_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define matrixY2_GetValue()           PORTCbits.RC3
#define matrixY2_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define matrixY2_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define matrixY2_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define matrixY2_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define matrixY2_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define matrixY2_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define matrixY2_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define matrixY2_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set matrixX1 aliases
#define matrixX1_TRIS                 TRISCbits.TRISC4
#define matrixX1_LAT                  LATCbits.LATC4
#define matrixX1_PORT                 PORTCbits.RC4
#define matrixX1_WPU                  WPUCbits.WPUC4
#define matrixX1_OD                   ODCONCbits.ODCC4
#define matrixX1_ANS                  ANSELCbits.ANSC4
#define matrixX1_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define matrixX1_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define matrixX1_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define matrixX1_GetValue()           PORTCbits.RC4
#define matrixX1_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define matrixX1_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define matrixX1_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define matrixX1_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define matrixX1_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define matrixX1_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define matrixX1_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define matrixX1_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set matrixY1 aliases
#define matrixY1_TRIS                 TRISCbits.TRISC5
#define matrixY1_LAT                  LATCbits.LATC5
#define matrixY1_PORT                 PORTCbits.RC5
#define matrixY1_WPU                  WPUCbits.WPUC5
#define matrixY1_OD                   ODCONCbits.ODCC5
#define matrixY1_ANS                  ANSELCbits.ANSC5
#define matrixY1_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define matrixY1_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define matrixY1_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define matrixY1_GetValue()           PORTCbits.RC5
#define matrixY1_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define matrixY1_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define matrixY1_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define matrixY1_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define matrixY1_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define matrixY1_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define matrixY1_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define matrixY1_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set matrixX2 aliases
#define matrixX2_TRIS                 TRISCbits.TRISC6
#define matrixX2_LAT                  LATCbits.LATC6
#define matrixX2_PORT                 PORTCbits.RC6
#define matrixX2_WPU                  WPUCbits.WPUC6
#define matrixX2_OD                   ODCONCbits.ODCC6
#define matrixX2_ANS                  ANSELCbits.ANSC6
#define matrixX2_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define matrixX2_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define matrixX2_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define matrixX2_GetValue()           PORTCbits.RC6
#define matrixX2_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define matrixX2_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define matrixX2_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define matrixX2_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define matrixX2_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define matrixX2_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define matrixX2_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define matrixX2_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set matrixY3 aliases
#define matrixY3_TRIS                 TRISCbits.TRISC7
#define matrixY3_LAT                  LATCbits.LATC7
#define matrixY3_PORT                 PORTCbits.RC7
#define matrixY3_WPU                  WPUCbits.WPUC7
#define matrixY3_OD                   ODCONCbits.ODCC7
#define matrixY3_ANS                  ANSELCbits.ANSC7
#define matrixY3_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define matrixY3_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define matrixY3_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define matrixY3_GetValue()           PORTCbits.RC7
#define matrixY3_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define matrixY3_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define matrixY3_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define matrixY3_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define matrixY3_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define matrixY3_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define matrixY3_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define matrixY3_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCAF5 pin functionality
 * @Example
    IOCAF5_ISR();
 */
void IOCAF5_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCAF5 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCAF5 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF5_SetInterruptHandler(MyInterruptHandler);

*/
void IOCAF5_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCAF5 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCAF5_SetInterruptHandler() method.
    This handler is called every time the IOCAF5 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF5_SetInterruptHandler(IOCAF5_InterruptHandler);

*/
extern void (*IOCAF5_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCAF5 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCAF5_SetInterruptHandler() method.
    This handler is called every time the IOCAF5 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF5_SetInterruptHandler(IOCAF5_DefaultInterruptHandler);

*/
void IOCAF5_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF3 pin functionality
 * @Example
    IOCCF3_ISR();
 */
void IOCCF3_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF3 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF3 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF3_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF3_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF3 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF3_SetInterruptHandler() method.
    This handler is called every time the IOCCF3 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF3_SetInterruptHandler(IOCCF3_InterruptHandler);

*/
extern void (*IOCCF3_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF3 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF3_SetInterruptHandler() method.
    This handler is called every time the IOCCF3 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF3_SetInterruptHandler(IOCCF3_DefaultInterruptHandler);

*/
void IOCCF3_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF5 pin functionality
 * @Example
    IOCCF5_ISR();
 */
void IOCCF5_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF5 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF5 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF5_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF5_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF5 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF5_SetInterruptHandler() method.
    This handler is called every time the IOCCF5 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF5_SetInterruptHandler(IOCCF5_InterruptHandler);

*/
extern void (*IOCCF5_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF5 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF5_SetInterruptHandler() method.
    This handler is called every time the IOCCF5 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF5_SetInterruptHandler(IOCCF5_DefaultInterruptHandler);

*/
void IOCCF5_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF7 pin functionality
 * @Example
    IOCCF7_ISR();
 */
void IOCCF7_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF7 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF7 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF7_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF7_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF7 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF7_SetInterruptHandler() method.
    This handler is called every time the IOCCF7 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF7_SetInterruptHandler(IOCCF7_InterruptHandler);

*/
extern void (*IOCCF7_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF7 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF7_SetInterruptHandler() method.
    This handler is called every time the IOCCF7 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF7_SetInterruptHandler(IOCCF7_DefaultInterruptHandler);

*/
void IOCCF7_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/