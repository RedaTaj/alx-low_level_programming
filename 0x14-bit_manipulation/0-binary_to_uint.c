#include "main.h"

/**
 * binary_to_uint - Converts a binary string to an unsigned int
 * @b: Binary string to be converted
 *
 * Description:
 * This function converts a binary string into an unsigned integer.
 * The input string must exclusively consist of '0' and '1'. After
 * interpreting the string as a base-2 number, the function computes
 * the equivalent decimal value.
 *
 * Return: The converted unsigned int.
 * If the input string is not valid (NULL or containing non-binary characters),
 * the function returns 0.
 */
unsigned int binary_to_uint(const char *b)
{
	int z;
	unsigned int dec_val = 0;

	if (!b)
		return (0);

	for (z = 0; b[z]; z++)
	{
		if (b[z] < '0' || b[z] > '1')
			return (0);
		dec_val = 2 * dec_val + (b[z] - '0');
	}

	return (dec_val);
}

