#include "main.h"
#include <unistd.h>

/**
 * _putchar - Write the chars to a standard output
 * @c: is the char to be written
 *
 * the goal of this function is to write a single chat to the standard output (stdout).
 * It makes a char as an argument and sends it to the standard output stream immediately
 *
 * Return: returns 1 on success. On error, it returns -1 and sets the appropriate
 * error code in an errno.
 */
int _putchar(char c)
{
    return (write(1, &c, 1));
}
