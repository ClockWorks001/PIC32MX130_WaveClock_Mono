/*******************************************************************************
 *	WAVE 処理
 *	新規:20121122
 *  Timer2 : PWMソースクロック
 *  Timer3 : サンプリング周波数作成
 *  Timer4 : SDカード読み込みタイミング作成
 *	修正:-
 ******************************************************************************/
#define WAVE_LIB

#include <plib.h>            /* Include to use PIC32 peripheral libraries      */
#include <sys/attribs.h>     /* For __ISR definition                          */
#include "xprintf.h"
#include "system.h"

#include "vWAVE_lib.h"
//#include "vUSART_Menu_lib.h"
#include "vERROR_CODE.h"
#include "vRTCC_lib.h"

/*****************************
 * 2byteの順序をひっくり返す。
 *****************************/
unsigned short usSwab_w(unsigned char *A){
	union SWAB_W_DATA{
		unsigned short usData;
		unsigned char ucData[2];
	} ;
	union SWAB_W_DATA B;
	B.ucData[1] = *(A);
	B.ucData[0] = *(++A);
	return B.usData;
}

/*****************************
 * 4byteの順序をひっくり返す。
 *****************************/
unsigned long ulSwab_dw(unsigned char *A){
	union SWAB_DW_DATA{
		unsigned long ulData;
		unsigned char ucData[4];
	} ;
	union SWAB_DW_DATA B;
	B.ucData[0] = *(A);
	B.ucData[1] = *(++A);
	B.ucData[2] = *(++A);
	B.ucData[3] = *(++A);
	return B.ulData;
}


/*****************************
 * initialization
 *****************************/
void vWAVE_init(void) {
	// (4)Assign PWM output Pin
	//  RPB7R(PORTB7)<==OC1 (L)
    RPB7R = 0b0101;
	//  RPB6R(PORTB6)<==OC4 (R)
    //RPB6R = 0b0101;

	// Timer2はPWM用のソースクロック
    // configure Timer 1 using internal clock, 1:1 prescale, 2Bit 256step
	//OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_1, 256 + 40);  // +40はフルスイングした時の音割れを防ぐための設定
	OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_1, 256 );  // +40はフルスイングした時の音割れを防ぐための設定
    // set up the timer interrupt with a priority of 2
	ConfigIntTimer2(T2_INT_OFF | T2_INT_PRIOR_2);

	// Enable OC | 16 bit Mode  | Timer2 is selected | MODULE MODE   , OCxRS Compare value, OCxR Compare value
	OpenOC1( OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE , 128, 128 );
	//OpenOC4( OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE , 128, 128 );

//	AUDIO_EN();

}

/*****************************
 * close PWM
 *****************************/
void vWAVE_close(void) {

	AUDIO_DISEN();

	// close OC1,4, Timer2
	CloseOC1();
	//CloseOC4();
	CloseTimer2();
	CloseTimer3();

	// (4)Disconect PWM output Pin
	//  RPB7R(PORTB7)<==OC1
    RPB7R = 0b0000;
	//  RPB6R(PORTB6)<==OC4
    //RPB6R = 0b0000;

	LATBbits.LATB7 = 0;
	LATBbits.LATB6 = 0;

	eWaveStatusC3 = eWaveC3_end;

}

/*****************************
 * initialization
 * TIMER3 is making Wave sampling rate
 *****************************/
void vTIMER3_init(unsigned int T3_Hz) {

    // configure Timer 1 using internal clock, 1:256 prescale
    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_1, PBCLK/T3_Hz );
    // set up the timer interrupt with a priority of 2
    ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_5);				// Highest intrupt level

}

//******************************************************************************
//   Intrupt TIMER3
//
//   Description   : PWM output by timing of sampling rate
//   Input         : sampling rate
//   Output        :
//******************************************************************************
void __ISR(_TIMER_3_VECTOR, ipl5) Intrupt_TIMER3(void)
{
	int n;
	unsigned short pwm_value;
	volatile unsigned int *ocxrs[2];	//型を合わせる為に、volatileを指定
	ocxrs[0] = &OC1RS;		//(L)
	//ocxrs[1] = &OC4RS;	//(R)
// ********************************
// 1.Clear the Timer3 interrupt Flag
// ********************************
	IFS0bits.T3IF = 0;

	//演奏の終わりをチェック
	if (SdFF.ulDataByte){
		SdFF.ulDataByte = SdFF.ulDataByte - SdFF.iBlockSize;
	} else {
		//演奏終わり
		SdFF.iWaveBusy = 0;		// 1:idle
		return;
	}

	pwm_value = usCalPwmValue();
	if (SdFF.iChannel==2){
		SdFF.di = SdFF.di ++;
		pwm_value = (pwm_value +  usCalPwmValue())/2;
	}
	*ocxrs[0] = pwm_value;

	//next pointer
	SdFF.ri = (SdFF.ri + SdFF.iBlockSize) % SD_BUFFER_SIZE;
	SdFF.di = SdFF.di ++;
	if(SdFF.ri == 0){
		SdFF.di = 0;
		if(SdFF.li == 0){
			SdFF.li = 1;
		}else{
			SdFF.li = 0;
		}
	}

}

//******************************************************************************
//   Intrupt TIMER3
//
//   Description   : PWM control by timing of sampling rate
//   Input         : SdFF
//   Output        : PwmValue
//******************************************************************************
unsigned short usCalPwmValue(void) {
	//データを各チャンネル（PWM出力の値）へセット
	if (SdFF.iLength == 16) {
		//set PCM data to PWM (16bit 2ch)
		return SdFF.uWV.sLine[SdFF.li][SdFF.di] / 0x100 + 128;
	}else{
		//set PCM data to PWM (8bit 2ch)
		return SdFF.uWV.bLine[SdFF.li][SdFF.di] ;
	}
}

/*****************************
 * initialization
 * TIMER4 is timing for reading SD card
 *****************************/
void vTIMER4_init(void) {
// Let compile time pre-processor calculate the PR4 (period)
//#define PBCLK				(SYS_FREQ / PB_DIV)	// Peripheral Clock
#define T4_PRESCALE				256
#define T4_TOGGLES_PER_SEC		4000			// =4000hz

    // configure Timer4 using internal clock, 1:32 prescale, PRreg value
    OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_256, PBCLK/T4_PRESCALE/T4_TOGGLES_PER_SEC );
    // set up the timer interrupt with a priority of 2
    ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_3);				// Middle intrupt level

}

//******************************************************************************
//   Intrupt TIMER4
//
//   Description   : read next file data
//   Input         : reading SD card
//   Output        :
//******************************************************************************
void __ISR(_TIMER_4_VECTOR, ipl3) Intrupt_TIMER4(void)
{
    // 1.Clear the TIMER4 interrupt Flag
	IFS0bits.T4IF = 0;
	vReadNextSector();
}

//******************************************************************************
//   Read next Sector
//
//   Description   : read next file Sector
//   Input         : reading SD card
//   Output        : SdFF
//******************************************************************************
void vReadNextSector(void)
{

	//------------------------------------------------
	// fileが最後まで読まれたかチェック
	if (fs.fptr >= fs.fsize || fs.fptr == 0) {
//		xputs("\r\nEND SD READ\r\n>");		//割込みの中で出力するのは問題ありのようだ。
//		CloseTimer4();						// 割込みの中でcloseするのは注意。処理が途中で止まるようだ。
		return ;
	}

	//------------------------------------------------
	// 次のバッファにデータを読み込んで良いかチェック
	// li	:read line index
	// buffi:SD card read and stock buffer index
	// 次に読み込む予定のバッファインデックス(buffli)をまだ読んでいる(li)ならば
	// 何もしないが、読んでいるライン(li)が変わったら、SD cardから読み込む。
	if( SdFF.li != SdFF.buffli ){
		res = pf_read(SdFF.uWV.bLine[SdFF.buffli], SD_BUFFER_SIZE, &s1);
		if (res != FR_OK) {		//ERROR handling
			vPut_rc(res);
			return ;
		}
		// set the next SD data setting line pointer
		// 次のsecterを格納するバッファインデックスを前もって設定しておく。
		SdFF.buffli =SdFF.li;
	}
	return ;
}


//******************************************************************************
//   Get Wave Property
//
//   Description   :
//     1.open the Wave file.
//     2.check the file header.
//     3.get the Wave property.
//   Precondition  :
//     The SD card must have been initialized & mount by "pf_mount".
//   Input         : SD card
//   Parameters    :
//     BYTE *WaveFileName : wave file name.
//   Returns       :
//     The return status from file system.
//******************************************************************************

BYTE bGetWaveProperty(BYTE *WaveFileName) {
	int i;
	//----------------------------------------------------------------------
	// fi - Mount the volume //
	//	res = pf_mount(&fs);
	//	if (res != FR_OK) {
	//		vPut_rc(res);
	//		return res;
	//	}
	// fo <file> - Open a file //
	i = 0;
	do{
		i++;
		if (i > 10) {
			vPut_rc(res);
			return res;
		}
		res = pf_open(WaveFileName);
	}while(res != FR_OK) ;
	xputs("\r\npf_opne OK");
	// read a file
	i = 0;
	do{
		i++;
		if (i > 10) {
			vPut_rc(res);
			return res;
		}
		res = pf_read(SdFF.uWV.bLine[0], sizeof(SdFF.uWV.bLine[0]), &s1);
	}while(res != FR_OK) ;
	xputs("\r\npf_read OK");

	//----------------------------------------------------------------------

	if(strncmp(&SdFF.uWV.bLine[0][0],"RIFF",4)!=0 || strncmp(&SdFF.uWV.bLine[0][8],"WAVE",4)!=0 ){ //strncmpram2pgm
		xputs("\r\nNO WAV FILE");
		return ERROR99; //eror
	}
	SdFF.iFmtByte = SdFF.uWV.bLine[0][16];		//fmt byte のデータサイズ
	SdFF.iChannel = SdFF.uWV.bLine[0][22];		//mono=1 stereo=2
	SdFF.iSamplingRate = ulSwab_dw(&SdFF.uWV.bLine[0][24]);		//44.1khz=44AC 22khz=2256 16khz=803E
	SdFF.iBlockSize = SdFF.uWV.bLine[0][32];	//ブロックサイズ (Byte/sample×チャンネル数)
	SdFF.iLength  = SdFF.uWV.bLine[0][34];		//bit length 16 or 8
	for (i = 36; i < fs.fsize; i++){
		if(strncmp(&SdFF.uWV.bLine[0][i],"data",4) == 0 ){ //strncmpram2pgm
			i = i + 4;
			SdFF.ulDataByte = ulSwab_dw(&SdFF.uWV.bLine[0][i]);
			SdFF.ri = i + 4  ;			// set buffer read start point
			break;
		}
	}

	//open wave logic
	SdFF.di = SdFF.ri / SdFF.iBlockSize / SdFF.iChannel ;	// set data start point
	SdFF.li = 0;			// set the reading out line pointer
	SdFF.buffli = 1;		// set the next SD data setting line pointer

	xprintf("\r\nFMT_BYTE=%u", SdFF.iFmtByte);
	xprintf("\r\nCH=%u", SdFF.iChannel);
	xprintf("\r\nFQ=%luHz", SdFF.iSamplingRate);
	xprintf("\r\nLEN=%uBits", SdFF.iLength);
	xprintf("\r\nBLOCK=%uBytes", SdFF.iBlockSize);
	xprintf("\r\nDATABYTE=%uBytes", SdFF.ulDataByte);
	xputs("\r\n>");

	return FR_OK;

}

//******************************************************************************
//   Search Directory And Play Wave (return:res)
//
//   Description   : ディレクトリをサーチし、指定されたn番目のファイル名を取得する
//                 : 指定されたn番目のwaveファイルの演奏をスタートさせる。
//                 : 注意！並びはファイル名順。
//     1.open the Directory.
//     2.serch the Directory by pFileNo.
//     3.get a line which inclede a wave file name for playing.
//     4.start the Wave playing.
//   Precondition  :
//     The SD card must have been initialized & mount by "pf_mount".
//   Input         : SD card
//   Parameters    :
//     int  iFileNo		: Index.
//     BYTE *pDirName	: Directory name.
//     int* iFileMaxNo  : output File No in the Directory.
//     BYTE **pFileName	: output File name.
//   Returns       :
//     The return status from file system.
//     BYTE bWaveFileNames[]
//******************************************************************************
BYTE bSearchDirAndPlayWave(int iFileNo, BYTE *pDirName, int *iFileMaxNo, BYTE **pReturnFileNames ) {
//BYTE bSearchDirAndPlayWave(int iFileNo, BYTE *pDirName) {
		int  ifileNameLength1;

		strcpy(bWaveFileNames, pDirName);
		ifileNameLength1 = strlen(bWaveFileNames);

		res = pf_opendir(&dir, bWaveFileNames);
		if (res) {
			vPut_rc(res);
			return res;
		}
		s1 = 0;
		for(;;) {
			res = pf_readdir(&dir, &fno);
			if (res != FR_OK) {
				vPut_rc(res);
				return res;
			}
//			xprintf("\r\nFile name is %s ", fno.fname);
			if (!fno.fname[0]){		//wav file search が終わった場合の処置
				if(s1 == 0){
					xprintf("\r\nNo Music Files %s ", bWaveFileNames);
					return ERROR10;
				}
				if(s1 < iFileNo){
					xprintf("\r\nEnd of Music Files %s ", bWaveFileNames);
					return ERROR11;
				}
//				xputs("\r\nEnd of Music Files");
				break;
			}
			if(strstr(fno.fname, ".wav") || strstr(fno.fname, ".WAV")){
				s1++;
				if(s1 == iFileNo){
					strncat(bWaveFileNames, "/", 1);
					strncat(bWaveFileNames, fno.fname, 13);
					bWaveFileNames[ifileNameLength1+15] = '\0';
					xprintf("\r\nFile name is %s", bWaveFileNames);

//					vWavePlayStart(bWaveFileNames) ;
//					break;
				}
			}
		}
		*iFileMaxNo = s1;				// return 総waveファイル数
		*pReturnFileNames = bWaveFileNames;	// return file name

//		xprintf("\r\n%u item(s) ", s1);
		vWavePlayStart(bWaveFileNames);
		return NO_ERROR;
}

//******************************************************************************
//   Search List And Get FileNames (return:res)
//
//   Description   : リストファイルを読み込み、インデックスで指定された１行を抽出する
//                 : 指定された1行を、指定のバッファに格納して返信する。
//     1.open the List file.
//     2.serch the List file by pListIndex.
//     3.get a line which inclede some wave file name for playing.
//     4.return the Wave file names.
//   Precondition  :
//     The SD card must have been initialized & mount by "pf_mount".
//   Input         : SD card
//   Parameters    :
//     BYTE *pListIndex : Index.
//     BYTE *pListName  : List file name.
//   Returns       :
//     The return status from file system.
//     BYTE **pReturnFileNames
//     BYTE bWaveFileNames[]
//******************************************************************************
BYTE bSearchListAndGetFileName(BYTE *pListIndex, BYTE *pListName, BYTE **pReturnFileNames, FILE_INDEXS *pIdxs) {
	int i, j;
	BYTE byte1;
	BYTE index4[5];
	//1ライン読み込み
	enum eReadStatus {
		eRS_Start,
		eRS_GetIndex,
//		eRS_IndexCheck,
		eRS_PicUp,
		eRS_skip
	} eRS_Status;

	vWAVE_close();						//stop WAVE playing
	CloseTimer4();						//stop SD card reading
	
	//----------------------------------------------------------------------
	// fi - Mount the volume //
	res = pf_mount(&fs);
	if (res != FR_OK) {
		vPut_rc(res);
		return res;
	}
	// fo <file> - Open the List file //
	//res = pf_open(ptr0);
	res = pf_open(pListName);
	if (res != FR_OK) {
		vPut_rc(res);
		return res;
	}
	// read the List file
	res = pf_read(SdFF.uWV.bLine[0], sizeof(SdFF.uWV.bLine[0]), &s1);
	//----------------------------------------------------------------------

	eRS_Status = eRS_Start;
	SdFF.ulDataByte = fs.fsize;
	SdFF.ri = 0;
	SdFF.di = 0;
	SdFF.li = 1;			// 次のfor文の最初で、ri=0の時にliが0となるように
	SdFF.buffli = 1;		// 次の SD data の読み込み位置を設定。

	for (i=0; i < WAVE_LIST_BUFFER_SIZE; bWaveFileNames[i++] = '\0'); //clear the buffer
	strcpy(pIdxs->bIndexNxt, "9999");		//比較用の初期値設定
	strcpy(pIdxs->bIndexMin, "9999");		//比較用の初期値設定
	strcpy(pIdxs->bIndexMax, "0000");		//比較用の初期値設定

	for (i=0; i < fs.fsize; i++){
		// Pointer
		SdFF.ri = i % SD_BUFFER_SIZE;
		// Next Pointer
		if (SdFF.ulDataByte){
			SdFF.ulDataByte --;
		}
		if(SdFF.ri == 0){
			if(SdFF.li == 0){
				SdFF.li = 1;
			}else{
				SdFF.li = 0;
			}
			vReadNextSector();
		}
		byte1 = SdFF.uWV.bLine[SdFF.li][SdFF.ri];

		switch(eRS_Status){
		case eRS_Start:
			//先頭のspaceや\r\nをスキップし、先頭の1文字を取得する。
			switch(byte1) {
			case '\r':	// CR
			case '\n':	// LF
			case '\t':	// tab
			case ' ':	// space
				break;
			default:
				j = 0;
				//bWaveFileNames[j] = byte1;
				index4[j] = byte1;
				eRS_Status++;
				break;
			}
			break;
		case eRS_GetIndex:
			//Index pick up
			switch(byte1) {
			case '\r':	// CR
			case '\n':	// LF
				eRS_Status = eRS_Start; 
				break;
			default:
				j++;
				index4[j] = byte1;
				if ( j < 3){
					break;
				}else{
					j++;
					index4[j] = '\0';
					j = 0;
					if(strncmp(index4, pListIndex ,4) == 0){ //先頭4文字の時間が一致したら
						eRS_Status = eRS_PicUp;
					}else{
						eRS_Status = eRS_skip;
					}

					//時報用に次のindexを取得する
					if(strcmp(index4, pIdxs->bIndexMin) < 0){	//最小のチェック。
						strcpy(pIdxs->bIndexMin, index4);		//小さいなら小さいのを設定
					}
					if(strcmp(index4, pIdxs->bIndexMax) > 0){	//最大のチェック
						strcpy(pIdxs->bIndexMax, index4);		//大きいなら大きいのを設定
					}
					if((strcmp(index4, pListIndex) > 0) && (strcmp(index4, pIdxs->bIndexNxt) < 0)){	//次に大きいか
						strcpy(pIdxs->bIndexNxt, index4);		//次に大きいのを設定
					}

				}
				break;
			}
			break;		
		case eRS_PicUp:
			//1 line pick up
			switch(byte1) {
			case '\r':	// CR
			case '\n':	// LF
				eRS_Status = eRS_Start;
				break;
			case '\t':	// tab 、tabの時はspaceに変更して次のdefault処理を行う。
				byte1 = ' ';
			default:
				if ( j < WAVE_LIST_BUFFER_SIZE){
					bWaveFileNames[j] = byte1;
					j++;
				}else{
					eRS_Status = eRS_skip;
				}
			}
			break;
		case eRS_skip:
			switch(byte1) {
			case '\r':	// CR
			case '\n':	// LF
				eRS_Status = eRS_Start;
			default:
				break;
			}
			break;
		default:
			break;
		}

	}
WAVE_LIST_START:
	CloseTimer4();						//stop SD card reading of the list file
	strcpy(*pReturnFileNames, bWaveFileNames);
	if(strcmp(pIdxs->bIndexNxt, "9999") == 0){		//Nextが取得できなかったら
		strcpy(pIdxs->bIndexNxt,pIdxs->bIndexMin);	//ふりだしに戻る。
	}

	return FR_OK;

}

/*****************************
 * Wave Play by Start
 *****************************/
void vWavePlayStart(BYTE *ptr1) {
	strcpy(bWaveFileNames, ptr1);
	bWaveFileName_ptr = bWaveFileNames;
//	xprintf("\r\nvWavePlayStart>%s", bWaveFileName_ptr);
	eWaveStatusC3 = eWaveC3_FileSystemOpen;
}

/*****************************
 * speak Time message　
 *****************************/
void vSpeakTimeMessage(void) {
	FILE_INDEXS fileIndexs;
	static BYTE bTimeMessage[125];
	BYTE bTime[5];
	BYTE *bTimeMessage_ptr = bTimeMessage;
	vGetsRTCC();			// RTCCモジュールから日付時間を取得する。
	xsprintf(bTime, "%02d%02d", ucHour, ucMin);
	xprintf( "\n\rTime is %s", bTime);
	if(bSearchListAndGetFileName(bTime, "TimeTone.txt", &bTimeMessage_ptr, &fileIndexs) == 0){
			xprintf( "\n\rIndexs Min:%s Max:%s Next:%s ", fileIndexs.bIndexMin, fileIndexs.bIndexMax, fileIndexs.bIndexNxt);
			vWavePlayStart(bTimeMessage);		//WAVE FILE LISTを渡してSTART
	}

}


//******************************************************************************
//   Function Name : Wave Play Status Control
//******************************************************************************
void vWavePlayControl01(void) {

	switch (eWaveStatusC3) {
	case  	eWaveC3_idle :
		vWAVE_close();						//stop WAVE playing
		break;

	case  	eWaveC3_FileSystemOpen :
		// fi - Mount the volume //
		res = pf_mount(&fs);
//		if (res != FR_OK) {
			vPut_rc(res);
//		}
		eWaveStatusC3++;	//PlayList_checkへ
		break;

	case  	eWaveC3_NameCheck :
//		vWAVE_close();						//stop WAVE playing
		CloseTimer4();						//stop SD card reading

		while (*bWaveFileName_ptr == ' ') bWaveFileName_ptr++;	//spaceの読み飛ばし
		if (*bWaveFileName_ptr == '\0') {
			eWaveStatusC3 = eWaveC3_end;
			break;
		}
		xprintf("\r\nWave Play Start>%s", bWaveFileName_ptr);
		eWaveStatusC3 = eWaveC3_start;	//waveの再生
		break;

	case  	eWaveC3_start :
		if (bGetWaveProperty(bWaveFileName_ptr) != FR_OK ){
			xputs("\r\nERROR WAVE PLAY\r\n>");
			eWaveStatusC3 = eWaveC3_next;
			break;
		}

		vWAVE_init();
		SdFF.iWaveBusy = 1;		// 1:busy
		vTIMER3_init(SdFF.iSamplingRate);	// start wave playing
		vTIMER4_init();						// start SD card next reading

		eWaveStatusC3++;					//モードを次のステータスへ遷移
		AUDIO_EN();
		break;

	case  	eWaveC3_busy :
//		AUDIO_EN();
		if(SdFF.iWaveBusy) break;			//wait until idle
		eWaveStatusC3++;					//モードを次のステータスへ遷移
		AUDIO_DISEN();
		break;

	case  	eWaveC3_next :
		while (*bWaveFileName_ptr != ' ' && *bWaveFileName_ptr != '\0') bWaveFileName_ptr++;	//次の曲・フレーズへ
		eWaveStatusC3 = eWaveC3_NameCheck;
		break;

	case  	eWaveC3_end :
		xputs("\r\nEND WAVE PLAY\r\n>");
		vWAVE_close();						//stop WAVE playing
		CloseTimer4();						//stop SD card reading
		eWaveStatusC3 = eWaveC3_idle;		//モードを次のステータスへ遷移
		break;

	default:
		eWaveStatusC3 = eWaveC3_end;			//モードをidle状態へ
		break;
	}

}


