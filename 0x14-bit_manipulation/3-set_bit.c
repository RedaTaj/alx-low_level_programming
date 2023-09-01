#include "main.h"
/**
 * set_bit - Sets bit at index to one in num.
 * @n: the pointer to num. to modify
 * @index: Bit index to set to one
 *
 * Return:  -1 for error and 1 for success
 */
int set_bit(unsigned long int *n, unsigned int index)
{
	if (index > 63)
		return (-1);
	*n = ((1UL << index) | *n);
	return (1);
}
