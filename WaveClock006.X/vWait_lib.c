//********************************
//*  遅延関数ライブラリ
//*    vWait_us(time) ----- time x 1μsec遅延関数
//*    vWait_ms(time) ----- time x 1msec遅延関数
//*    vWait_100ms(time) ----- time x 100msec遅延関数
//********************************
#define WAIT_LIB

#include <plib.h>            /* Include to use PIC32 peripheral libraries      */
#include "system.h"
#include "vWait_lib.h"

//******************************
//*  1μsec遅延関数
//*  この関数でμ秒のウェイトを入れます。引数 100 = 約100μ秒ウェイト
//*  クロックスピードにより調整してください。
//*  1sec / (48Mhz / 4クロック実行サイクル) = 0.083usec / 1 instruction cycle
//******************************
void vWait_us(unsigned int uiTime)
{
	unsigned long ulT;
	//9850は実測値
    //ulT = uiTime * 9850 / 1000 ;
	ulT = uiTime * (10 * (40000000L / FCY)) ;
	while(ulT--);
}

//******************************
//*  1msec遅延関数
//*  この関数でミリ秒のウェイトを入れます。引数 100 = 約100ミリ秒ウェイト
//*  クロックスピードにより調整してください。
//******************************
void vWait_ms(unsigned int uiTime)
{
	unsigned long ulT;
	ulT = uiTime * (10000 * (40000000L / FCY)) ;
	while(ulT--);
}

//******************************
//*  100msec遅延関数
//*  この関数でミリ秒のウェイトを入れます。引数 1 = 約100ミリ秒ウェイト
//*  クロックスピードにより調整してください。
//******************************
void vWait_100ms(unsigned int uiTime)
{
	unsigned long ulT;
	ulT = uiTime * (1000000 * (40000000L / FCY)) ;
	while(ulT--);
}

