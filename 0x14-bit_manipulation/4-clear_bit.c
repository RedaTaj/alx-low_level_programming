#include "main.h"
/**
 * clear_bit - this function clears the bit to a specified index in a number
 * @n: Ptr. to number to modify
 * @index: Index of the bit to be cleared
 *
 * return:  -1 on error and 1  if succeeded,
 */
int clear_bit(unsigned long int *n, unsigned int index)
{
	if (index > 63)
		return (-1);
	*n = (~(1UL << index) & *n);
	return (1);
}
