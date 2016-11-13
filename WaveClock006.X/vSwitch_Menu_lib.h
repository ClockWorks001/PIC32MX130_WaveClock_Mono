/*************************************************
*  Switch_Menu処理ヘッダファイル
*    vPushSwitch_init()  ----- 初期化
*    vSW2_Check() ----- SW2_ チェック＆repeat処理
*    vSW2_UserHandling() ----- SW2_が押された時のユーザ処理を記述する
*    char cSW2_ON() ----- SW2_の状態を返信する。フラグをクリアする。
*    vSW1_Check() ----- SW1_ チェック＆repeat処理
*    vSW1_UserHandling() ----- SW2_が押された時のユーザ処理を記述する
*************************************************/

//pushbuttons define
#define SW1		PORTBbits.RB2	//bring forward the Switch menu status
#define SW2		PORTBbits.RB3	//for Number Addition
#define SW3		PORTAbits.RA2	//for Number Subtraction
#define SW4		PORTAbits.RA3	//for cancellation
#define SWITCH_ON		1
#define SWITCH_OFF		0
#define FILE_NAME_BUFFER_SIZE 30			//File Name buffer size

/*****************************
** 定数変数定義
*****************************/
#if defined SWITCH_MENU_LIB
	char cSW2_flag = 0;		// global変数はstaticは、要らない
	char cSW3_flag = 0;		// global変数はstaticは、要らない
	char cSW4_flag = 0;		// global変数はstaticは、要らない
	int iSelectNo01;		// 制御selectする場合の番号保持用

	BYTE bFileName_buff[FILE_NAME_BUFFER_SIZE + 1];	//File Name buffer
	unsigned char ucMin02, ucHour02;	//時刻設定用

	enum eModeS1 {
		eModeS1_clock,			// idle

		// Switch Main Menu control
		eModeS1_ModeSelect_pre,
		eModeS1_ModeSelect,
		eModeS1_ModeSelect_jmp,
		eModeS1_ModeSelect_jmp_wave_play,
		eModeS1_ModeSelect_jmp_Time_set,
		eModeS1_ModeSelect_jmp_Date_set,
		eModeS1_ModeSelect_jmp_Chime_Enable,
		eModeS1_ModeSelect_jmp_Chime_Disable,

		// Time Date set Menu control
		eModeS1_Time_set_pre,
		eModeS1_1H_set,
		eModeS1_1M_set,
		eModeS1_Time_set_desision_pre,
		eModeS1_Time_set_desision,
		eModeS1_Time_set_desision_jmp,
		eModeS1_Time_set,
		eModeS1_Time_set_cancel,

		eModeS1_Date_set_pre,
		eModeS1_1Year_set,
		eModeS1_1Month_set,
		eModeS1_1Day_set,
		eModeS1_Date_set_desision_pre,
		eModeS1_Date_set_desision,
		eModeS1_Date_set_desision_jmp,
		eModeS1_Date_set,
		eModeS1_Date_set_cancel,

		// Wave Play Menu control
		eModeS1_search_music_pre,
		eModeS1_search_music_dir,
		eModeS1_play_music,

		// other control
		eModeS1_sleep,
		eModeS1_beep,

		eModeS1_end
	};
	enum eModeS1 eModeSwitchStatus1;


#else
	//extern char ucTestCount = 0;
#endif


/*****************************
*  プロトタイプ定義ファイル
*****************************/
void vPushSwitch_init(void);
void vSW2_Check(void);
void vSW2_UserHandling(void);
char cSW2_ON(void);
void vSW1_Check(void);
void vSW1_UserHandling(void);
void vSW3_Check(void);
void vSW3_UserHandling(void);
char cSW3_ON(void);
void vSW4_Check(void);
void vSW4_UserHandling(void);
char cSW4_ON(void);
void vModeSwitchControl00(void);
void vModeSwitchControl01(void);
void vModeSwitchControl02(void);

int iAddNumber(int iNowTime, int iAddTime, int iMinTime, int iMaxTime);
int iSubNumber(int iNowTime, int iSubTime, int iMinTime, int iMaxTime);
void vPowerSave(void);


