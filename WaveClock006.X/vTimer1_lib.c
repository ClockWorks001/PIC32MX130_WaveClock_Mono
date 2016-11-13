/*******************************************************************************
 *	処理タイミング用 TIMER1 設定
 *	新規:20130128
 *	修正:-
 ******************************************************************************/
#define TIMER1_LIB

#include <plib.h>            /* Include to use PIC32 peripheral libraries      */
#include <sys/attribs.h>     /* For __ISR definition                          */
#include "system.h"
#include "vTIMER1_lib.h"


//#define OUT_T1	LATBbits.LATB4

/*****************************
 * initialization
 *****************************/
void vTIMER1_init(void) {
// Let compile time pre-processor calculate the PR1 (period)
//#define PBCLK				(SYS_FREQ / PB_DIV)	// Peripheral Clock
#define PRESCALE       		256
#define TOGGLES_PER_SEC		100				// 100hz = 10msec
#define T1_TICK       		(PBCLK/PRESCALE/TOGGLES_PER_SEC )

    // configure Timer 1 using internal clock, 1:256 prescale
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_256, T1_TICK);
//    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_256, 35500);
    // set up the timer interrupt with a priority of 2
    ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_2);

}

/*****************************
 * TIMER1 CLOSE
 *****************************/
void vTIMER1_close(void) {
	CloseTimer1();
}


//******************************************************************************
//   Function Name :
//   Title         : Intrupt TIMER1
//   Input         :
//   Output        :
//******************************************************************************
void __ISR(_TIMER_1_VECTOR, ipl2) Intrupt_TIMER1(void)
{
    unsigned char  IO_char;

// ********************************
// 1.Clear the Timer1 interrupt Flag
// ********************************
	IFS0bits.T1IF = 0;

	// タイマ1割り込み処理  10msc毎

	sMSecc = sMSecc + 10;

//	if(!(sMSecc % 10) ) {
		cFlag10mSec ++;					//10msec TaskFlag set. Switch, Task 用
		if(!(sMSecc % 500) ){			//500msec = 0.5sec 経過をチェック
			cFlagSec05++;				//0.5sec  TaskFlag set. Lcd 用
		}
		if(sMSecc >= 1000 ){			//1000msec = 1sec 経過をチェック
			sMSecc = 0;
			cFlagSec++;					//1sec TaskFlag set. LED moniter 用
		}
//	}

}