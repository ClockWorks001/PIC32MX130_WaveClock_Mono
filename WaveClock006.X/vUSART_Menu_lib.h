/*******************************************************************************
 *	USART_Menu処理
 *	新規:20120922
 *	修正:-
 ******************************************************************************/
#include "pff.h"		//file system を構築する為、ここに記述

/*****************************
 * VARIABLES
 *****************************/
enum eModeC2 {
	eModeC2_menu_msg0,					//Start message
	eModeC2_menu_msg1,					//Start message
	eModeC2_menu_init,
	eModeC2_vGetsCMND,
	eModeC2_vExecCmd,					//コマンド分岐
	eModeC2_Command_error,
	eModeC2_end
};


#if defined USART_MENU_LIB

	enum eModeC2 eModeStatusC2;
	unsigned char *ucPtr1, *ucPtr2;			// Pointer for Byte data
	long p1, p2;


#else
	extern enum eModeC2 eModeStatusC2;
#endif


/*****************************
 * PROTOTYPES
 *****************************/
void vUSART_menu_init(void);
void vModeUartControl11(void);

void vMessage_0_ModeStart01(void);
void vCommand_TimeSet(void);
void vCommand_DateSet(void);

void vComandFormatCheck_7Digit(void);	//Comand format check 7digit
void vShowNowTimeMessage(void);			//時間の表示

void vCommand_FatFs(void);

void vXputs_return(void);
void vPut_rc (FRESULT rc);				//ステータスOUTPUT

void vModeC2_Wave(void);

