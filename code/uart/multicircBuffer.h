#ifndef _OVERFLOWCBUFFER_H_
#define _OVERFLOWCBUFFER_H_

#include "apDefinitions.h"
#include "loggerDefinitions.h"


// Constructors - Destructors
// ==========================
// this Function returns a pointer to a new multi Circular Buffer

void OFB_init (void);

// this function frees the Multi Circular Buffer MCB Ref
/*void freeMultiCircBuffer (MCBRef* MCB);

// Accesor Methods
// ===============

// returns the amount of unread bytes in the circular buffer
unsigned int getMultiLength (MCBRef MCB);

// returns the actual index of the head
int readMultiHead (MCBRef MCB);

// returns the actual index of the tail
int readMultiTail (MCBRef MCB);

// returns the byte (actual value) that the head points to. this
// does not mark the byte as read, so succesive calls to peak will
// always return the same value
unsigned char Multipeak(MCBRef MCB, unsigned char outBuffer[DMABUFFERSIZE]);


// Manipulation Procedures
// ======================
// returns the front of the circular buffer and marks the byte as read
unsigned char readMultiFront (MCBRef MCB, unsigned char outBuffer[DMABUFFERSIZE]);

// writes one byte at the end of the circular buffer, returns 1 if overflow occured
unsigned char writeMultiBack (MCBRef MCB, unsigned char inBuffer[DMABUFFERSIZE]);

// empties the circular buffer. It does not change the size. use with caution!!
void makeMultiEmpty (MCBRef MCB);

// returns the amount of times the CB has overflown;
unsigned char getMultiOverflow(MCBRef MCB);
*/


#endif
