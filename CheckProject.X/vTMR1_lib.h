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
    unsigned int uiTMR001;
#else
    extern unsigned int uiTMR001;
#endif

/*****************************
 * PROTOTYPES
 *****************************/
void Intrupt_TMR1(void);    //decrease timer parameter step by 1msec.
#define FLAG_iTMR001 (uiTMR001==0)


