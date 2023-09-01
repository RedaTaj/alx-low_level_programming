#include "main.h"
/**
 * get_endianness - it checks the machine's endianness
 * Return:  one for little and 0 for big
 */ 
int get_endianness(void)
{
	unsigned int i = 1;
	char *c = (char *) &i;
	return (*c);
}
