



#include "FSIO.h"
#include "p33FJ256GP710.h"
#include "stdio.h"
#include "overflowBuffer.h"
#include "uart2.h"
#include "id_code.h"
#include "data_logger.h"
_FOSCSEL(FNOSC_FRC & IESO_ON);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF); 
char sendBuffer[] = "This is test string 1";
char send2[] = "2";
char receiveBuffer[50];

#define FILESIZE 10000


//#define TESTOVERFLOWBUFFER


#if defined (__PIC24F__)

    _CONFIG2(IESO_OFF & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_HS)
    _CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & ICS_PGx2 & FWDTEN_OFF)

#elif defined (__PIC32MX__)
    #pragma config FPLLMUL  = MUL_15        // PLL Multiplier
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
    #pragma config FPLLODIV = DIV_1         // PLL Output Divider
    #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
    #pragma config FWDTEN   = OFF           // Watchdog Timer
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    #pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
    #pragma config FNOSC    = PRIPLL        // Oscillator Selection
    #pragma config CP       = OFF           // Code Protect
    #pragma config BWP      = OFF           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
    #pragma config DEBUG    = ON            // Background Debugger Enable
#endif

   
int main (void)
{

   FSFILE * pointer=NULL;
   DWORD first_sector;
   BYTE test_array[512];
   SearchRec rec;
   pointer=NULL;
   unsigned char attributes;
   unsigned char size = 0, i;
   PLLFBD =38;
   CLKDIVbits.PLLPOST=0;
   CLKDIVbits.PLLPRE=0;
   __builtin_write_OSCCONH(0b011);
   __builtin_write_OSCCONL(0b01);
	while (OSCCONbits.COSC != 0b011);	// Wait for Clock switch to occur	
	while(OSCCONbits.LOCK != 1) {};
	UART2Init();
	printf("starting Integration test\r\n");
	//DataEEInit();
	int id=0;
	id=Get_ID_Code();
	printf("ID: %u\r\n",id);
	OFB_init(id);
	Increment_ID_Code();
	#ifdef __DEBUG
		printf("Clock Switch Complete, Waiting For Media\r\n");
	#endif
	//waits for a card to be inserted
   while (!MDD_MediaDetect());
	#ifdef __DEBUG
		printf("Media Found, Waiting for FSinit\r\n");
	#endif
   // Initialize the library
   while (!FSInit());
   char filename[9];
   sprintf(filename,"%05d.bin",id);
   // Create a file
   printf("filename will be: %s\r\n",filename);
   while(pointer==NULL)
   {
   		pointer = FSfopen (filename, "w");
   }
   #ifdef __DEBUG
   	printf("File Has been opened\r\n");
   #endif		
	
	while(1)
	{
		Service_Spi(pointer);
	}	
	//printf("stuipd thing");
	//TRISD=0x0FF;
	//setting up pins to show on usb debugger
	TRISDbits.TRISD6=1;
	TRISAbits.TRISA7=0;
	TRISAbits.TRISA6=0;
	TRISAbits.TRISA5=0;
	TRISAbits.TRISA4=0;
	TRISGbits.TRISG0=0;
	AD1PCFGLbits.PCFG0=1;	
	//LATA=1;
	//_LATA4=1;
	//_RA7=1;
	//_LATA6=1;
	
	//_LATA5=1;
	//_LATA7=1;
	
	//printf("they should be on now");
	//while(1);
	//LATAbits.LATA7=0;
	//TRISB=0xFFFF;
	//AD1PCFGLbits.PCFG1=1;	
	//Service_Spi();
	/*#ifdef __DEBUG
		printf("Clock Switch Complete, Waiting For Media\r\n");
	#endif
	//waits for a card to be inserted
   while (!MDD_MediaDetect());
   
   
	#ifdef __DEBUG
		printf("Media Found, Waiting for FSinit\r\n");
	#endif
   // Initialize the library
   while (!FSInit());
	char temp;
	int character_count,remove_success;
	character_count=0;
   // Create a file
   printf("starting up\r\n");
   remove_success=FSremove("WRITE.TXT");
   printf("Removal of prev: %d\r\n",remove_success);
   pointer = FSfopen ("WRITE.TXT", "w");

   if (pointer == NULL)
   {
	   #ifdef __DEBUG
	   	printf("File open failed\r\n");
	   #endif
      while(1);
   }   

   printf("waiting for operation\r\n");
   printf("in file resize_test\r\n");
   
   
   DWORD sizeinbytes;
   //need to convert from number of sectors to number of bytes and allocate that much space
   sizeinbytes=(DWORD)FILESIZE*(DWORD)512;
   printf("Chew Fat: %lu\r\nChew Fat Sectors: %d\r\n",CHEW_FAT_SIZE,CHEW_FAT_SIZE_IN_SECTORS);
   //sizeinbytes=3774873*(DWORD)512;
   //allocate_size(sizeinbytes,pointer,FALSE);
   //FSfclose(pointer);*/
   /*FILEallocate_multiple_clusters(pointer,24);
   FAT_print_cluster_chain(pointer->cluster, pointer->dsk);
   FILEallocate_multiple_clusters(pointer,24);
   FAT_print_cluster_chain(pointer->cluster, pointer->dsk);
   int numclus,numcount;
   //DWORD clusttemp;
   printf("First CLuster in main: %lu\r\n",get_First_Sector(pointer));
   for (numclus=0;numclus<48;numclus++)
   {
		for(numcount=0;numcount<512;numcount++)
		{
		   test_array[numcount]=numclus+48;
		}
		MDD_SDSPI_SectorWrite(get_First_Sector(pointer)+numclus,test_array,FALSE);
	}*/
   //FILEallocate_multiple_clusters(pointer,24);
   //FILEallocate_multiple_clusters(pointer,24);
   //FILEallocate_multiple_clusters(pointer,CHEW_FAT_SIZE_IN_SECTORS);
   //FSfclose(pointer);
   //FILEallocate_multiple_clusters(pointer,4096);
   //FSfclose(pointer);
   //FILEallocate_multiple_clusters(pointer,1024);
   //FILEallocate_multiple_clusters(pointer,1024);
   
   //FSfseek(pointer,0,SEEK_SET);
   first_sector=get_First_Sector(pointer);
   set_First_Sector(first_sector);
   DWORD erasure;
   OFB_init(0x1f1f);
   //FSfclose(pointer);
   //MDD_ShutdownMedia();
   printf("done with file allocation\r\n");
   #ifdef DMAON
   #else
   #endif
      
      //while(UART2IsEmpty());
      //temp=UART2GetChar();
      //write_array[character_count]=temp;
      //character_count++;
    while(1)
    {
	    Service_Spi(pointer);
	}
}