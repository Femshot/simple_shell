#include "sshell.h"

/**
 * main - Point of entry of simple shell execution
 * @ac: Number of arguments passed to program
 * @av: Array of Arguments strings passed to program
 *
 * Return: 0 on success, -1 on failure, Errno is set appropraitely
 */
int main(int ac, char **av)
{
	char *lineptr, *pat, **path_ev, *bv, *cv;
	size_t num = 0;
	int count = 0, count_2 = 0, chk, ret = 0;
	struct stat st;

	(void) ac;
	bv = av[0];
	while (1)
	{
		start_prompt(&lineptr);
		ret = getline(&lineptr, &num, stdin);
		if (ret == -1)
			break;
		count = count_tokens(lineptr);
		av = create_token_array(lineptr, count);
		chk = checking_built(av);
		if (chk == 1)
		{
			pat = _getenv("PATH");
			count_2 = count_path_tokens(pat);
			path_ev = path_list(pat, count_2);
			if (stat(av[0], &st) == 0)
				run_exe(av, pat);
			else
			{
				cv = make_copy(av[0]);
				av[0] = check_command(av[0], path_ev);
				if (av[0] != NULL)
					run_exe(av, pat);
				else
					print_error(bv, cv, av);
				free(cv);
			}
			free_safe_2(path_ev);
		}
		free(lineptr);
	}
	end_prompt(lineptr);
	return (0);
}

/**
 * count_tokens - Count the number of tokens in a string
 * @str: Pointer to string
 *
 * Return: Number of tokens in string
 */
int count_tokens(char *str)
{
	int count = 0;
	char *token, *ptr = NULL;

	if (str == NULL)
		exit(EXIT_FAILURE);
	if (str[0] == '\n')
		return (1);
	ptr = make_copy(str);
	token = strtok(ptr, " \t\n");
	/*if (token == NULL)  added this*/
		/*return (1);*/
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t\n");
	}
	free(ptr);
	return (count);
}

/**
 * create_token_array - Create an array of tokens from a string
 * @str: Pointer to string
 * @count: Number of tokens in string
 *
 * Return: POinter to array of tokens created
 */
char **create_token_array(char *str, int count)
{
	char **av =  NULL, *token = NULL, *ptr;
	int i = 0;

	av = malloc(sizeof(char *) * (count + 1));
	if (av == NULL)
	{
		_puts("Unable to allocate memory space");
		exit(EXIT_FAILURE);
	}

	if (*str == '\n') /*added this*/
	{
		av[i] = "\n";
		return (av);
	}
	ptr = make_copy(str);
	token = strtok(ptr, " \n");
	while (token != NULL)
	{
		av[i] = make_copy(token);
		token = strtok(NULL, " \n");
		i++;
	}
	av[i] = NULL;
	free(ptr);
	return (av);
}

/**
 * count_path_tokens - count the number of token, paths in path string
 * @str: Pointer to string
 *
 * Return: Number of tokens in path string counted
 */
int count_path_tokens(char *str)
{
	int count = 0;
	char *token, *ptr = NULL;

	if (str == NULL)
	{
		_puts("PATH Environment Unavailable");
		exit(EXIT_FAILURE);
	}
	ptr = make_copy(str);
	token = strtok(ptr, "=:\n");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, ":\n");
	}
	free(ptr);
	return (count);
}

/**
 * path_list - Create array of tokens, path string from path environment string
 * @str: Pointer to  string
 * @count: Number of tokens in path
 *
 * Return: Pointer to array of strings in path
 */
char **path_list(char *str, int count)
{
	char **av = NULL, *token = NULL, *ptr;
	int i = 0;

	av = malloc(sizeof(char *) * (count));
	if (av == NULL)
	{
		_puts("Unable to allocate memory space");
		exit(EXIT_FAILURE);
	}
	ptr = make_copy(str);
	token = strtok(ptr, "=:\n");
	token = strtok(NULL, ":\n");
	while (token != NULL)
	{
		av[i] = make_copy(token);
		token = strtok(NULL, ":\n");
		i++;
	}
	av[i] = NULL;
	free(ptr);
	return (av);
}
