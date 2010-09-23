#include <stdlib.h>
#include "overflowBuffer.h"
#include "loggerdefinitions.h"
#include <stdio.h>




unsigned char ofb_buffer[OVERFLOWBUFFERDEPTH][SECTOR];

unsigned char ofb_head;
unsigned char ofb_tail;
unsigned char ofb_size;

// Constructors - Destructors
// ==========================
// this Function returns a pointer to a new Circular Buffer of size pm_size 

	void OFB_init (void){
		
		// initialize to zero
		int i,j;
		for (i=0; i<OVERFLOWBUFFERDEPTH; i++)
		{
			for (j=0;j<DMABUFFERSIZE; j++)
			{
				ofb_buffer[i][j] = 0;
			}
		}
				
		// initialize the data members
		ofb_head = 0;
		ofb_tail = 0;
		ofb_size = OVERFLOWBUFFERDEPTH;
	}

	


// Accesor Methods
// ===============

// returns the amount of unread bytes in the circular buffer
unsigned int getMultiLength (MCBRef MCB){	
	// if the circular buffer is not null
	if (MCB != NULL){
		if (MCB->head <= MCB->tail){
			return (MCB->tail-MCB->head);
		} else{
			return (MCB->size + MCB->tail - MCB->head);
		}		
	}
	else{
		return 0;
	}
	

}

// returns the actual index of the head
int readMultiHead (MCBRef MCB){
	// if the circular buffer is not null
	if (MCB != NULL){
		return (MCB->head);
	}
	else{
		return 0;
	}

}

// returns the actual index of the tail
int readMultiTail (MCBRef MCB){
	// if the circular buffer is not null
	if (MCB != NULL){
		return (MCB->tail);
	}
	else{
		return 0;
	}

}

// returns the byte (actual value) that the head points to. this
// does not mark the byte as read, so succesive calls to peak will
// always return the same value
unsigned char Multipeak(MCBRef MCB, unsigned char outBuffer[DMABUFFERSIZE]){
	// if the circular buffer is not null
	if (MCB != NULL)
	{	
		// if there are bytes in the buffer
		if (getMultiLength(MCB) > 0){
			return MCB->buffer[MCB->head];
		}
	}
	return 0;	
}


// Manipulation Procedures
// ======================
// returns the front of the circular buffer and marks the byte as read
unsigned char readMultiFront (MCBRef MCB, unsigned char outBuffer[DMABUFFERSIZE]){
	// if the circular buffer is not null
	if (MCB != NULL)
	{	
		char retVal;
		// if there are bytes in the buffer
		if (getMultiLength(MCB) > 0){
			retVal = MCB->buffer[MCB->head];
			MCB->head = MCB->head < (MCB->size -1)? MCB->head+1: 0;
			return retVal;
		}
		return 128;
	}
	return 254;
}

// writes one byte at the end of the circular buffer, 
// increments overflow count if overflow occurs
unsigned char writeMultiBack (MCBRef MCB, unsigned char inBuffer[DMABUFFERSIZE]){
	// if the circular buffer is not null
	if (MCB != NULL){			
		if (getMultiLength (MCB) == (MCB->size -1)){
			MCB->overflowCount ++;
			//return 1;
		} else {		
			//this is where you copy the data MCB->buffer[MCB->tail] = data;
			MCB->tail = MCB->tail < (MCB->size -1)? MCB->tail+1: 0;
			//return 0;
		}
		//return 0;
	}
	else{
		return 1;
	}
}

// empties the circular buffer. It does not change the size. use with caution!!
void makeMultiEmpty (MCBRef MCB){
	if (MCB != NULL){
		int i,j;
		for(i = 0; i < MCB->size; ++i)
		{
			for (j =0; j<DMABUFFERSIZE;j++)
			{
				MCB->buffer[i][j]= 0;
			}
		}
		MCB->head = 0;
		MCB->tail = 0;
		MCB->overflowCount = 0;
	}
}

// returns the amount of times the MCB has overflown;
unsigned char getMultiOverflow(MCBRef MCB){
	if (MCB != NULL){
		return MCB->overflowCount;
	}
}