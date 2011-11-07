/******************************************************************************
 *
 *               Microchip Memory Disk Drive File System
 *
 ******************************************************************************
 * FileName:        Demonstration.c
 * Dependencies:    FSIO.h
 * Processor:       PIC24F/PIC32
 * Compiler:        C30/C32 
 * Company:         Microchip Technology, Inc.
 * Version:         1.2.0
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
*****************************************************************************/


/*****************************************************************************
   Note:  This file is included to give you a basic demonstration of how the
           functions in this library work.  Prototypes for these functions,
           along with more information about them, can be found in FSIO.h
*****************************************************************************/

#include "MDD File System\FSIO.h"
#include "p33FJ256GP710.h"
#include "stdio.h"
#include "UART2.h"
#include "overflowBuffer.h"
_FOSCSEL(FNOSC_FRC & IESO_ON);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF); 
char sendBuffer[] = "This is test string 1";
char send2[] = "2";
char receiveBuffer[50];

#define FILESIZE 2500


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

   FSFILE * pointer;
   char path[30];
   char count = 30;
   char * pointer2;
   int gh;
   BYTE write_array[512];
   for(gh=0; gh<512; gh++)
   if(gh%8)
   		write_array[gh]='a';
   else
   		write_array[gh]='b';
   DWORD first_sector;
   BYTE test_array[512];
  /* OFB_init();
   OFB_push(write_array);
   calc_checksum(write_array);
   while(1);*/
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
	//printf("stuipd thing");
	//TRISD=0x0FF;
	//setting up pins to show on usb debugger
	TRISDbits.TRISD6=1;
	TRISAbits.TRISA7=0;
	TRISAbits.TRISA6=0;
	TRISAbits.TRISA5=0;
	TRISAbits.TRISA4=0;
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

	#ifdef TESTOVERFLOWBUFFER
		#ifdef __DEBUG
			printf("Starting test of overflow buffer");

			unsigned char ofbtestin[SECTORSIZE];
			unsigned char ofbtestout[SECTORSIZE];
			OFB_init();		
			int ofbi,ofbj,ofbk,result;
			char num=0;
			printf("Starting insertion test\r\n");
			for(ofbj=0;ofbj<=OVERFLOWBUFFERDEPTH;ofbj++)
			{
					for(ofbi=0;ofbi<SECTORSIZE;ofbi++)
						ofbtestin[ofbi]=num+48;
					printf("Size of Buffer: %d\r\n",OFB_getSize());
					printf("Result of Insertion: %d\r\n",OFB_push(ofbtestin));
					printf("New Size: %d\r\n",OFB_getSize());
					num++;
			}
			printf("Starting retrieval test\r\n");
			for(ofbj=0;ofbj<=OVERFLOWBUFFERDEPTH;ofbj++)
			{
				printf("Size of Buffer: %d\r\n",OFB_getSize());
				result=OFB_read_tail(ofbtestout);
				printf("result of read: %d\r\n",result);
				printf("343rd entry in array: %c\r\n",ofbtestout[342]);
				/*for(i=0;i<SECTORSIZE;i++)
				{
					printf("%d",ofbtestout[i]);
					while(UART2IsEmpty());
				}*/
				//printf("\r\n");
				result=OFB_pop();
				printf("Result of Pop: %d\r\n",result);
			}	
			while(1);
		#endif
	#endif	
	
	//Service_Spi();
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
      //FSfseek(pointer,0,SEEK_SET);
	//set_First_Sector(first_sector);
   //FSfwrite("greetings",1,9,pointer);
   printf("waiting for operation\r\n");
   //FSfwrite("greetings",1,9,pointer);
   //allocate_size(38769,pointer);
   DWORD sizeinbytes;
   //need to convert from number of sectors to number of bytes and allocate that much space
   sizeinbytes=(DWORD)FILESIZE*(DWORD)512;
   //sizeinbytes=3774873*(DWORD)512;
   allocate_size(sizeinbytes,pointer,FALSE);
   FSfseek(pointer,0,SEEK_SET);
   first_sector=get_First_Sector(pointer);
   set_First_Sector(first_sector);
   DWORD erasure;
   OFB_init();
   	   for(erasure=0;erasure<FILESIZE;erasure++)
		   {
			   MDD_SDSPI_SectorWrite(first_sector, write_array,FALSE);
			   first_sector++;
			   if(erasure%100==0)
			   		printf("%lu\r",erasure);
			}
   int bleh;
   
   FSfclose(pointer);
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
	    Service_Spi();
	} 
	/*while(temp!='+')
	{
		if(character_count<512)
		{
			if(!UART2IsEmpty())
			{
				temp=UART2GetChar();
				write_array[character_count]=temp;
				character_count++;
				//printf("%08d\r",character_count);
			}
		}
		else
		{
		FSfwrite(write_array,1,character_count, pointer);
		character_count=0;
		}
	}*/
	 //FSfwrite(write_array,1,character_count, pointer);
   	//FSfwrite(sendBuffer,1,21, pointer);
   	unsigned int buffer[512];
   	char buffersign;
   	//bufferreturn(buffer);
   	while(1)
   	{
	 /*buffersign=bufferreturn(buffer);
	 if(buffersign==1)
	 {
		 //FSfwrite(buffer,1,512,pointer);
	 }*/
   	if(!PORTDbits.RD6)
   	{   
	   	DMA0CONbits.CHEN=0;	
		//FSfclose(pointer);
		DMA0CONbits.CHEN=0;
		printf("done with operations\r\n");
		MDD_ShutdownMedia();
		while(1){}
	}
	}
   while(1);
}








