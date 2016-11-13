/*******************************************************************************
 *	RTCC処理
 *	c32の Peripheral Library を使用しています。
 *	新規:20130130
 *	修正:-
 ******************************************************************************/

#define CHIME_ON 1
#define CHIME_OFF 0

/*****************************
 * VARIABLES
 *****************************/
#if defined RTCC_LIB
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucWDay; 			// Week Day
	unsigned char ucHour;
	unsigned char ucMin;
	unsigned char ucSec;

	FILE_INDEXS ChimeIndexs;		// FILE_INDEXSはvWAVE_lib.hに定義あり
	int iChime_ON = CHIME_ON;
	char cFlag1Minute;
#else
	extern unsigned char ucYear;	//year
	extern unsigned char ucMonth;	//month
	extern unsigned char ucDay;		//day
	extern unsigned char ucWDay; 	// Week Day
	extern unsigned char ucHour;	//hour
	extern unsigned char ucMin;		//min
	extern unsigned char ucSec;		//sec

	extern char cFlag1Minute;
#endif

/*****************************
 * PROTOTYPES
 *****************************/
void vRTCC_init(void);
void vGetsRTCC_Time(void) ;				//RTCCモジュールから時間を取得する。
void vGetsRTCC_Date(void) ;				//RTCCモジュールから日付を取得する。
void vGetsRTCC(void);					//RTCCモジュールから日付時間を取得する。
void vSetsRTCC_Time(void);				//時間をRTCCモジュールに設定する
void vSetsRTCC_Date(void);				//日付をRTCCモジュールに設定する

unsigned char ucBCDtoHEX(unsigned char ucBCD);	//BCD(8bit)->HEX(8bit)変換
unsigned char ucHEXtoBCD(unsigned char ucHEX);	//BCD(8bit)<-HEX(8bit)変換

void vSetChimeOFF(void) ;						//
void vSetChimeIndexs(void);						//時報ファイルを読み込んで、次の時報の値を設定する。
void vCheckChimeIndexs(void);					//時報を鳴らす時間かチェックし、時間ならば時報するよう設定する。

