/*******************************************************************************
 *	Motor 処理
 *	新規:20130930
 *	修正:-
 ******************************************************************************/

/*****************************
 * VARIABLES
 *****************************/

#define MOTOR_EN()		LATBbits.LATB11 = 1;LATBbits.LATB12 = 1;	// 1 = H 
#define	MOTOR_DISEN()	LATBbits.LATB11 = 0;LATBbits.LATB12 = 0;	// 0 = L 

/*****************************
 * PROTOTYPES
 *****************************/


