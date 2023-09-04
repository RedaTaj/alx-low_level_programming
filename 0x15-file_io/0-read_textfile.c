#include "main.h"
#include <stdlib.h>
/**
 * read_textfile - Reads a text file and prints it into STDOUT.
 * @filename: The path to the txt file to be read.
 * @letters: The num. of chars to be read.
 * Return: Returns w- the actual num. of bytes read and printed.
 *         0 when the funcs. fails or if the filename is defined as NULL.
 */

ssize_t read_textfile(const char *filename, size_t letters)
{
    ssize_t fd;
    ssize_t t;
    ssize_t w;
    char *buf;

    buf = malloc(sizeof(char) * letters);
    if (buf == NULL)
    {
        return (-1); 
    }

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        free(buf);
        return (0);
    }

    t = read(fd, buf, letters);
    if (t == -1)
    {
        free(buf);
        close(fd);
        return (-1);
    }

    w = write(STDOUT_FILENO, buf, t);

    free(buf);
    close(fd);

    return (w);
}

