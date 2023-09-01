#include "main.h"
/**
 * get_bit - it retrieves bit value at an index in a decimal num.
 * @n: Num. to inspect
 * @index:the bit index
 *
 * return: Bit value (one  or zero)
 */
int get_bit(unsigned long int n, unsigned int index)
{
	int bit_val;
	if (index > 63)
		return (-1);
	bit_val = (n >> index) & 1;
	return (bit_val);
}
