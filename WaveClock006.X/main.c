/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <plib.h>           /* Include to use PIC32 peripheral libraries      */
#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */

#include "system.h"         /* System funct/params, like osc/periph config    */
#include "user.h"           /* User funct/params, such as InitApp             */

/******************************************************************************/
/* Configuration Bits                                                         */
/******************************************************************************/

/* TODO Fill in your configuration bits from the config bits generator here.  */
#pragma config PMDL1WAY  = OFF		//Peripheral Module Disable Configuration:Allow multiple reconfigurations
#pragma config IOL1WAY   = OFF		//Peripheral Pin Select Configuration:Allow multiple reconfigurations
//#pragma config FUSBIDIO  = OFF		//USB USID Selection:Controlled by Port Function
//#pragma config FVBUSONIO = OFF		//USB VBUS ON Selection:Controlled by Port Function
#pragma config FPLLIDIV  = DIV_2
#pragma config FPLLMUL   = MUL_20
//#pragma config UPLLIDIV  = DIV_1		//USB PLL Input Divider:
//#pragma config UPLLEN	 = OFF			//USB PLL Enable:
#pragma config FPLLODIV  = DIV_2		//System PLL Output Clock Divider:
#pragma config FNOSC     = FRCPLL	//Fast RC Osc with PLL
#pragma config FSOSCEN   = ON		//Secondary Oscillator Enable:Enable (and SOSCEN has tobe ON)
#pragma config IESO      = ON		//Internal/External Switch Over:Enable
#pragma config POSCMOD   = OFF		//Primary Oscillator Configuration:Primary osc disabled (EC,XT,HS,OFF)
#pragma config OSCIOFNC  = OFF		//CLKO Output Signal Active on the OSCO Pin::disabled
#pragma config FPBDIV    = DIV_1	//Peripheral Clock Divisor:Pb_Clk is Sys_Clk/1 (DIV_1,DIV_2,DIV_4,DIV_8)
#pragma config FCKSM     = CSECMD	//Clock Switching and Monitor Selection:Clock Switch Disable, FSCM Disabled (CSECME,CSECMD,CSDCMD)
#pragma config WDTPS     = PS1		//Watchdog Timer Postscaler:1:1 (PS1,,,,PS1048576)
#pragma config WINDIS    = OFF		//Watchdog Timer Window Enable:Watchdog Timer is in Non-Window Mode
#pragma config FWDTEN    = OFF		//Watchdog Timer Enable:WDT Disabled (SWDTEN Bit Controls)
#pragma config FWDTWINSZ = WINSZ_50	//Watchdog Timer Window Size:Window Size is 50% (WINSZ_75,WINSZ_50,WINSZ_37,WISZ_25)
#pragma config DEBUG     = OFF		//Background Debugger Enable:Debugger is Disabled
#pragma config JTAGEN    = OFF		//JTAG Enable:JTAG Disabled
#pragma config ICESEL	 = ICS_PGx1	//ICE/ICD Comm Channel Select:Reserved (RESERVED,ICS_PGx3,ICS_PGx2,ICS_PGx1)
#pragma config PWP       = OFF		//Program Flash Write Protect:
#pragma config BWP       = OFF		//Boot Flash Write Protect bit:
#pragma config CP        = OFF		//Code Protect:

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint32_t <variable_name>; */


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int32_t main(void)
{

    /*Refer to the C32 peripheral library documentation for more
    information on the SYTEMConfig function.
    
    This function sets the PB divider, the Flash Wait States, and the DRM
    /wait states to the optimum value.  It also enables the cacheability for
    the K0 segment.  It could has side effects of possibly alter the pre-fetch
    buffer and cache.  It sets the RAM wait states to 0.  Other than
    the SYS_FREQ, this takes these parameters.  The top 3 may be '|'ed
    together:
    
    SYS_CFG_WAIT_STATES (configures flash wait states from system clock)
    SYS_CFG_PB_BUS (configures the PB bus from the system clock)
    SYS_CFG_PCACHE (configures the pCache if used)
    SYS_CFG_ALL (configures the flash wait states, PB bus, and pCache)*/

    /* TODO Add user clock/system configuration code if appropriate.  */
    SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL); 

    /*Configure Multivector Interrupt Mode.  Using Single Vector Mode
    is expensive from a timing perspective, so most applications
    should probably not use a Single Vector Mode*/
  	//マルチベクタ割り込み設定、割り込み許可
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
	IEC0 = IEC1 = IFS0 = IFS1 = 0;

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    /* Initialize I/O and Peripherals for application */
    InitApp();

	INTEnableSystemMultiVectoredInt();

// *******************
//  2.Program Main
// *******************
    //while(1);
	user_main();

	return (EXIT_SUCCESS);


}
