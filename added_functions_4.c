#include "sshell.h"

/**
 * start_prompt - Starts the shell prompt
 * @s: Pointer to get line input
 */
void start_prompt(char **s)
{
	*s = NULL;
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * print_error - Prints error message if command unrecgnised
 * @pg: Program name
 * @cmd: Command typed
 * @av: Array of command arguments
 */
int print_error(char *pg, char *cmd, char **av)
{
	static int i = 1;

	_puts2(pg);
	_puts2(": ");
	print_number(i);
	_puts2(": ");
	_puts2(cmd);
	_puts2(": not found");
	_putchar('\n');
	i++;
	free_safe_2(av);
	return (127);
}

/**
 * _puts2 - Prints inputed string to stdout without a newline
 * @str: String to to printed
 */
void _puts2(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
}

/**
 * end_prompt - Ends shell prompt
 * @p: Pointer to line input string
 */
void end_prompt(char *p, int q)
{
	free(p);
	if (isatty(STDIN_FILENO))
		_putchar('\n');
	if (q == 127)
		exit(127);
}

/**
 * _atoi - Converts an integar string into an integar
 * @s: Integar string to be converted
 *
 * Return: 0 if no intergar string found else integar number
 */
int _atoi(char *s)
{
	int sign = 1, num_end = 0;
	unsigned int total = 0;

	while (*s != '\0')
	{
		if (*s == '-')
			sign *= -1;

		if (*s >= '0' && *s <= '9')
		{
			num_end = 1;
			total = total * 10 + *s - '0';
		}
		else if (num_end)
			break;
		s++;
	}

	if (sign < 0)
		total = (-total);

	return (total);
}
