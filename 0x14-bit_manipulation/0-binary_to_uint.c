#include "main.h"
/**
 * binary_to_uint - a binary string to the unsigned int conversion
 * @b: Binary string the needs to be converted
 * Summary:
 * this converts a binary string into an unsigned integer. The input string must
 * exclusively consist of '0' and also '1'. after interpreting the string as a base-2
 * number, the function computes the equivalent as decimal value.
 * Returns:
 * The converted non assigned integer. If the input string is not valid (NULL or
 * containing nonbinary characters), the function gives 0.
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
