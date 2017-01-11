/*******************************************************************************
 *	処理タイミング用 TIMER1 設定
 *  1000Hz 1msec interval
 *	author  :hiroshi murakami
 *	created :20161225
 *	modified:-
 ******************************************************************************/
#define TMR1_LIB

//#include <xc.h>            /* Include to use PIC32 peripheral libraries      */
#include "mcc_generated_files/mcc.h"
#include "vTMR1_lib.h"

//******************************************************************************
//   Function Name :Intrupt TIMER1
//   Outline       :タイマ1割り込み処理  1000Hz 1msec interval
//   Input         :
//   Output        :
//******************************************************************************
void Intrupt_TMR1(void)
{
	if (uiTMR001 > 0) --uiTMR001; // 1msec decrement timer with zero stopped 

}


