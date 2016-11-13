/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ    40000000L
#define FCY         SYS_FREQ
#define PB_DIV      1					// Peripheral Clock Divisor:
#define PBCLK		(SYS_FREQ / PB_DIV)	// Peripheral Clock
//#define	PBCLK		(SYS_FREQ/(1 << OSCCONbits.PBDIV))

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */


