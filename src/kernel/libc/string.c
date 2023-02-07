#include "libc/string.h"

char* atoi(int value, int base){
	static char repr[]= "0123456789abcdef";
	static char buffer[50]; 
	char *ptr; 

	ptr = &buffer[49]; 
	*ptr = '\0'; 

	do {
		*--ptr = repr[value%base]; 
		value /= base; 
	}while(value != 0); 

	return(ptr); 
}

void* memset(void *dest, int val, unsigned long len){
  unsigned char *ptr = dest;
  while (len-- > 0) *ptr++ = val;
  return dest;
}