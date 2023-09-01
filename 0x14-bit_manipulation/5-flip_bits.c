#include "main.h"

/**
 * flip_bits - Calculates the number of differing bits between two numbers.
 * @n: First number.
 * @m: Second number.
 *
 * Return: Number of differing bits.
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	int i, count = 0;
	unsigned long int current;
	unsigned long int exclusive = n ^ m;

	for (i = 63; i >= 0; i--)
	{
		current = exclusive >> i;
		if (current & 1)
			count++;
	}

	return (count);
}

