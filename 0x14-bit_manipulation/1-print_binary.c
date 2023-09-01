#include "main.h"
/**
 * print_binary - this code displays the binary. equiv. of a decimal num.
 * @n: Num. to show in binary.
 */
void print_binary(unsigned long int n)
{
        int z, count = 0;
        unsigned long int current;
        for (z = 63; z >= 0; z--)
        {
                current = n >> z;
                if (current & 1)
                {
                        _putchar('1');
                        count++;
               }
                else if (count)
                        _putchar('0');
        }
        if (!count)
                _putchar('0');
}
