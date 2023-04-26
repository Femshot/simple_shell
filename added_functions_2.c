#include "sshell.h"

/**
 * run_exe - Execute the command passed in
 * @av: Pointr to array of command and arguments
 * @path: Pointer to path string
 */
void run_exe(char **av, char *path)
{
	char *env[2];
	int wstatus;
	pid_t pl;

	env[0] = path;
	env[1] = NULL;
	pl = fork();
	if (pl == -1)
	{
		perror("Error:");
		exit(EXIT_FAILURE);
	}
	if (pl == 0)
	{
		if (execve(av[0], av, env) == -1)
			perror("Error:");
	}
	else
	{
		wait(&wstatus);
		free_safe_2(av);
	}
}

/**
 * check_command - Check if string is a command in PATH executales
 * @cmd: command string to check
 * @paths: Array of strings in environment path variable
 *
 * Return: path of command string
 */
char *check_command(char *cmd, char **paths)
{
	struct stat bt;
	char *full_path;
	int i, j, k = 0;

	while (paths[k] != NULL)
	{
		full_path = NULL;
		i = _strlen(cmd);
		j = _strlen(paths[k]);
		full_path = make_full_path(paths[k], cmd, i, j);
		if (stat(full_path, &bt) == 0)
		{
			free(cmd);
			return (full_path);
		}
		k++;
		free(full_path);
	}
	free(cmd);
	return (NULL);
}

/**
 * make_full_path - Append a command to path string
 * @a: Pointer to path string
 * @b: pointer to command
 * @c: length of command string
 * @d: leanth of pth string
 *
 * Return: POinter to appended full path string
 */
char *make_full_path(char *a, char *b, int c, int d)
{
	char *ptr = NULL;
	int i, j;

	ptr = malloc(sizeof(char) * c + d + 2);
	if (ptr == NULL)
		exit(EXIT_FAILURE);
	for (i = 0; a[i]; i++)
		ptr[i] = a[i];
	ptr[i++] = '/';
	for (j = 0; b[j]; i++, j++)
		ptr[i] = b[j];
	ptr[i] = '\0';
	return (ptr);
}

/**
 * _getenv - checks to find specific environment variable
 * @name: Path variable to get
 *
 * Return: Path environmnt variable
 */
char *_getenv(const char *name)
{
	int len = 0, ret = 0;

	len = _strlen(name);
	ret  = find_var(name, len);
	if (ret >= 0)
		return (environ[ret]);
	return (NULL);
}

/**
 * find_var - compares word search with environment variables
 * @name: Path environment name
 * @len: length of path name
 *
 * Return: Position of path in environment variable list
 */
int find_var(const char *name, int len)
{
	int i = 0, j = 0, k = 0, diff;

	while (environ[i])
	{
		while (environ[i][j] && name[k] && (j < len))
		{
			diff = environ[i][j] - name[k];
			if (diff != 0)
				break;
			j++;
			k++;
		}
		if (diff == 0)
			return (i);
		i++;
	}
	return (-1);
}
