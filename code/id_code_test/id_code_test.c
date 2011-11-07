




#include "p33FJ256GP710.h"
#include "stdio.h"
#include "uart2.h"
#include "id_code.h"
_FOSCSEL(FNOSC_FRC & IESO_ON);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF); 


#define FILESIZE 10000


//#define TESTOVERFLOWBUFFER



   
int main (void)
{
  
   //clock switching
   PLLFBD =38;
   CLKDIVbits.PLLPOST=0;
   CLKDIVbits.PLLPRE=0;
   __builtin_write_OSCCONH(0b011);
   __builtin_write_OSCCONL(0b01);
	while (OSCCONbits.COSC != 0b011);	// Wait for Clock switch to occur	
	while(OSCCONbits.LOCK != 1) {};

	UART2Init();
	printf("starting ID code test\r\neach reset should increment count by one\r\n");
	
	int id=0;
	id=Get_ID_Code();
	printf("ID: %u\r\n",id);
	Increment_ID_Code();
	while(1);
}	