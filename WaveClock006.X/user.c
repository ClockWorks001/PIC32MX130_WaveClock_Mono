/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <plib.h>            /* Include to use PIC32 peripheral libraries     */
#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "system.h"         /* System funct/params, like osc/periph config    */
#include "user.h"            /* variables/params used by user.c               */


#include "vRTCC_lib.h"
#include "vTimer1_lib.h"
#include "vUSART_Menu_lib.h"
#include "vUSART_CMND_lib.h"
#include "vWave_lib.h"
#include "vWait_lib.h"
//#include "vLcd_I2C_lib.h"
#include "vSwitch_Menu_lib.h"
#include "vMotor_lib.h"


//#define LED0	LATBbits.LATB11 //Min routin check blink!
//#define LED1	LATBbits.LATB12 //Min routin check blink!

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* TODO Initialize User Ports/Peripherals/Project here */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void InitApp(void)
{

	//unsigned int pll_startup_counter = 100;
	//while(pll_startup_counter--);

	/* Setup analog functionality and port direction */
	// (1)Define PortB
    TRISB = 0x0000201E;    // 32bit I/O SETTING
    LATB  = 0x00000000;    // 32bit OUTPUT REGiSTER
    PORTB = 0x00000000;    // 32bit INPUT REGiSTER

	// (1)Define PortA
    TRISA = 0x0000000C;    // 32bit I/O SETTING
    LATA  = 0x00000000;    // 32bit OUTPUT REGiSTER
    PORTA = 0x00000000;    // 32bit INPUT REGiSTER

	// (2)Define ANSEL (All Degital Port)
    ANSELA = 0;
    ANSELB = 0;


	// (3)モジュール初期化
	vPushSwitch_init();

	vTIMER1_init();
	
//	vUSART_menu_init();
	vRTCC_init();
	
	vWait_100ms(3);
	vI2C_init();
	vLcd_init();
//	vLcd_printAt(0,0);
//	vLcd_str("test");

	//pFatFs////////////////////////////////////////////////////////////////////
	// Attach SPI1 module to I/O pads //
	//sample RPINR20 = 0x1F0C;	// SDI1 -- RP12 //
	//sample RPOR6 = 0x0800;	// SCK1OUT -- RP13 //
	//sample RPOR7 = 0x0007;	//* SDO1 -- RP14 //
	//SPIの為に、RA1/RP1:IN RA5/RP2:OUT RB1/RP4:OUTに設定が必要？

	SDI2R = 0b0011;	//SDI = RPB13	SPI2 DATA INPUT
//	RPOR4 = 10;		//PIN26 = SCK	SPI2 CLOCK OUTPUT
	RPA1R = 0b0100;	//RPA1 = SDO	SPI2 DATA OUTPUT

	SD_POWER_EN();
	MOTOR_DISEN();

	//Initialize SPI port
	//ビット幅8BIT、フレームなし、マスタ、クロックタイミングMODE0
	//#define SPI_OPEN  (SPI_OPEN_MODE8 | SPI_OPEN_CKE_REV | SPI_OPEN_SMP_END | SPI_OPEN_ON | SPI_OPEN_MSTEN)	// SPI open mode
	//#define SPI_CHN   2
	//SpiChnOpen(SPI_CHN, SPI_OPEN, 4);	// divide fpb by 4, configure the I/O ports. Not using SS in this example



	//enable a pull-up for the card detect, just in case the SD-Card isn't attached
	//  then lets have a pull-up to make sure we don't think it is there.
	//INTCON2bits.RBPU = 0;　　　//＜＝＝★★★★★★★★★★★★★★★★★★

	//pFatFs////////////////////////////////////////////////////////////////////

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
void user_main(void) {

	//割込み開始
	//RCONbits.IPEN = 0;			//高優先度割込み使用せず
	//INTCONbits.GIE = 1;			//

	//開始処理
//	LED0 = 1;						//LEDを点灯
	//	xprintf("Test Start!\r\n");	//開始のメッセージ

	while(1) {
		if(cFlag10mSec) {
			cFlag10mSec = 0;
			vSW2_Check();
			vSW1_Check();
			vSW3_Check();
			vSW4_Check();
			vModeSwitchControl00();		// Switch Main Menu control
			vModeSwitchControl01();		// Time set Menu control
			vModeSwitchControl02();		// Wave Play Menu control
//			vModeUartControl11();		// UART Menu contorol
			vWavePlayControl01();		// Wave Play status control
			
		}
		if(cFlagSec05) {
			cFlagSec05 = 0;
			vModeLcdControl01();			//lcd表示タスク
		}
		if(cFlag1Minute) {
			cFlag1Minute = 0;
			vCheckChimeIndexs();			//毎分毎のチャイムチェック
			vModeLcdControl01();			//lcd表示タスク
		}


		if(cFlagSec) {
			cFlagSec = 0;
			vModeLcdControl01();			//lcd表示タスク
			vPowerSave();

//			LED0 = ~LED0;
//			LED1 = ~LED0;
		}


		

	}
}