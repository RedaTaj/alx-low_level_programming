#include "main.h"
#include <stdlib.h>
/**
 * read_textfile - Reads a text file and prints it into STDOUT.
 * @filename: The path to the txt file to be read.
 * @letters: The num. of chars to be read.
 * Return: Returns w- the actual num. of bytes read and printed.
 *         0 when the funcs. fails or if the filename is defined as NULL.
 */
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

ssize_t read_textfile(const char *filename, size_t letters)
{
    char *buf;
    ssize_t fd;
    ssize_t w;
    ssize_t t;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (-1);

    buf = malloc(sizeof(char) * letters);
    if (buf == NULL) {
        close(fd);
        return (-1);
    }

    t = read(fd, buf, letters);
    if (t == -1) {
        free(buf);
        close(fd);
        return (-1);
    }

    w = write(STDOUT_FILENO, buf, t);

    free(buf);
    close(fd);

    return (w);
}


