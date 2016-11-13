/********************************
*  遅延関数ライブラリ
*    wait_us(time) ----- time x 1μsec遅延関数
*    wait_ms(time) ----- time x 1msec遅延関数
*    wait_100ms(time) ----- time x 100msec遅延関数
********************************/
#if defined WAIT_LIB

#endif

void vWait_us(unsigned int uiTime);
void vWait_ms(unsigned int uiTime);
void vWait_100ms(unsigned int uiTime);
