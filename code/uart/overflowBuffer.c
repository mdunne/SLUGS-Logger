#include <stdlib.h>
#include "overflowBuffer.h"
#include "loggerdefinitions.h"
#include <stdio.h>

typedef unsigned char BYTE;
unsigned char ofb_buffer[OVERFLOWBUFFERDEPTH][SECTORSIZE];

unsigned char ofb_head;
unsigned char ofb_tail;
unsigned int ofb_size;

// Constructors - Destructors
// ==========================
// this Function returns a pointer to a new Circular Buffer of size pm_size 

	void OFB_init (int idcode){
		
		// initialize to zero
		int i,j;
		
		for (i=0; i<OVERFLOWBUFFERDEPTH; i++)
		{
			ofb_buffer[i][0]=HEADER_ONE;
			ofb_buffer[i][1]=HEADER_TWO;
			for (j=2;j<DMABUFFERSIZE; j++)
			{
				ofb_buffer[i][j] = 0;
			}
			ofb_buffer[i][DMABUFFERSIZE+2]=FOOTER_ONE;
			ofb_buffer[i][DMABUFFERSIZE+3]=FOOTER_TWO;
			ofb_buffer[i][510]=(char)((0xFF00&idcode)>>4);
			ofb_buffer[i][511]=(char)(0x00FF&idcode);
		}
				
		// initialize the data members
		ofb_head = 0;
		ofb_tail = 0;
		ofb_size = 0;

	}
	


// Accesor Methods
// ===============

// returns the amount of unread bytes in the circular buffer
// WARNING: this assumes that init has been called first
unsigned int OFB_getSize (void){	
	return ofb_size;
}

// fills array with top of queue, returns 0 if unsuccessful or queue is empty
int OFB_read_tail(unsigned char outputarray[])
{
	if(ofb_size!=0)
	{
		int j;
		for(j=0;j<SECTORSIZE;j++)
			outputarray[j]=ofb_buffer[ofb_tail][j];
		return 1;
	}
	else
	{
		return 0;
	}
}


//pops an array off the tail
// needs to be seperate from read due to length of time it takes to copy a full array out
int OFB_pop(void)
{
	if(ofb_size!=0)
	{
		ofb_tail++;
		if(ofb_tail>=OVERFLOWBUFFERDEPTH)
		{
			ofb_tail=0;
		}	
		ofb_size--;
		return 1;
	}
	else
	{
		return 0;
	}	
}
	
	
	
int OFB_push(unsigned char inbuffer[])
{
	static int overflowed=0;
	if(ofb_size!=OVERFLOWBUFFERDEPTH)
	{
		unsigned char checksum;
		checksum=calc_checksum(inbuffer);
		//ofb_buffer[ofb_head][0]='1';
		ofb_buffer[ofb_head][DMABUFFERSIZE+4]=checksum;
		ofb_head++;
		if(ofb_head>=OVERFLOWBUFFERDEPTH)
		{
			ofb_head=0;
		}
		ofb_size++;
		return 1;

	}	
	else
	{
		printf("OverFlow Buffer was overflowed\r\n");
		overflowed++;
		return 0;
	}	
}	

unsigned char calc_checksum(unsigned char inBuffer[])
{
		// Loop through all chars to get a checksum
		unsigned char checkSum; //= inBuffer[0];
		checkSum=inBuffer[0];
		ofb_buffer[ofb_head][2]=inBuffer[0];
		int i;
		for (i=1;i<DMABUFFERSIZE; i++)
		{
			checkSum^=inBuffer[i];
			ofb_buffer[ofb_head][i+2]=inBuffer[i];
		}
		//printf("%d",checkSum);
		return checkSum;
		/*for (i = 0; i< DMABUFFERSIZE; i++)
	    {
	   		   // Is this the first value for the checksum?
	        if (i == 0)
	        {
	          // Yes. Set the checksum to the value
	          checkSum = inBuffer[i];
	        }
	        else
	        {
	          // No. XOR the checksum with this character's value
		       checkSum ^= inBuffer[i];
	        }
	        outBuffer[i]=inBuffer[i];
	    }*/
	    // Return the checksum 

}
