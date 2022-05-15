#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 


typedef unsigned char byte;
typedef unsigned int u32;

#define BIT_SET(byte,nbit)   ((byte) |=  (1<<(nbit)))
#define BIT_CLEAR(byte,nbit) ((byte) &= ~(1<<(nbit)))
#define BIT_FLIP(byte,nbit)  ((byte) ^=  (1<<(nbit)))
#define BIT_CHECK(byte,nbit) ((byte) &   (1<<(nbit)))
