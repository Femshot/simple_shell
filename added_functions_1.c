#include "sshell.h"

/**
 * _strlen - Determines the length of input string
 * @s: Address od string to be measured
 *
 * Return: Length of string
 */
int _strlen(const char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - Prints inputed string to stdout
 * @str: String to to printed
 */
void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
	_putchar('\n');
}

/**
 * _strdup - Copies the value of a string to a newly allocated memory space
 * @str: Pointer to  string to be copied
 *
 * Return: Pointer to new duplicate string, NULL if failed to create space
 */
char *_strdup(char *str)
{
	char *ptr;
	int i, len = 0;

	if (str == NULL)
		return (NULL);
	while (*(str + len))
		len++;
	ptr = malloc((len + 1) * sizeof(*ptr));
	if (ptr == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
		*(ptr + i) = *(str + i);
	*(ptr + i) = '\0';
	return (ptr);
}

/**
 * make_copy - Make a copy of string passed into it
 * @str: Pointer to string to be copied
 *
 * Return: Pointer to address of the copy if succesful
 */
char *make_copy(char *str)
{
	char *ptr = NULL;

	ptr = _strdup(str);
	if (ptr == NULL)
	{
		_puts("Unable to allocate duplicate string");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
