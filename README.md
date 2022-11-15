#Simple Shell Project

Repository Description
This repository contains the files to simulate a basic Unix Shell with its respective commands. It uses the POSIX API to implement many of the same functionalities of the first Ken Thompson's Shell and It is made to carry out the 0x16. C - simpleshell project.

The predominantly used calls are read, write, open, execve, exit, fflush, fork, free, malloc, getline, isatty, perror, strtok, wait, and waitpid.

This simple shell is a Shell interface written in C programming language that gives to the user a prompt *Hell_Shell>> *, after it accepts, it executes a user inputted command in a separate process called child process.

This shell provides the following features:
This program displays a prompt and waits that the user types a command. A command line always ends with a new line (when user push ENTER key).
The prompt is displayed again each time a command has been executed.
When the user enters exit, Hell shell will end and returns the status 0.
When the user enters exit [status], Hell Shell will end and returns the inputted status, where status is a value from 0 to 255.
The user could stop the program using Ctrl+D (end of file).
The shell handles the command lines with arguments and pathways.
The program does not quit when the user imputs ^C (Ctrl+C).
The program prints the current enviroment when the user types env.
This program executes the most common shell commands as ls, grep, find, pwd, rm, cp, mv, exit, env, history, etc... with arguments.
If an executable cannot be found, It prints an error message and displays the prompt again.
This Shell supports commentaries using #,
The Hell Shell does NOT support wildcard characters such as ls *.dat in parameters (or commands).
This shell does NOT support pipes |, shell logical operators as && or ||, neither commands separator ;.
Process Description
The next steps are a brief description about how the shell works:

First, the parent process is created when the user run the program.
Then, the isatty() function using STDIN_FILENO file descriptor -fd- to tests if there is an open file descriptor referring to a terminal. If isatty() returns 1, the prompt is showed using write() with STDOUT_FILENO as fd and waits for an input user command line.
When the user types a command, getline() function reads an entire line from the stream and strtok() function breaks the inputted command into a sequence of non-empty tokens.
Next, it creates a separate child process suing fork() that performs the inputted command. Unless otherwise is specified, the parent process waits for the child to exit before continuing.
After tokening the command, execve() function brings and executes it, the it frees all allocated memory with free().
Finally, the program returns to main process: prints the prompt, and waits for another user input.

**Requirements**

General
Allowed editors: vi, vim, emacs
All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
All your files should end with a new line
A README.md file, at the root of the folder of the project is mandatory
Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
Your shell should not have any memory leaks
No more than 5 functions per file
All your header files should be include guarded
Use system calls only when you need to (why?)
Write a README with the description of your project
You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker
