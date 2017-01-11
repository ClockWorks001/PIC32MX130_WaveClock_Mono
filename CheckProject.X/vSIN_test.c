#include <math.h>
#include "mcc_generated_files/mcc.h"
#include "vSIN_test.h"

#define PI 3.141592

static int a = 0, b, y ;
static float rad;
//static unsigned int y;

int vSIN_out(void)
{
    
    if (++a >= 512) a = 0;
    
    rad = (PI * a) / 256;
    y = (sin( rad ) + 1) * 127 + 1;
    OC1_PWMPulseWidthSet( (uint16_t)y );
 
//    if(++b >= 32 ){
//        b = 0;
//    }
   
    return (int)y;

}
