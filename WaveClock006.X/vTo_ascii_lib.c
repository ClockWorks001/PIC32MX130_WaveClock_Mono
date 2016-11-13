/*************************************************
*  数値->ascii変換ライブラリ
*    vCharToHEX(data, *buffer) ----- 8ビット値を2桁の16進数ASCII文字列へ変換
*    vIntToDec(digit, data, *buffer) ----- int整数を10進数ASCII文字列に変換
*************************************************/
#define TO_ASCII_LIB

#include "vTo_ascii_lib.h"

/*****************************
*  バイナリ値を2桁の16進数ASCII文字列へ変換
*****************************/
void vCharToHEX(unsigned char data, char *buffer){
    *buffer = '0' + ((char)(data >> 4) & 0x0F); //上位４ビット16進変換
    if(((data >> 4) & 0x0F) > 9){               //10以上の場合
        *buffer += 7;                           //A-Fに変換
    }
    buffer++;                                   //バッファ次へ
    *buffer = '0' + ((char)(data) & 0x0F);      //下位4ビット16進変換
    if(((data) & 0x0F) > 9){                    //10以上の場合
        *buffer += 7;                           //A-Fに変換
    }
}

/*****************************
* int整数を10進数ASCII文字列に変換
* digit:桁数 data:input *buffer:output
*****************************/
void vIntToDec(char digit, unsigned int data, char *buffer){
	char i;

	buffer += digit;					// 最後の数字位置 *digit:数字の桁数
	for(i=digit; i>0; i--) {			// 変換は下位から上位へ
		buffer--;						// ポインター１
		*buffer = (data % 10) + '0';	// ASCIIへ
		data = data / 10;				// 次の桁へ
	}
}
