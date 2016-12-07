/*******************************************************************************
 *	RTCC処理
 *	c32の Peripheral Library を使用しています。
 *	新規:20130130
 *	修正:-
 ******************************************************************************/
#define RTCC_LIB

#include <plib.h>            /* Include to use PIC32 peripheral libraries      */
#include <sys/attribs.h>     /* For __ISR definition                          */
#include "vWAVE_lib.h"		//FILE_INDEXSを定義している為、vRTCC_lib.hより先に記載する。
#include "vRTCC_lib.h"

/*****************************
 * VARIABLES
 *****************************/

//******************************************************************************
//   Function Name : Intrupt_RTCC
//   Title         : Intrupt RTCC
//   Input         :
//   Output        :
//******************************************************************************
void __ISR(_RTCC_VECTOR, ipl3) Intrupt_RTCC(void){
	// once we get in the RTCC ISR we have to clear the RTCC int flag
	INTClearFlag(INT_RTCC);
	cFlag1Minute++;
	xputs( "\n\rIntrupt_RTCC");

}

/*****************************
 * initialization
 *****************************/
void vRTCC_init(void) {
	rtccTime	tm;	//ファンクション用のrtccTime変数を定義 Peripheral Library 参照
	rtccDate	dt;	//ファンクション用のrtccDate変数を定義 Peripheral Library 参照
	// Setup RTCC
	vGetsRTCC();
	if ((ucHour > 23) || (ucMonth > 12) || (ucDay > 31))  {
        tm.l = 0;
        tm.sec = 0x00;
        tm.min = 0x00;
        tm.hour = 0x20;
        dt.l = 0;
        dt.wday = 6;
        dt.mday = 0x25;
        dt.mon = 0x11;
        dt.year = 0x16;
//		RtccOpen(0x00000000,0x09100804,0);
		RtccOpen(tm.l, dt.l ,0);
	}
	RtccInit();				// init the RTCC
	while(RtccGetClkStat()!=RTCC_CLK_ON);	// wait for the SOSC to be actually running and RTCC to have its clock source
							// could wait here at most 32ms

	
	RtccSetAlarmTime(0x00000000);		// set the alarm time 0xhhmmss00
	RtccChimeEnable();					// enable indefinite repeats
	RtccSetAlarmRptCount(0);			// set the initial repeat count (only one alarm)
	RtccSetAlarmRpt(RTCC_RPT_MIN);		// enable repeat rate, every minute, for ex
	RtccAlarmEnable();					// enable the alarm
//	RtccAlarmDisable();					// disable the alarm
//	isAlrmEn=RtccGetAlarmEnable();		// check that the alarm is enabled
	
	INTSetVectorPriority(INT_RTCC_VECTOR, INT_PRIORITY_LEVEL_3);			// set the RTCC priority in the INT controller
	INTSetVectorSubPriority(INT_RTCC_VECTOR, INT_SUB_PRIORITY_LEVEL_1);		// set the RTCC sub-priority in the INT controller
	INTEnable(INT_RTCC, INT_ENABLED);					// enable the RTCC event interrupts in the INT controller.
	INTClearFlag(INT_RTCC);

	//RtccSetCalibration(0);

	//vSetChimeIndexs();
	strcpy(ChimeIndexs.bIndexNxt, "9998"); // 初期化後一回読み込む為、9999ではなく9998を設定。

}

/*****************************
 * RTCCモジュールから時間を取得する。
 *****************************/
void vGetsRTCC_Time(void) {
	rtccTime	tm;	//ファンクション用のrtccTime変数を定義 Peripheral Library 参照
	rtccDate	dt;	//ファンクション用のrtccDate変数を定義 Peripheral Library 参照

	RtccGetTimeDate(&tm, &dt);

	ucHour  = ucBCDtoHEX(tm.hour);
	ucMin	= ucBCDtoHEX(tm.min);
	ucSec	= ucBCDtoHEX(tm.sec);
}

/*****************************
 * RTCCモジュールから日付を取得する。
 *****************************/
void vGetsRTCC_Date(void) {
	rtccTime	tm;	//ファンクション用のrtccTime変数を定義 Peripheral Library 参照
	rtccDate	dt;	//ファンクション用のrtccDate変数を定義 Peripheral Library 参照

	RtccGetTimeDate(&tm, &dt);

	ucYear  = ucBCDtoHEX(dt.year);
	ucMonth = ucBCDtoHEX(dt.mon);
	ucDay	= ucBCDtoHEX(dt.mday);
	ucWDay  = ucBCDtoHEX(dt.wday);
}

/*****************************
 * RTCCモジュールから日付時間を取得する。
 *****************************/
void vGetsRTCC(void) {

	vGetsRTCC_Date();
	vGetsRTCC_Time();
/*
	rtccTime	tm;	//ファンクション用のrtccTime変数を定義 Peripheral Library 参照
	rtccDate	dt;	//ファンクション用のrtccDate変数を定義 Peripheral Library 参照

	RtccGetTimeDate(&tm, &dt);

	ucYear  = ucBCDtoHEX(dt.year);
	ucMonth = ucBCDtoHEX(dt.mon);
	ucDay	= ucBCDtoHEX(dt.mday);
	ucWDay  = ucBCDtoHEX(dt.wday);
	ucHour  = ucBCDtoHEX(tm.hour);
	ucMin	= ucBCDtoHEX(tm.min);
	ucSec	= ucBCDtoHEX(tm.sec);
*/

 }

/*****************************
 * 時間をRTCCモジュールに設定する
 *****************************/
void vSetsRTCC_Time(void) {
	rtccTime	tm;	//ファンクション用のrtccTime変数を定義 Peripheral Library 参照

	tm.rsvd = 0;
	tm.hour = ucHEXtoBCD(ucHour);
	tm.min  = ucHEXtoBCD(ucMin);
	tm.sec  = ucHEXtoBCD(ucSec);
	RtccSetTime(tm.l);

}

/*****************************
 * 日付をRTCCモジュールに設定する
 *****************************/
void vSetsRTCC_Date(void) {
	rtccDate	dt;	//ファンクション用のrtccDate変数を定義 Peripheral Library 参照

	dt.year = ucHEXtoBCD(ucYear);
	dt.mon  = ucHEXtoBCD(ucMonth);
	dt.mday = ucHEXtoBCD(ucDay);
	dt.wday = 0;
	RtccSetDate(dt.l);
}

/*****************************
 * BCD(8bit)->HEX(8bit)変換
 *****************************/
unsigned char ucBCDtoHEX(unsigned char ucBCD) {
	return((ucBCD >> 4) * 10 + (ucBCD & 0x0F));
}

/*****************************
 * BCD(8bit)<-HEX(8bit)変換
 *****************************/
unsigned char ucHEXtoBCD(unsigned char ucHEX) {
	return(((ucHEX / 10) << 4) | (ucHEX % 10));
}

//******************************************************************************
//   Function Name : vSetChimeOFF
//   Title         :
//   Input         :
//   Output        : iChime_ON = CHIME_OFF
//******************************************************************************
void vSetChimeOFF(void) {
	iChime_ON = CHIME_OFF;
}

//******************************************************************************
//   Function Name : vSetChimeIndexs
//   Title         : Intrupt RTCC
//   Input         :
//   Output        : ChimeIndexs
//******************************************************************************
void vSetChimeIndexs(void) {
	BYTE bChimeMessage[125];
	BYTE bTime[5];
	BYTE *bChimeMessage_ptr = bChimeMessage;

	iChime_ON = CHIME_ON;
	vGetsRTCC();			// RTCCモジュールから日付時間を取得する。
	xsprintf(bTime, "%02d%02d", ucHour, ucMin);
	if(bSearchListAndGetFileName(bTime, "Chime.txt", &bChimeMessage_ptr, &ChimeIndexs) !=0 ){
		strcpy(ChimeIndexs.bIndexNxt, "9999") ;
	}
	xprintf( "\n\rTime is %s. ChimeNext is %s. and CHIME_ON?=%d ",bTime , ChimeIndexs.bIndexNxt, iChime_ON);
}

//******************************************************************************
//   Function Name : vCheckChimeIndexs
//   Title         : vCheckChimeIndexs RTCC
//   Input         :
//   Output        :
//******************************************************************************
void vCheckChimeIndexs(void) {
	static BYTE bChimeMessage[125];
	BYTE bTime[5];
	BYTE *bChimeMessage_ptr = bChimeMessage;
    
	vGetsRTCC();			// RTCCモジュールから日付時間を取得する。
	xsprintf(bTime, "%02d%02d", ucHour, ucMin);
	xprintf( "\n\rTime is %s", bTime);
	xprintf( "\n\rChimeNext is %s. and CHIME_ON?=%d ", ChimeIndexs.bIndexNxt, iChime_ON);

	if(iChime_ON){

		if(strcmp(ChimeIndexs.bIndexNxt, "9999") == 0){
			//vSetChimeIndexs();
			iChime_ON = CHIME_OFF;
		}else if(strcmp(ChimeIndexs.bIndexNxt, bTime) < 0){
			vSetChimeIndexs();
		}else if(strcmp(ChimeIndexs.bIndexNxt, "2359") > 0){
			vSetChimeIndexs();
		}

		//取得した時間と、次のチャイムの時間を比較する。
		if(strcmp(bTime, ChimeIndexs.bIndexNxt) == 0){
			//次のチャイムの時間とあったならば、時報をならす。
			if(bSearchListAndGetFileName(bTime, "Chime.txt", &bChimeMessage_ptr, &ChimeIndexs) == 0){
					xprintf( "\n\rChimeIndexs Min:%s Max:%s Next:%s ", ChimeIndexs.bIndexMin, ChimeIndexs.bIndexMax, ChimeIndexs.bIndexNxt);
					vWavePlayStart(bChimeMessage);		//WAVE FILE LISTを渡してSTART
			}
		}
	}

}

