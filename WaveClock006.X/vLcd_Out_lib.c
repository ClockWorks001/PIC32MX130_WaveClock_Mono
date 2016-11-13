/*******************************************************************************
 *	LCD output control 処理
 *	新規:20130505
 *	修正:-
 ******************************************************************************/
#define LCD_OUT_LIB

#include <plib.h>            /* Include to use PIC32 peripheral libraries      */
#include "system.h"
//#include "string.h"

#include "vLcd_i2c_lib.h"
#include "vLcd_Out_lib.h"
#include "vRTCC_lib.h"

//****************************
// 1行目の先頭から出力
//****************************
void vLcdOutLine(int iLine,BYTE *bLine_buff)
{
	int l;
	l = strlen(bLine_buff);
	vLcd_printAt(iLine,0);	//1行目先頭へ移動
	vLcd_str(bLine_buff);		//lcd2行目へ出力
    while(l < LCD_LINE_SIZE){	//表示の後ろの部分にspace詰め
        vLcd_data(' ');			//space出力
		l++;
    }

}

//****************************
// 行の指定位置からから出力　シフト用
// iline		:出力行
// *bLine_buff	:出力データbuffer
// iPosition	:何文字目から出力
//****************************
void vLcdShiftLine(int iLine, BYTE *bLine_buff, int iPosition)
{
	int l2;
	l2 = strlen(bLine_buff + iPosition);
	vLcd_printAt(iLine,0);			//2行目先頭へ移動

	vLcd_str(bLine_buff + iPosition);	//行の途中からlcd2行目へ出力
    while(l2 < LCD_LINE_SIZE){			//表示の後ろが空いているならば、先頭分から追加
        vLcd_data(*bLine_buff);			//先頭分から追加
		bLine_buff++;
		l2++;
    }

}

//*****************************
// write the Menu on LCD
//*****************************
void vLcd_L1buff_TimeSet(void)
{
	xsprintf(bLCD_Lin1_buff, "Time %02u:%02u:%02u ",ucHour,ucMin,ucSec);
	if(eModeLcdL1Status == eModeL1_pose){			//一定時間隔起動が停止なら
		vLcdOutLine(LCD_LINE1,bLCD_Lin1_buff);				//LCD1行目へ出力
	}
}

//*****************************
// write the Menu on LCD
//*****************************
void vLcd_L2buff_DateSet(void)
{
	xsprintf(bLCD_Lin2_buff, "Date %02u-%2u-%2u ",ucYear,ucMonth,ucDay);
	if(eModeLcdL2Status == eModeL2_pose){			//一定時間隔起動が停止なら
		vLcdOutLine(LCD_LINE2,bLCD_Lin2_buff);				//LCD2行目へ出力
	}
}

//****************************
// bufferのnullクリア
//****************************
void vLcdBuffClear(BYTE *bLine_buff)
{
	int i;
	for(i=0; i < LCD_BUFFER_SIZE; *(bLine_buff + i++) = '\0');
}

//******************************************************************************
//   Lcd Display mode control 01
//
//   Description   : 表示のコントロール用。
//                 : 0.5秒間隔で表示。
//   Precondition  :
//   Input         : bLCD_Lin1_buff :LCDの1行目
//                 : bLCD_Lin2_buff :LCDの2行目
//   Output        : LCD
//******************************************************************************
void vModeLcdControl01(void)
{
	static int iL1Cposition;
	static int iL2Cposition;

	switch (eModeLcdL1Status) {
	case  	eModeL1_TimeOut:
		vGetsRTCC_Time();					// RTCCモジュールから時間を取得する。
		vLcd_L1buff_TimeSet();
		vLcdOutLine(LCD_LINE1,bLCD_Lin1_buff);
		break;
	case  	eModeL1_pose:					//表示処理を switch_menuの設定に任せる状態
		break;
	default:
		eModeLcdL1Status = eModeL1_TimeOut;
		break;
	}

	switch (eModeLcdL2Status) {
	case  	eModeL2_DateOut :
		vGetsRTCC_Date();					// RTCCモジュールから日付を取得する。
		vLcd_L2buff_DateSet();
		vLcdOutLine(LCD_LINE2,bLCD_Lin2_buff);
		break;
	case  	eModeL2_pose:					//表示処理を switch_menuの設定に任せる状態
		break;
	case	eModeL2_shift_L_pre:
		//表示を左に動かす準備
		iL2Cposition = 0;
		eModeLcdL2Status++;
		break;
	case	eModeL2_shift_L_repeat:
		//表示を左に動かす動作中
		if(bLCD_Lin2_buff[iL2Cposition]=='\0'){
			iL2Cposition = 0;
		}
		vLcdShiftLine(LCD_LINE2, bLCD_Lin2_buff, iL2Cposition);
		iL2Cposition++;
		break;
	default:
		eModeLcdL2Status = eModeL2_DateOut;
		break;
	}

}
