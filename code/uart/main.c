//test harness for timers
#define PICGP710

#ifdef PICGP710
#include "p33FJ256GP710.h"
#endif
#include "circBuffer.h"
#include "uart2.h"
#include <stdio.h>
_FOSCSEL(FNOSC_FRC & IESO_ON);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF);

static char first;
static int foop;

	

int main ( void )
{
        //The settings below set up the oscillator and PLL for 16 MIPS as
        //follows:
        //            Crystal Frequency  * (DIVISOR+2)
        // Fcy =     ---------------------------------
        //             PLLPOST * (PRESCLR+2) * 4	
        PLLFBD =38;
        CLKDIVbits.PLLPOST=0;
        CLKDIVbits.PLLPRE=0;
        __builtin_write_OSCCONH(0b011);
        __builtin_write_OSCCONL(0b01);
	while (OSCCONbits.COSC != 0b011);	// Wait for Clock switch to occur	
	while(OSCCONbits.LOCK != 1) {};
	UART2Init();
	char temp;
	printf("hmm, does this work after all");
	while(1)
	{		
		if(!UART2IsEmpty())
			UART2PutChar(UART2GetChar());	
	}

}
