/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.0
        Device            :  PIC32MX130F064B
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.40
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"
#include "./integer.h"
#include "./vTMR1_lib.h"

#define LED1_Toggle()   IO_RB6_Toggle() 
#define AUDIO_EN()		LATBbits.LATB5 = 0	/* CS = L */
#define	AUDIO_DISEN()	LATBbits.LATB5 = 1	/* CS = H */
#define	AUDIO_CE_Toggle() IO_RB5_Toggle()
#define SD_POWER_EN()		LATBbits.LATB10 = 1	/* CS = H */
#define	SD_POWER_DISEN()	LATBbits.LATB10 = 0	/* CS = L */

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    uiTMR001 = 0;
    
    AUDIO_EN();
    SD_POWER_EN();
    TMR1_Start();
    TMR2_Start();
//    TMR3_Start();
    OC1_Start();

    while (1)
    {
        // Add your application code
        
        if(FLAG_uiTMR001){
            uiTMR001 = 1000; //1000msec period
            LED1_Toggle(); 
        }
        
    }

    return -1;
}
/**
 End of File
*/