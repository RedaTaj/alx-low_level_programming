#include "main.h"
/**
 * append_text_to_file - Appends txt to a file.
 * @filename: Ptr to the file name.
 * @text_content: String to append.
 *
 * Return: Failure or filename is defined as NULL - -1.
 *      Non-existent files or insufficient write perms - -1.
 *      Success - 1.
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int o, w, len = 0;

	if (filename == NULL)
		return (-1);

	o = open(filename, O_WRONLY | O_APPEND);
	if (o == -1)
		return (-1);

	if (text_content != NULL)
	{
		for (len = 0; text_content[len];)
			len++;
	}

	w = write(o, text_content, len);
	if (w == -1)
	{
		close(o);
		return (-1);
	}

	close(o);

	return (1);
}

