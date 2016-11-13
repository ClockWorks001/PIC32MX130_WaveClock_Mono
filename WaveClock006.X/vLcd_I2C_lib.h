/********************************
*  液晶表示器用ヘッダファイル
*    vLcd_init()    ----- 初期化
*    vLcd_str(ptr)  ----- 文字列表示出力
*    vLcd_clear()   ----- 全消去
*	 vLcd_printAt(ucLine, ucColumn)	----- カーソル位置を移動
*    vLcd_cmd(cmd)  ----- コマンド出力
*    vLcd_data(data) ----- １文字表示出力
*    cDataTrans(data) ----- I2Cデータ出力共通関数
********************************/

#define LCD_LINE_SIZE 16				//LCD の1行の文字数

#if defined LCD_I2C_LIB
	/********************************
	*  LCD i2c setting
	*********************************/
	#define LCD_I2C_BUS         I2C1
	#define I2C_CLOCK_FREQ      400000
	#define LCD_ADDRESS			0b01111100
	//I2C_7_BIT_ADDRESS   SlaveAddress;

	#define C1uSEC (10 * (40000000L / FCY)) // 1 micro sec

	/********************************
	*  調整用定数
	*********************************/
	//#define CONTRAST	0x18	// for 5.0V
	#define CONTRAST  0x38		// for 3.3V (max=3F)
	/*********************************
	*　アイコンの定義
	*********************************/
	const unsigned char ICON[14][2]={
		{0x00, 0x10},		// アンテナ
		{0x02, 0x10},		// 電話
		{0x04, 0x10},		// 無線
		{0x06, 0x10},		// ジャック
		{0x07, 0x10},		// △
		{0x07, 0x08},		// ▽
		{0x07, 0x18},		// △▽
		{0x09, 0x10},		// 鍵
		{0x0B, 0x10},		// ピン
		{0x0D, 0x02},		// 電池無し
		{0x0D, 0x12},		// 容量少
		{0x0D, 0x1A},		// 容量中
		{0x0D, 0x1E},		// 容量多
		{0x0F, 0x10}		// 丸
	};

#endif

void vI2C_init(void) ;
void vI2C_close(void) ;
void vStartTransfer( void );
void vStopTransfer( void ) ;

char cDataTrans(unsigned char data);
void vLcd_data(unsigned char data);
void vLcd_cmd(unsigned char cmd);
void vLcd_init(void);
void vLcd_clear(void);
void vLcd_printAt(unsigned char ucLine, unsigned char ucColumn);
void vLcd_str(const unsigned char* ptr);
void vLcd_icon(unsigned char num, unsigned char onoff);
void vLcd_blinkON(void);
void vLcd_blinkOFF(void);

