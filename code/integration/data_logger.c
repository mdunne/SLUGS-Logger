#include "p33FJ256GP710.h"
//#include "apDefinitions.h"
//#include "MultiCircBuffer.h"
#include "FSIO.h"
#include "uart2.h"
#include "stdio.h"
#include "loggerDefinitions.h"
#include "overflowBuffer.h"


#define BUFFERSIZE 512

	#include "SD-SPI.h"
	
	static char bufferflag;
	static char need_buffer;
	static int need_write;
	//FSFILE * pointer;
	

//#endif

void Init_Data_Logger(int id)
{
	
}



static DWORD first_sector;

void set_First_Sector(DWORD sector)
{
	//CurrentSector=sector;
	first_sector=sector;
}	


//bulk of the program, checks for flags and then adds items to the buffer or
//writes to SPI as needed

void Service_Spi(FSFILE *fo)
{
	static int totalerr=0;
	static int card_initerr=1;
	static int maxbuffersize=0;
	static DWORD sector_count=0;
	static DWORD CurrentSector=0;
	static int IncreaseSizeNow=FALSE;
	static int IncreaseSize=FALSE;
	int ofb_error=0;
	BYTE error=TRUE;

		
		// if bytes are ready from DMA interrupt
		
		//if sectors are still in the buffer or there was en error
		if((sector_count>=CHEW_FAT_SIZE_IN_SECTORS)||(sector_count==0))
		{
			FILEallocate_multiple_clusters(fo,CHEW_FAT_SIZE_IN_SECTORS);
			sector_count=1;
			if (CurrentSector==0)
			{
				CurrentSector=get_First_Sector(fo);
			}	
	
		}	
		if (OFB_getSize()!=0)//if (need_write==1)
		{
			#ifdef __DEBUG
				//printf("err: %d\t%lu\t%d\r\n",error,CurrentSector,totalerr);
				//printf("modulo Result: %lu\r\n",(CurrentSector-first_sector)%CHEW_FAT_SIZE);
			#endif
			if(sector_count>=NINETY_PER_CHEW_FAT_SIZE_IN_SECTORS)
			{
				#ifdef __DEBUG
					//printf("Allocating file: %lu\r\n",CurrentSector);
				#endif
				IncreaseSize=TRUE;
				sector_count=1;
				if (CurrentSector==0)
				{
					CurrentSector=get_First_Sector(fo);
				}	
			}	
			//if there is an error from writing to the card or the last card
			//init has failed it trys to init the card again
			//if(error!=TRUE||card_initerr!=1)
			if(card_initerr!=TRUE)
			{
				card_initerr=MDD_SDSPI_MediaInitialize();
				#ifdef __DEBUG
					printf("e\r\n");
				#endif
				need_write=TRUE;
				return;
			}
			else
			{
				//if the card is successfully inited it reads out a sector and 
				//dumps to spi
				unsigned char outbuf[512];
				OFB_read_tail(outbuf);
				error=MDD_SDSPI_SectorWrite(CurrentSector,outbuf,0);
				if(error==TRUE)
				{
					//if it succeeds pop sector off buffer and advance
					OFB_pop();
					#ifdef __DEBUG
						int temp=OFB_getSize();
						if(temp>maxbuffersize)
						{
							maxbuffersize=temp;
							printf("Max Buffer Size: %d\r\n",maxbuffersize);
						}	
					#endif					
					CurrentSector++;
					sector_count++;
					if(OFB_getSize()==0)
					{
						need_write=0;
						#ifdef __DEBUG
							//printf("Over Flow Buffer is Empty\r\n");
						#endif
					}	
					return;
				}
				else
				{
					//if error has again occured try to init card again
					card_initerr=MDD_SDSPI_MediaInitialize();
					#ifdef __DEBUG
						UART2PutChar('e');
						UART2PutChar('\r');
						UART2PutChar('\n');
					#endif
				}				
			}
		}
		else if(IncreaseSize)
		{
			FILEallocate_multiple_clusters(fo,CHEW_FAT_SIZE_IN_SECTORS);
			IncreaseSizeNow=FALSE;
			IncreaseSize=FALSE;
			sector_count=1;
		}	
}