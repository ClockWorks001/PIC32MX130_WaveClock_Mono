/*******************************************************************************
 *	処理タイミング用 TIMER1 設定
 *  1000Hz 1msec interval
 *	author  :hiroshi murakami
 *	created :20161225
 *	modified:-
 ******************************************************************************/

/*****************************
 * VARIABLES
 *****************************/
#if defined TMR1_LIB
    volatile unsigned int uiTMR001;
#else
    volatile extern unsigned int uiTMR001;
#endif

/*****************************
 * PROTOTYPES
 *****************************/
void Intrupt_TMR1(void);    //decrease timer parameter step by 1msec.
#define FLAG_uiTMR001 (uiTMR001==0)


