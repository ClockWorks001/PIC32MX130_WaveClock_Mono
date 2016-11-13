/********************************
*  液晶表示器用ヘッダファイル
*    vLcd_init()    ----- 初期化
*    vLcd_str(ptr)  ----- 文字列表示出力
*    vLcd_clear()   ----- 全消去
*    vLcd_cmd(cmd)  ----- コマンド出力
*    vLcd_data(data) ----- １文字表示出力
*	 vLcd_printAt(ucLine, ucColumn)	----- カーソル位置 0,0が原点
*    vLcd_blinkON()   ----- 点滅　ON
*    vLcd_blinkOFF()   ----- 点滅 OFF
*    cDataTrans(data) ----- I2Cデータ出力共通関数
********************************/
#define LCD_I2C_LIB

#include <plib.h>            /* Include to use PIC32 peripheral libraries      */
#include "system.h"

#include "vLcd_I2C_lib.h"
#include "vWait_lib.h"
#include "xprintf.h"
#include "vERROR_CODE.h"


/*****************************
 * I2C initialization
 *****************************/
void vI2C_init(void) {
    UINT32              actualClock;

	// Configure Various I2C Options
//	I2C1CON = 0x00;
	I2CConfigure(LCD_I2C_BUS, I2C_ENABLE_HIGH_SPEED);
    // Set the I2C baudrate
    actualClock = I2CSetFrequency(LCD_I2C_BUS, PBCLK, I2C_CLOCK_FREQ);
    if ( abs(actualClock-I2C_CLOCK_FREQ) > I2C_CLOCK_FREQ/10 )
    {
        xprintf("Error: I2C1 clock frequency (%u) error exceeds 10%%.\n", (unsigned)actualClock);
    }

    // Enable the I2C bus
    I2CEnable(LCD_I2C_BUS, TRUE);
	I2C1CONbits.STREN = 1;

}

/*****************************
 * I2C initialization
 *****************************/
void vI2C_close(void) {
    I2CEnable(LCD_I2C_BUS, FALSE);
}

/*******************************************************************************
  Function:
    void vStartTransfer( BOOL restart )
  Summary:
    Starts (or restarts) a transfer to/from the EEPROM.
  Description:
    This routine starts a transfer to/from the Target, waiting
    until the start condition has completed.
  Precondition:
    The I2C module must have been initialized.
  Parameters:
    None.
  Returns:
    None.

  Remarks:
    This is a blocking routine that waits for the bus to be idle and the Start
    signal to complete.
  *****************************************************************************/

void vStartTransfer( void )
{
//	int iWait;

    // Send the Start signal
	I2C1CONbits.SEN = 1;

    // Wait for the signal to complete
//	iWait = 0;
    while (I2C1CONbits.SEN == 1);
//	{
//		iWait++;
//		if(iWait > C1uSEC) return ; //ERROR99;
//	};

}

/*******************************************************************************
  Function:
    void vStopTransfer( void )
  Summary:
    Stops a transfer to/from the EEPROM.
  Description:
    This routine Stops a transfer to/from the EEPROM, waiting (in a
    blocking loop) until the Stop condition has completed.
  Precondition:
    The I2C module must have been initialized & a transfer started.
  Parameters:
    None.
  Returns:
    None.

  Remarks:
    This is a blocking routine that waits for the Stop signal to complete.
  *****************************************************************************/

void vStopTransfer( void )
{
//	int iWait;
    // Send the Stop signal
	I2C1CONbits.PEN = 1;

    // Wait for the signal to complete
//	iWait = 0;
    while (I2C1CONbits.PEN == 1);
//	{
//		iWait++;
//		if(iWait > C1uSEC) return ; //ERROR99;
//	};

}





/*********************************
*  I2Cデータ出力共通関数
*********************************/
char cDataTrans(unsigned char data)
{
	int iWait;
	iWait = 0;
	IFS1bits.I2C1MIF = 0;
    // Wait for the transmitter to be ready
    while(I2C1STATbits.TBF);
//	{
//		iWait++;
//		if(iWait > C1uSEC) return ERROR99;
//	};
    // Transmit the byte
    I2C1TRN = data;        //送信
    // Wait for the transmission to finish
	iWait = 0;
	while(IFS1bits.I2C1MIF == 0);
//	{
//		iWait++;
//		if(iWait > C1uSEC) return ERROR99;
//	};
	IFS1bits.I2C1MIF = 0;
    return(0);
}


/*********************************
* 液晶へ1文字表示データ出力
*********************************/
void vLcd_data(unsigned char data)
{
	char cReturn;		// 0:successful -n:there was an error 　*リターンは読み捨て

    //while( !I2CBusIsIdle(LCD_I2C_BUS) );	//バスアイドル待ち
    vStartTransfer();	// スタート

	cReturn = cDataTrans(LCD_ADDRESS);	//アドレス
	cReturn = cDataTrans(0x40);			//表示データ指定
	cReturn = cDataTrans(data);			//表示データ出力

	vStopTransfer();	// ストップ
    vWait_us(27);		//30usec待ち
}

/*******************************
* 液晶へ１コマンド出力
*******************************/
void vLcd_cmd(unsigned char cmd)
{
	char cReturn;     // 0:successful -n:there was an error 　*リターンは読み捨て

    //while( !I2CBusIsIdle(LCD_I2C_BUS) );	//バスアイドル待ち
    vStartTransfer();  // スタート
	cReturn = cDataTrans(LCD_ADDRESS);	//アドレス
	cReturn = cDataTrans(0x00);			//コマンドデータ指定
	cReturn = cDataTrans(cmd);			//コマンドデータ出力

	vStopTransfer();         // ストップ

    /* ClearかHomeか */
    if((cmd == 0x01)||(cmd == 0x02)){
        vWait_ms(2);             //2msec待ち
    } else {
        vWait_us(27);            //30usec待ち
    }
}

/*******************************
*  初期化関数
*******************************/
void vLcd_init(void)
{
    vWait_100ms(3);
    vLcd_cmd(0x38);              // 8bit 2line Normal mode
    vLcd_cmd(0x39);              // 8bit 2line Extend mode
    vLcd_cmd(0x14);              // BIAS 1/5 CLK 380Khz
    /* コントラスト設定 */
    vLcd_cmd(0x70 + (CONTRAST & 0x0F));
    vLcd_cmd(0x5C + (CONTRAST >> 4));
//  vLcd_cmd(0x6A);              // Follower for 5.0V
	vLcd_cmd(0x6B);              // Follower for 3.3V
    vWait_100ms(3);
    vLcd_cmd(0x38);              // Set Normal mode
    vLcd_cmd(0x0C);              // Display On
    vLcd_cmd(0x01);              // Clear Display
}

/******************************
* 全消去関数
******************************/
void vLcd_clear(void)
{
    vLcd_cmd(0x01);              //初期化コマンド出力
}

/******************************
* カーソル位置を移動
* ucLine 0->1行目 1->2行目
******************************/
void vLcd_printAt(unsigned char ucLine, unsigned char ucColumn)
{
	switch (ucLine) {
	case  	0 :					//1行目
	    vLcd_cmd(0b10000000 | (0x00 + ucColumn)); //カーソル位置指定
		break;
	default:					//2行目
	    vLcd_cmd(0b10000000 | (0x40 + ucColumn)); //カーソル位置指定
	}
}

/*****************************
* 文字列表示関数
*****************************/
void vLcd_str(const unsigned char *ptr)
{
	int i;
	i = 0;
    while(*ptr && i < LCD_LINE_SIZE){        		//文字取り出し
        vLcd_data(*ptr++);		//文字表示
		i++;
    }
}

/*****************************
*  アイコン表示制御関数
*****************************/
void vLcd_icon(unsigned char num, unsigned char onoff)
{
    vLcd_cmd(0x39);              // Extend mode
    vLcd_cmd(0x40 | ICON[num][0]);   // アイコンアドレス指定
    if(onoff){
        vLcd_data(ICON[num][1]); // アイコンオンデータ
    }else{
        vLcd_data(0x00);         // アイコンオフデータ
    }
    vLcd_cmd(0x38);              // Normal Mode
}


/*****************************
* blink ON
*****************************/
void vLcd_blinkON(void)
{
    vLcd_cmd(0b00001111);		//d:1 display on c:1 cursor on b:1 blink on
    //vLcd_cmd(0x0F);			//d:1 display on c:1 cursor on b:1 blink on
}

/*****************************
* blink OFF
*****************************/
void vLcd_blinkOFF(void)
{
    //vLcd_cmd(0b00001100);		//d:1 display on c:1 cursor on b:1 blink on
    vLcd_cmd(0x0C);				//d:1 display on c:1 cursor on b:1 blink on
}


