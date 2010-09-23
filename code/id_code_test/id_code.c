#include <stdlib.h>
#include "id_code.h"
#include "loggerdefinitions.h"
#include <stdio.h>
#include "DEE.h"


static int code;
static int dee_init=0;

unsigned int Get_ID_Code(void)
{
	int err=0;
	if(dee_init==0)
	{
		err=DataEEInit();
		dee_init++;
		#ifdef __DEBUG
			//printf("Error for Init: %d\r\n",err);
		#endif
	}
	code= DataEERead(MEM_LOCATION_ID);
	return code;
}




char Increment_ID_Code(void)
{
	if(dee_init)
	{
		int err=0;
		code++;
		err = DataEEWrite(code,MEM_LOCATION_ID);
		return err;
	}
	return 0xff;
}	