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