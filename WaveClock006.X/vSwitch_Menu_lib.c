/*************************************************
*  Switch_Menu処理
*    vPushSwitch_init()  ----- 初期化
*    vSW2_Check() ----- SW2_ チェック＆repeat処理
*    vSW2_UserHandling() ----- SW2_が押された時の本体処理
*    vSW1_Check() ----- SW1_ チェック＆repeat処理
*    vSW1_UserHandling() ----- SW1_が押された時の本体処理
*************************************************/
#define SWITCH_MENU_LIB

#include <plib.h>            /* Include to use PIC32 peripheral libraries      */
#include "system.h"
#include "string.h"

#include "vSwitch_Menu_lib.h"
#include "vLcd_i2c_lib.h"
#include "vLcd_Out_lib.h"
#include "vRTCC_lib.h"
#include "vTo_ascii_lib.h"
#include "vUSART_Menu_lib.h"
#include "vERROR_CODE.h"
#include "vWave_lib.h"

#define LED0	LATBbits.LATB11 //Min routin check blink!
#define LED1	LATBbits.LATB12 //Min routin check blink!


/*****************************
*  Initialize
*****************************/
void vPushSwitch_init(void)
{
    //Initialize the user pushbuttons
    //ANSELHbits.ANS11 = 0;			//Analog off
    //INTCON2bits.RABPU = 0;			//pull-ups are enabled(corresponding WPUA and WPUB bits)
    //WPUBbits.WPUB5 = 1;				//Pull up SW2_
    //WPUBbits.WPUB7 = 1;				//Pull up SW1_
    //TRISBbits.TRISB5 = 1;			//INPUT_PIN;
    //TRISBbits.TRISB7 = 1;			//INPUT_PIN;

	unsigned temp;


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 1. enable change notice, enable discrete pins and weak pullups
	//  CNx_IDLE_STOP=> SIDL=0 / CNx_IDLE_CON=> SIDL=1
	//   SIDL: Peripheral Stop in Idle Mode bit
	//   1 = Discontinue module operation when device enters Idle mode
	//   0 = Continue module operation in Idle mode

	mCNAOpen(CNA_ON | CNA_IDLE_STOP, CNA2_ENABLE | CNA3_ENABLE, CNA2_PULLUP_ENABLE | CNA3_PULLUP_ENABLE);
	mCNBOpen(CNB_ON | CNB_IDLE_STOP, CNB2_ENABLE | CNB3_ENABLE, CNB2_PULLUP_ENABLE | CNB3_PULLUP_ENABLE);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 2. read port(s) to clear mismatch on change notice pins
    temp = PORTRead(IOPORT_A);
    temp = PORTRead(IOPORT_B);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 3. clear change notice interrupt flag

    ConfigIntCNA(CHANGE_INT_PRI_1 | CHANGE_INT_ON);
    ConfigIntCNB(CHANGE_INT_PRI_1 | CHANGE_INT_ON);
}

void __ISR(_CHANGE_NOTICE_VECTOR, ipl1) Intrupt_CN(void)
{
	unsigned int temp;

    // clear the interrupt flag
//	mCNAClearIntFlag();
//	mCNBClearIntFlag();
	IFS1bits.CNAIF = 0;
	IFS1bits.CNBIF = 0;

    // clear the mismatch condition
    temp = PORTRead(IOPORT_A);
    temp = PORTRead(IOPORT_B);


//	vSW2_Check();
//	vSW1_Check();
//	vSW3_Check();
//	vSW4_Check();

//	LED0 = ~LED0;
//	LED1 = ~LED0;
	LED0 = 0;
	LED1 = 1;

}


//******************************************************************************
//   Switch SW2
//******************************************************************************
/*****************************
* push SW2 on/off check section
* this section is set at 10msec section.
* it has repeat.
*****************************/
void vSW2_Check(void)
{

	static unsigned short usSW2_OnTime = 0;

	if(!SW2){	//switch ON when an Input port is low.
		switch(usSW2_OnTime)
		{
			case 0:
				//user handling here
				vSW2_UserHandling();
				break;
			case 100:					//10msec*100 wait after the first push
				//user handling here
				vSW2_UserHandling();
				usSW2_OnTime = 100 - 30; 	//10msec*30 wait for Next repeat
				break;
			default:
				break;
		}
		usSW2_OnTime++;
	}else{
		usSW2_OnTime = 0;
	}
}

/*****************************
* SW2 User Handling
*****************************/
void vSW2_UserHandling(void)
{
	cSW2_flag = SWITCH_ON;
}

/*****************************
* SW2 test
*****************************/
char cSW2_ON(void)
{
	if(cSW2_flag == SWITCH_ON){
		cSW2_flag = SWITCH_OFF;
		return 1;
	}
	return 0;
}

//******************************************************************************
//   Switch SW1
//******************************************************************************
/*****************************
 * push SW1 on/off check section
 * SW1 go forward the switch status.
 * this section is set at 10msec section.
 * it don't use repeat.
 *****************************/
void vSW1_Check(void)
{

	static unsigned short usSW1_OnTime = 0;

	if(!SW1){	//switch ON when an Input port is low.
		switch(usSW1_OnTime)
		{
			case 0:
				//user handling here
				vSW1_UserHandling();
				usSW1_OnTime++;
				break;
/*
			case 100:					//10msec*200 wait for the first push
				//user handling here
				vSW1_UserHandling();
				usSW1_OnTime = 100 - 30; 	//10msec*30 wait for repeat
				break;
*/
			default:
				break;
		}
//		usSW1_OnTime++;
	}else{
		usSW1_OnTime = 0;
	}
}

/*****************************
* SW1 User Handling
*****************************/

void vSW1_UserHandling(void)
{
	//bring forward the Switch menu status
	eModeSwitchStatus1++;
	if(eModeSwitchStatus1==eModeS1_end){
		eModeSwitchStatus1=eModeS1_clock;
	}
}

//******************************************************************************
//   Switch SW3
//******************************************************************************
//****************************
// push Switch SW3 on/off check section
// this section is set at 10msec section.
// it has repeat.
//****************************
void vSW3_Check(void)
{

	static unsigned short usSW3OnTime = 0;

	if(!SW3){	//switch ON when an Input port is low.
		switch(usSW3OnTime)
		{
			case 0:
				//user handling here
				vSW3_UserHandling();
				break;
			case 100:					//10msec*100 wait after the first push
				//user handling here
				vSW3_UserHandling();
				usSW3OnTime = 100 - 30; 	//10msec*30 wait for Next repeat
				break;
			default:
				break;
		}
		usSW3OnTime++;
	}else{
		usSW3OnTime = 0;
	}
}

//****************************
// SW3 User Handling
//****************************
void vSW3_UserHandling(void)
{
	cSW3_flag = SWITCH_ON;
}

//****************************
// SW3 test
//****************************
char cSW3_ON(void)
{
	if(cSW3_flag == SWITCH_ON){
		cSW3_flag = SWITCH_OFF;
		return 1;
	}
	return 0;
}

//******************************************************************************
//   Switch SW4
//******************************************************************************
//****************************
// push Switch SW4 on/off check section
// this section is set at 10msec section.
// it has repeat.
//****************************
void vSW4_Check(void)
{

	static unsigned short usSW4OnTime = 0;

	if(!SW4){	//switch ON when an Input port is low.
		switch(usSW4OnTime)
		{
			case 0:
				//user handling here
				vSW4_UserHandling();
				break;
			case 100:					//10msec*100 wait after the first push
				//user handling here
				vSW4_UserHandling();
				usSW4OnTime = 100 - 30; 	//10msec*30 wait for Next repeat
				break;
			default:
				break;
		}
		usSW4OnTime++;
	}else{
		usSW4OnTime = 0;
	}
}

//****************************
// SW4 User Handling
//****************************
void vSW4_UserHandling(void)
{
	cSW4_flag = SWITCH_ON;
}

//****************************
// SW4 test
//****************************
char cSW4_ON(void)
{
	if(cSW4_flag == SWITCH_ON){
		cSW4_flag = SWITCH_OFF;
		return 1;
	}
	return 0;
}


//******************************************************************************
//   Switch Menu mode control 00
//
//   Description   : SW2, SW1 のメニューを変更する。
//   Precondition  :
//   Input         : SW2:値の変更
//                 : SW1:ステータスの遷移　HOUR->MIUTE->SET
//   Output        : LCD
//******************************************************************************
void vModeSwitchControl00(void)
{
	if (cSW4_ON()){
		vWAVE_close();				//stop WAVE playing
		CloseTimer4();				//stop SD card reading
		eModeSwitchStatus1 = eModeS1_clock;
	}
	switch (eModeSwitchStatus1) {
	case  	eModeS1_clock :		//時刻表示処理
		//★★ここに時間設定表示処理を入れる
		vGetsRTCC();						// RTCCモジュールから日付時間を取得する。
		eModeLcdL1Status = eModeL1_TimeOut;	//一定時間間隔起動
		eModeLcdL2Status = eModeL2_DateOut;	//一定時間間隔起動
		vLcd_L1buff_TimeSet();
		vLcd_L2buff_DateSet();
		if(cSW2_ON()){
			vSpeakTimeMessage();
		}

		//vPowerSave();
		break;

	case	eModeS1_ModeSelect_pre:

		iSelectNo01 = eModeS1_ModeSelect_jmp_wave_play;
		eModeSwitchStatus1++;
		break;

	case	eModeS1_ModeSelect:
		iSelectNo01 = iAddNumber(iSelectNo01, cSW2_ON(), eModeS1_ModeSelect_jmp_wave_play, eModeS1_ModeSelect_jmp_Chime_Disable);
		iSelectNo01 = iSubNumber(iSelectNo01, cSW3_ON(), eModeS1_ModeSelect_jmp_wave_play, eModeS1_ModeSelect_jmp_Chime_Disable);

		switch(iSelectNo01){
			case eModeS1_ModeSelect_jmp_Time_set:
				strcpy(bLCD_Lin2_buff, "set the Time?");
				break;
			case eModeS1_ModeSelect_jmp_Date_set:
				strcpy(bLCD_Lin2_buff, "set the Date?");
				break;
			case eModeS1_ModeSelect_jmp_Chime_Enable:
				strcpy(bLCD_Lin2_buff, "Chime Enable?");
				break;
			case eModeS1_ModeSelect_jmp_Chime_Disable:
				strcpy(bLCD_Lin2_buff, "Chime Disable?");
				break;
			case eModeS1_ModeSelect_jmp_wave_play:
			default:
				strcpy(bLCD_Lin2_buff, "play wave file?");
				iSelectNo01 = eModeS1_ModeSelect_jmp_wave_play;
				break;
		}

		vLcdOutLine(LCD_LINE2,bLCD_Lin2_buff);		//lcd2行目を出力
        vLcd_printAt(1,0);					//カーソルブリンク

		break;
	case	eModeS1_ModeSelect_jmp:		//上記の選択に従い処理分岐
		eModeSwitchStatus1 = iSelectNo01;
		break;
	case	eModeS1_ModeSelect_jmp_wave_play:
		eModeSwitchStatus1 = eModeS1_search_music_pre;
		break;
	case	eModeS1_ModeSelect_jmp_Time_set:
		eModeSwitchStatus1 = eModeS1_Time_set_pre;
		break;
	case	eModeS1_ModeSelect_jmp_Date_set:
		eModeSwitchStatus1 = eModeS1_Date_set_pre;
		break;
	case	eModeS1_ModeSelect_jmp_Chime_Enable:
		vSetChimeIndexs();					// 次の時報を設定する
//		RtccAlarmEnable();					// enable the alarm
		eModeSwitchStatus1 = eModeS1_clock;
		break;
	case	eModeS1_ModeSelect_jmp_Chime_Disable:
		vSetChimeOFF();
//		RtccAlarmDisable();					// disable the alarm
		eModeSwitchStatus1 = eModeS1_clock;
		break;
	}

}

//******************************************************************************
//   Switch Menu mode control 01
//
//   Description   : 時刻の設定用。
//                 : SW2, SW1 の操作において、時刻を設定する。
//   Precondition  :
//   Input         : SW2:値の変更
//                 : SW1:ステータスの遷移　HOUR->MIUTE->SET
//   Output        : LCD
//******************************************************************************
void vModeSwitchControl01(void)
{

	switch (eModeSwitchStatus1) {
	// Time set ---------------------------------------------------------------
	case  	eModeS1_Time_set_pre :
		//★★ここに時間設定表示処理を入れる
		eModeLcdL1Status = eModeL1_pose;		//一定時間間隔起動は停止
		vLcd_L1buff_TimeSet();
		vLcd_L2buff_DateSet();
		//★★ここにカーソル位置の設定を入れる
        vLcd_blinkON();						//カーソルブリンク
        vLcd_printAt(LCD_LINE1,6);
		eModeSwitchStatus1++;
		break;

	case  	eModeS1_1H_set :
		ucHour = iAddNumber(ucHour, cSW2_ON(), 0, 23);
		ucHour = iSubNumber(ucHour, cSW3_ON(), 0, 23);
		//★★ここに時間設定表示処理を入れる
		vLcd_L1buff_TimeSet();
		//★★ここにカーソル位置の設定を入れる
        vLcd_printAt(LCD_LINE1,6);
		break;

	case  	eModeS1_1M_set :
		ucMin = iAddNumber(ucMin, cSW2_ON(), 0, 59);
		ucMin = iSubNumber(ucMin, cSW3_ON(), 0, 59);
		//★★ここに時間設定表示処理を入れる
		vLcd_L1buff_TimeSet();
		//★★ここにカーソル位置の設定を入れる
        vLcd_printAt(LCD_LINE1,9);
		break;

	// Time setting ------------------------------------------------------------
	case  	eModeS1_Time_set_desision_pre :
		iSelectNo01 = eModeS1_Time_set;
		eModeSwitchStatus1++;
		break;

	case  	eModeS1_Time_set_desision :		//設定かキャンセルか決定する
		if (cSW2_ON()){
			iSelectNo01++;
		}
		switch(iSelectNo01){
		case eModeS1_Time_set_cancel:
			strcpy(bLCD_Lin1_buff, "Cancel?");
			break;
		case eModeS1_Time_set:
		default:
			strcpy(bLCD_Lin1_buff, "Time set?");
			iSelectNo01 = eModeS1_Time_set;
			break;
		}

		vLcdOutLine(LCD_LINE1,bLCD_Lin1_buff);		//lcd1行目へ出力
        vLcd_printAt(LCD_LINE1,9);
		break;

	case  	eModeS1_Time_set_desision_jmp :	//上記の選択に従い処理分岐
		eModeSwitchStatus1 = iSelectNo01;
		break;

	case  	eModeS1_Time_set :				//時間反映処理
		ucSec =0;
		vSetsRTCC_Time();					//時間をRTCCモジュールに設定する
		eModeSwitchStatus1 = eModeS1_clock;
		break;

	case  	eModeS1_Time_set_cancel :		//キャンセル処理
		eModeSwitchStatus1 = eModeS1_clock;
		break;

	// Date set ---------------------------------------------------------------
	case  	eModeS1_Date_set_pre :
		//★★ここに時間設定表示処理を入れる
		eModeLcdL2Status = eModeL2_pose;		//一定時間間隔起動は停止
		vLcd_L1buff_TimeSet();
		vLcd_L2buff_DateSet();
		//★★ここにカーソル位置の設定を入れる
        vLcd_blinkON();					//カーソルブリンク
        vLcd_printAt(LCD_LINE2,6);
		eModeSwitchStatus1++;
		break;

	case  	eModeS1_1Year_set :
		ucYear = iAddNumber(ucYear, cSW2_ON(), 0, 99);
		ucYear = iSubNumber(ucYear, cSW3_ON(), 0, 99);
		//★★ここに日付設定表示処理を入れる
		vLcd_L2buff_DateSet();
		//★★ここにカーソル位置の設定を入れる
        vLcd_printAt(LCD_LINE2,6);			//2行目, 7桁目
		break;

	case  	eModeS1_1Month_set :
		ucMonth = iAddNumber(ucMonth, cSW2_ON(), 1, 12);
		ucMonth = iSubNumber(ucMonth, cSW3_ON(), 1, 12);
		//★★ここに日付設定表示処理を入れる
		vLcd_L2buff_DateSet();
		//★★ここにカーソル位置の設定を入れる
        vLcd_printAt(LCD_LINE2,9);
		break;

	case  	eModeS1_1Day_set :
		ucDay = iAddNumber(ucDay, cSW2_ON(), 1, 31);
		ucDay = iSubNumber(ucDay, cSW3_ON(), 1, 31);
		//★★ここに日付設定表示処理を入れる
		vLcd_L2buff_DateSet();
		//★★ここにカーソル位置の設定を入れる
        vLcd_printAt(LCD_LINE2,12);
		break;

	// Date setting ------------------------------------------------------------
	case  	eModeS1_Date_set_desision_pre :
		iSelectNo01 = eModeS1_Date_set;
		eModeSwitchStatus1++;
		break;

	case  	eModeS1_Date_set_desision :			//設定かキャンセルか決定する
		if (cSW2_ON()){
			iSelectNo01++;
		}
		switch(iSelectNo01){
		case eModeS1_Date_set_cancel:
			strcpy(bLCD_Lin1_buff, "Cancel?");
			break;
		case eModeS1_Date_set:
		default:
			strcpy(bLCD_Lin1_buff, "Date set?");
			iSelectNo01 = eModeS1_Date_set;
			break;
		}

		vLcdOutLine(LCD_LINE1,bLCD_Lin1_buff);			//lcd1行目へ出力
        vLcd_printAt(LCD_LINE1,9);

		break;

	case  	eModeS1_Date_set_desision_jmp :		//上記の選択に従い処理分岐
		eModeSwitchStatus1 = iSelectNo01;
		break;

	case  	eModeS1_Date_set :				//時間反映処理
		ucSec =0;
		vSetsRTCC_Date();					//時間をRTCCモジュールに設定する
		eModeSwitchStatus1 = eModeS1_clock;
		break;

	case  	eModeS1_Date_set_cancel :		//キャンセル処理
		eModeSwitchStatus1 = eModeS1_clock;
		break;



//	default:
//		eModeSwitchStatus1 = eModeS1_clock;
	}


}

//******************************************************************************
//   Switch Menu mode control 02
//
//   Description   : 音楽再生用。
//                 : SW2, SW1, SW3, SW4 の操作で、音楽を再生する。
//   Precondition  :
//   Input         : SW2:値の変更
//                 : SW1:ステータスの遷移　play style1->2->3
//   Output        : LCD & wave output
//******************************************************************************
void vModeSwitchControl02(void)
{
	static int iMusicNo = 1;
	int iFileMaxNo;
	BYTE *fileName;

	switch (eModeSwitchStatus1) {
	case  	eModeS1_search_music_pre :
		vWAVE_close();						//stop WAVE playing
		CloseTimer4();						//stop SD card reading
		vPut_rc(pf_mount(&fs));
		vPut_rc(pf_mount(&fs));
		eModeSwitchStatus1++;
		break;

	case  	eModeS1_search_music_dir :		//& playing
		vWAVE_close();						//stop WAVE playing
		CloseTimer4();						//stop SD card reading
		if(bSearchDirAndPlayWave(iMusicNo, "/music", &iFileMaxNo, &fileName)){ //Playing the wave file.
			//waveファイルが見つからない場合(return!=ok)iMusicNoを初期値にし時計表示に戻る。
			iMusicNo = 1;
			eModeSwitchStatus1 = eModeS1_clock;
			break;
		}
		//取得出来たwave file 情報を表示する。
		xprintf("\r\n%d/%d %s", iMusicNo, iFileMaxNo, fileName);
		xsprintf(bLCD_Lin2_buff, " %d/%d %s  ", iMusicNo, iFileMaxNo, fileName);	//LCD buffer への出力
		eModeLcdL2Status = eModeL2_shift_L_pre;		//LCD shift 表示

		eModeSwitchStatus1++;
		break;

	case  	eModeS1_play_music :
		//music play 中に、swが押された時の処理
		if(cSW2_ON()){	// next music
			iMusicNo++;
			eModeSwitchStatus1 = eModeS1_search_music_dir;
		}
		if(cSW3_ON()){	// before music
			iMusicNo--;
			eModeSwitchStatus1 = eModeS1_search_music_dir;
		}
//		if(cSW4_ON()){	// stop music
//			vWAVE_close();				//stop WAVE playing
//			CloseTimer4();				//stop SD card reading
//			eModeSwitchStatus1 = eModeS1_clock;
//		}
		//music play の終了を判断し、終了したならば次のmusicをサーチして演奏する。
		switch (eWaveStatusC3) {
		case  	eWaveC3_idle:
		case  	eWaveC3_end:
			iMusicNo++;
			eModeSwitchStatus1 = eModeS1_search_music_dir;
			break;
		default:
			break;
		}
	}

}

//******************************************************************************
//   Add Number and return
//
//   Description   : 時刻日付の設定用。
//                 : 時間を受け取り、指定の範囲で加算して返信する。
//                 : 時間を加算した結果が、指定範囲を超えていた場合は最小値を返す。
//   Precondition  :
//   Input         : iNowTime:加算する元
//                 : iAddTime:加算値
//                 : iMinTime:指定の範囲、最小値
//                 : iMaxTime:指定の範囲、最大値
//   Output        : 算出した値
//******************************************************************************
int iAddNumber(int iNowTime, int iAddTime, int iMinTime, int iMaxTime)
{
	iNowTime = iNowTime + iAddTime;
	if(iNowTime > iMaxTime){
		return iMinTime;
	}else{
		return iNowTime;
	}

}

//******************************************************************************
//   Subtract Number and return
//
//   Description   : 時刻日付の設定用。
//                 : 時間を受け取り、指定の範囲で減算して返信する。
//                 : 時間を減算した結果が、指定範囲を超えていた場合は最大値を返す。
//   Precondition  :
//   Input         : iNowTime:減算する元
//                 : iAddTime:減算値
//                 : iMinTime:指定の範囲、最小値
//                 : iMaxTime:指定の範囲、最大値
//   Output        : 算出した値
//******************************************************************************
int iSubNumber(int iNowTime, int iSubTime, int iMinTime, int iMaxTime)
{
	iNowTime = iNowTime - iSubTime;
	if(iNowTime < iSubTime){
		return iMaxTime;
	}else{
		return iNowTime;
	}
}

//******************************************************************************
//   Sleep CPU
//
//   Description   : CPUの起動停止。
//                 : 次の割込みがあるまでCPU停止。
//   Precondition  :
//   Input         :
//                 : RTCC:1 minute interrupt
//                 : IO:Switch input interrupt
//   Output        : non
//******************************************************************************
void vPowerSave(void)
{
	if((eWaveStatusC3 == eWaveC3_idle) && (eModeSwitchStatus1 == eModeS1_clock)) {
		SD_POWER_DISEN();
		AUDIO_DISEN();

	//	RCONbits.BOR = 0;

		PowerSaveSleep();
	//	PowerSaveIdle();

		SD_POWER_EN();
	//	AUDIO_EN();
	}

}
