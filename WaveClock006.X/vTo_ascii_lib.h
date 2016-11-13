/*************************************************
*  数値->ascii変換ライブラリ
*    vCharToHEX(data, *buffer) ----- 8ビット値を2桁の16進数ASCII文字列へ変換
*    vIntToDec(digit, data, *buffer) ----- int整数を10進数ASCII文字列に変換
*************************************************/

/*****************************
** 定数変数定義
*****************************/
#if defined TO_ASCII_LIB

#endif

/*****************************
*  プロトタイプ定義ファイル
*****************************/
void vCharToHEX(unsigned char data, char *buffer);
void vIntToDec(char digit, unsigned int data, char *buffer);

