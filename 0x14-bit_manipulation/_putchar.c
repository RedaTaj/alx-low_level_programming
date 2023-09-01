#include "main.h"
#include <unistd.h>

/**
 * _putchar - Writes a character to standard output.
 * @c: The character to be written.
 *
 * Description: The function writes a single character to the standard
 * output (stdout). It takes a character as an argument and sends it to
 * the standard output stream immediately.
 *
 * Return: 1 on success. On error, returns -1 and sets the appropriate
 * error code in errno.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

