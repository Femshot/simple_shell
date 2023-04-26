#include "sshell.h"

/**
 * checking_built - Checks command passed for special buitlins commands
 * @arr: Pointer to commands & arguments passed
 *
 * Return: 0 if command find succesful, -1 if failed
 */
int checking_built(char **arr)
{
	int i, j, len_input;
	builtins_f check[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{"\n", print_newprompt},
		{NULL, NULL}
	};

	i = j = 0;
	for (len_input = 0; arr[0][len_input] != '\0'; len_input++)
		;
	while (check[i].command != NULL)
	{
		j = 0;
		while (j < len_input)
		{
			if (check[i].command[j] != arr[0][j])
				break;
			j++;
		}
		if (check[i].command[j] == arr[0][j])
		{
			check[i].ptr(arr);
			return (0);
		}
		i++;
	}
	/*free_safe_2(arr);*/
	return (1);
}

/**
 * exit_shell - Exits shell upon exit command
 * @arr: Pointer to command & arguments passed
 */
void exit_shell(char **arr)
{
	int num = 0;

	if (arr[1]  == NULL)
	{
		free_safe_2(arr);
		_exit(0);
	}
	num = _atoi(arr[1]);
	free_safe_2(arr);
	_exit(num);
}

/**
 * print_env - Prints enviroment variables upon "env" command
 * @arr: Pointer to command & arguments passed
 */
void print_env(char **arr)
{
	int i = 0;
	(void)arr;

	while (environ[i])
	{
		_puts(environ[i]);
		i++;
	}
	free_safe_2(arr);
}

/**
 * print_newprompt - Prints a new shell prompt
 * @arr: Pointer to array of string
 */
void print_newprompt(char **arr)
{
	free(arr);
}

/**
 * free_safe_2 - Free array of malloc'd spaces
 * @pointer: Pointer to array of malloc'd spaces
 */
void free_safe_2(char **pointer)
{
	int i = 0;

	if (pointer != NULL)
	{
		while (pointer[i] != NULL)
		{
			free(pointer[i]);
			i++;
		}
		free(pointer[i]);
		free(pointer);
		pointer = NULL;
	}
}
