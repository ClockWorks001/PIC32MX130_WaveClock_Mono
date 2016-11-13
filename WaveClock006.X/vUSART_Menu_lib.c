/*******************************************************************************
 *	USART_Menu処理
 *	新規:20130130
 *	修正:-
 ******************************************************************************/
#define USART_MENU_LIB

#include <plib.h>            /* Include to use PIC32 peripheral libraries      */
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
//#include <stdio.h>
#include "xprintf.h"

#include "vUSART_CMND_lib.h"
#include "vRTCC_lib.h"
#include "vWAVE_lib.h"
//#include "vTimer1_lib.h"
#include "vERROR_CODE.h"
#include "vUSART_Menu_lib.h"
#include "integer.h"

#define MSG_LINE01_MAX 13					//msg line 01
char cMsgLine01;
const BYTE bMsg01[] = {
	"\r\n+Input your command!\0"			//入力表示コマンドモード
	"\r\n+(DEL)->clear the command\0"		//コマンドクリア
	"\r\n+(ESC)->exit or clear\0"			//
	"\r\n+Dyymmdd->Date setting\0"			//
	"\r\n+Thhmmss->Time setting\0"			//
	"\r\n+G->Time Output\0"					//時間の表示
	"\r\n+fi ->Fs initialize\0"				//
	"\r\n+fo xxxx.txt->file open\0"							//
	"\r\n+fd ->Read out 128 bytes & dump\0"					//
	"\r\n+fw <len> <val> ->Write data to the file\0"		//
	"\r\n+fp xxMessegexx ->Write a Messege to the file\0"	//
	"\r\n+fe ->Move file pointer of the file\0"				//
	"\r\n+fl [<path>/<path>...] ->Directory listing\0"		//
};


//#pragma code
/*****************************
 * initialization
 *****************************/
void vUSART_menu_init(void) {
	eModeStatusC2 = eModeC2_menu_init ;
	vCMND_init();
	//xputs("\r\n>");					//改行&入力指示プロンプト
	vXputs_return();
}

/*****************************
 * Menu mode control
 *****************************/
void vModeUartControl11(void) {

	switch (eModeStatusC2) {
	case  	eModeC2_menu_msg0 :
		cMsgLine01=0;							//行表示用ポインタを1行目設定へ初期化しておく
		eModeStatusC2++;						//モードを次のステータスへ遷移
		break;

	case  	eModeC2_menu_msg1 :
		vMessage_0_ModeStart01();				//初期メッセージ出力
		break;

	case  	eModeC2_menu_init :
		//vCMND_init();
		//xputs("\r\n>");						//改行&入力指示プロンプト
		vXputs_return();						//改行&入力指示プロンプト
		eModeStatusC2++;						//モードを次のステータスへ遷移
		break;

	case  	eModeC2_vGetsCMND :
		switch(vGetsCMND()) {					//コマンド文字列取得->cCmdBuf格納
		case eUSART_CMND_Exec:
			eModeStatusC2 = eModeC2_vExecCmd;
			break;
		case eUSART_CMND_Esc:
			eModeStatusC2 = eModeC2_menu_msg0;
			break;
		case eUSART_CMND_Del:
			eModeStatusC2 = eModeC2_menu_init;
			break;
		default:								//コマンド入力まち
			break;
		}
		break;

	case  	eModeC2_vExecCmd:					//Command selection
		switch(cCmdBuf[0]) {
		case 'T':								//時計設定コマンド
		case 't':								//時計設定コマンド
			vCommand_TimeSet();
			vSetChimeIndexs();					// 次の時報を設定する
			eModeStatusC2 = eModeC2_menu_init;
			break;
		case 'D':								//日付設定コマンド
		case 'd':								//日付設定コマンド
			vCommand_DateSet();
			eModeStatusC2 = eModeC2_menu_init;
			break;
		case 'g':
		case 'G':
			vShowNowTimeMessage();
			eModeStatusC2 = eModeC2_menu_init;
			break;
		case 's':
		case 'S':
			vSpeakTimeMessage();
			eModeStatusC2 = eModeC2_menu_init;
			break;
		case '?':								//メニュー
			eModeStatusC2 = eModeC2_menu_msg0;
			break;
		case '\r':								//コマンド入力まち
			eModeStatusC2 = eModeC2_menu_init;
			break;

			//pFatFS moniter////////////////////////////////////////////////
		case 'f':
			vCommand_FatFs();
			eModeStatusC2 = eModeC2_menu_init;
			break;
			//pFatFS moniter////////////////////////////////////////////////

			//wave control//////////////////////////////////////////////////
		case 'w':
			vModeC2_Wave();
			eModeStatusC2 = eModeC2_menu_init;	//wave close check
			break;
			//pFatFS moniter////////////////////////////////////////////////

		default:								// コマンドエラー
			eModeStatusC2 = eModeC2_Command_error;
			break;
		}
		break;

	case  	eModeC2_Command_error:
		// コマンド該当なし
//		if(UARTTransmitterIsReady(UART2)) {
			xputs("\r\n? Unrecognized command format");	// 入力エラー
//		}
		eModeStatusC2 = eModeC2_menu_init;
		break;

	default:
		eModeStatusC2 = eModeC2_menu_init;
	}

}

/*****************************
 * command mode start message
 * ◆コマンドモード開始メッセージ
 *****************************/
void vMessage_0_ModeStart01(void) {
	const BYTE *ptr1;					//型を合わせる為に、constを指定
	ptr1 = bMsg01;
	int i;

	if(cMsgLine01 < MSG_LINE01_MAX) {	//最後の行'>'となるまで1行づつ表示
		for(i=0; i < cMsgLine01; i++){
			while(*ptr1 != '\0') *ptr1++;	//文字の読み飛ばし
			*ptr1++;
		}
		xprintf(ptr1);					//入力表示コマンドモード
		cMsgLine01++;					//1行表示したら次の行へ
	} else {
		cMsgLine01=0;					//使い終わった行表示用ポインタを1行目へ初期化しておく
		eModeStatusC2 ++;				//表示が終わったら次のステータスへ
	}
}


/*****************************
 * Timer Setting
 *****************************/
void vCommand_TimeSet(void) {
	char str[3];

	//コマンドフォーマットチェック *hhmmss
	vComandFormatCheck_7Digit();

	switch(cCmdBuf[0]) {
	case 'T':							//時計設定コマンド
	case 't':							//時計設定コマンド
		//ascii->numeric and set to the time
		str[0] = cCmdBuf[1];
		str[1] = cCmdBuf[2];
		str[3] = 0x00;
		ucHour = (unsigned char)atoi(str);

		str[0] = cCmdBuf[3];
		str[1] = cCmdBuf[4];
		ucMin  = (unsigned char)atoi(str);

		str[0] = cCmdBuf[5];
		str[1] = cCmdBuf[6];
		ucSec  = (unsigned char)atoi(str);

		vSetsRTCC_Time();				//時間をRTCCモジュールに設定する

//		if(UARTTransmitterIsReady(UART2)) {
			xputs("\n\rTime Setting Finish!");
//		}
		vShowNowTimeMessage();					//設定時間の再表示
		break;

	default:
		xputs("\r\n? Format Error.");	//入力エラー
		break;
	}

}
/*****************************
 * Date Setting
 *****************************/
void vCommand_DateSet(void) {
	char str[3];

	//コマンドフォーマットチェック *hhmmss
	vComandFormatCheck_7Digit();

	switch(cCmdBuf[0]) {
	case 'D':							//日付設定コマンド
	case 'd':							//日付設定コマンド
		//ascii->numeric and set to the time
		str[0] = cCmdBuf[1];
		str[1] = cCmdBuf[2];
		str[3] = 0x00;
		ucYear = (unsigned char)atoi(str);

		str[0] = cCmdBuf[3];
		str[1] = cCmdBuf[4];
		ucMonth  = (unsigned char)atoi(str);

		str[0] = cCmdBuf[5];
		str[1] = cCmdBuf[6];
		ucDay  = (unsigned char)atoi(str);

		vSetsRTCC_Date();				//時間をRTCCモジュールに設定する

//		if(UARTTransmitterIsReady(UART2)) {
			xputs("\n\rDate Setting Finish!");
//		}
		break;

	default:
		xputs("\r\n? Format Error.");	// 入力エラー
		break;
	}

}

/*****************************
 * Show Now Time Message
 *****************************/
void vShowNowTimeMessage(void) {
	vGetsRTCC();			// RTCCモジュールから日付時間を取得する。
//	if(UARTTransmitterIsReady(UART2)) {
		xprintf( "\n\rTime is %02d:%02d:%02d", ucHour, ucMin, ucSec);
		xprintf( "\n\rDate is %02d/%02d/%02d", ucYear, ucMonth, ucDay);
//	}
}

/*****************************
 * Comand format check 7digit
 *****************************/
void vComandFormatCheck_7Digit(void) {
	char i;
	for( i=1 ; i<7 ; i++) {
		if(!isdigit(cCmdBuf[i])) {
			cCmdBuf[0] = '?';
		}
	}
}

/*****************************
 * Timer Setting Error message
 *****************************/
void vModeC2_T_error(void) {

}

/*****************************
 * FatFs
 *****************************/
void vCommand_FatFs(void) {
	ucPtr1 = &cCmdBuf[2];
	switch(cCmdBuf[1]) {
	case 'i' :	/* fi - Mount the volume */
		vPut_rc(pf_mount(&fs));
		vPut_rc(pf_mount(&fs));
		break;

	case 'o' :	/* fo <file> - Open a file */
		while (*ucPtr1 == ' ') ucPtr1++;
		vPut_rc(pf_open(ucPtr1));
		break;
#if _USE_READ
	case 'd' :	/* fd - Read the file 128 bytes and dump it */
		ofs = fs.fptr;
		res = pf_read(SdFF.uWV.bLine[0], sizeof(SdFF.uWV.bLine[0]), &s1);
		if (res != FR_OK) {
			vPut_rc(res);
			break;
		}
		ucPtr1 = SdFF.uWV.bLine[0];
		//xputs("\r\n");
		vXputs_return();						//改行&入力指示プロンプト
		while (s1) {
			s2 = (s1 >= 16) ? 16 : s1;
			s1 -= s2;
			xput_dump((BYTE*)ucPtr1, ofs, s2, DW_CHAR);
			ucPtr1 += 16;
			ofs += 16;
		}
		break;

#endif
#if _USE_WRITE
	case 'w' :	/* fw <len> <val> - Write data to the file */
		// pf_writeは 512byte単位（セクタ単位）でのwriteのみ
		// 一旦セクタをnullクリアしてから、先頭からデータを書き込む。
		while (*ucPtr1 == ' ' || *ucPtr1 == 0x00) ucPtr1++;
//		if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
		for (s1 = 0; s1 < sizeof(SdFF.uWV.bLine[0]); SdFF.uWV.bLine[0][s1++] = (BYTE)p2) ;
		p2 = 0;
		while (p1) {
			if ((UINT)p1 >= sizeof(SdFF.uWV.bLine[0])) {
				cnt = sizeof(SdFF.uWV.bLine[0]);
				p1 -= sizeof(SdFF.uWV.bLine[0]);
			} else {
				cnt = (WORD)p1;
				p1 = 0;
			}

			res = pf_write(SdFF.uWV.bLine[0], cnt, &w);	/* Write data to the file */
			p2 += w;
			if (res != FR_OK) {
				vPut_rc(res);
				break;
			}
			if (cnt != w) break;
		}
		res = pf_write(0, 0, &w);		/* Finalize the write process */
		vPut_rc(res);
		if (res == FR_OK)
			xprintf("\r\n%lu bytes written.", p2);
		break;

	case 'p' :	/* fp - Write console input to the file */
		//xputs("Enter lines to write. A blank line finalize the write operation.\r\n");
		//debaug output buffer

		while (*ucPtr1 == ' ' || *ucPtr1 == 0x00) ucPtr1++;			// blank skip
		if (!*ucPtr1) break;
		strcpy(SdFF.uWV.bLine[0], ucPtr1);
		strcat(SdFF.uWV.bLine[0], "\r\n\x00");					// Not! strcat
		xprintf("\r\n %d sizeof SdFF.uWV.bLine[0]", sizeof(SdFF.uWV.bLine[0]));
		xprintf("\r\n %d bytes strlen", strlen(&SdFF.uWV.bLine[0][0]));

		//dump the SdFF.uWV.bLine[0] buffer
		//xputs("\r\n");
		//xputs("\r\n");
		vXputs_return();						//改行&入力指示プロンプト
		vXputs_return();						//改行&入力指示プロンプト
		s1 = 128;
		ucPtr2 = SdFF.uWV.bLine[0];
		while (s1) {
			s2 = (s1 >= 16) ? 16 : s1;
			s1 -= s2;
			xput_dump((BYTE*)ucPtr2, ofs, s2, DW_CHAR);
			ucPtr2 += 16;
			ofs += 16;
		}

		res = pf_write(SdFF.uWV.bLine[0], strlen(SdFF.uWV.bLine[0]), &w);	/* Write a line to the file */
		if (res == FR_OK)
			xprintf("\r\n %d bytes written.", w);
		res = pf_write(0, 0, &w);		/* Finalize the write process */
		vPut_rc(res);
		break;
#endif
#if _USE_LSEEK
	case 'e' :	/* fe - Move file pointer of the file */
		if (!xatoi(&ucPtr1, &p1)) break;
		if (!p1) p1 = 0;
		res = pf_lseek(p1);
		vPut_rc(res);
		if (res == FR_OK)
			xprintf("\r\nfptr = %lu(0x%lX) ", fs.fptr, fs.fptr);
		break;
#endif
#if _USE_DIR
	case 'l' :	/* fl [<path>] - Directory listing */
		// Format of the path names
		// "[/]directory/file"
		// The Petit FatFs module supports only 8.3 format file name.
		// The sub directories are separated with a /.
		// The path name is terminated with a NUL character, control character or white space.
		// Extended characters (0x80-0xFF) are not allowed for the path name on ASCII only configuration (_CODE_PAGE == 1).
		//
		// The Petit FatFs module does not have a concept of current directory like OS oriented file system.
		// All objects on the volume are always specified in full path name following from the root directory.
		// Dot names are not available. Heading separator is ignored and it can be exist or omitted.

		while (*ucPtr1 == ' ') ucPtr1++;
		res = pf_opendir(&dir, ucPtr1);
		if (res) {
			vPut_rc(res);
			break;
		}
		s1 = 0;
		for(;;) {
			res = pf_readdir(&dir, &fno);
			if (res != FR_OK) {
				vPut_rc(res);
				break;
			}
			if (!fno.fname[0]) break;
			if (fno.fattrib & AM_DIR)
				xprintf("\r\n	<DIR>	%s ", fno.fname);
			else
				xprintf("\r\n%9lu  %s ", fno.fsize, fno.fname);
			s1++;
		}
		xprintf("\r\n%u item(s) ", s1);
		break;
#endif
	}
}

/*****************************
 * 改行&入力指示プロンプト
 *****************************/
void vXputs_return(void) {
	xputs("\r\n>");					//改行&入力指示プロンプト
}


/*****************************
 * pFatFs Moniter
 *****************************/
void vPut_rc (FRESULT rc) {		//ステータスOUTPUT
	FRESULT i;
	const static char *str = {
		"OK\0"
		"DISK_ERR\0"
		"NOT_READY\0"
		"NO_FILE\0"
		"NO_PATH\0"
		"NOT_OPENED\0"
		"NOT_ENABLED\0"
		"NO_FILE_SYSTEM\0"
	};
	for (i = 0; i != rc && *str; i++) {
		while (*str++) ;
	}
	xprintf("\r\nrc=%u FR_%s\r\n>", (UINT)rc, str);

}


/*****************************
 * Wave
 *****************************/
void vModeC2_Wave(void) {

	ucPtr1 = &cCmdBuf[2];
	switch(cCmdBuf[1]) {
	case 'i' :	// open wave logic //
		//open wave logic
		vWAVE_init();
		break;
	case 'c' :	// close wave logic //
		//close wave logic
		vWAVE_close();				//stop WAVE playing
		CloseTimer4();				//stop SD card reading
		break;
	case 's' :	// start wave playing //
		vWAVE_close();				//stop WAVE playing
		CloseTimer4();				//stop SD card reading
		while (*ucPtr1 == ' ') ucPtr1++;
		vWavePlayStart(ucPtr1) ;
		break;
/*
	case '0' :	// wave check //
		vWavePlayStart("ho1_001.wav") ;
		break;
	case '1' :	// wave format check //
		vWavePlayStart("w16s500.wav") ;
		break;
	case '2' :	// wave format check //
		vWavePlayStart("w08m001.wav") ;
		break;
	case '3' :	// wave format check //
		vWavePlayStart("w16s005.wav") ;
		break;
	case '4' :	// wave format check //
		vWavePlayStart("w16s010.wav") ;
		break;
	case '5' :	// The Beatles //
		vWavePlayStart("mb001.wav") ;
		break;
	case '6' :	// wave check //
		vWavePlayStart("w16s001.wav") ;
		break;
	case '7' :	// wave check //
		vWavePlayStart("/timeword/h_07.wav") ;
		break;
*/
	}
}
