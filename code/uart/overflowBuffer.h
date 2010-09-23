#ifndef _OVERFLOWBUFFER_H_
#define _OVERFLOWBUFFER_H_

#include "apDefinitions.h"
#include "loggerDefinitions.h"


// Constructors - Destructors
// ==========================
// this Function returns a pointer to a new multi Circular Buffer

void OFB_init (int idcode);

// Accesor Methods
// ===============

// returns the amount of unread bytes in the circular buffer
unsigned int OFB_getSize(void);

// returns the head array
int OFB_read_tail(unsigned char outputarray[]);

int OFB_pop(void);

int OFB_push(unsigned char inbuffer[]);

// writes one byte at the end of the circular buffer, returns 1 if overflow occured


unsigned char calc_checksum(unsigned char inBuffer[]);

#endif
