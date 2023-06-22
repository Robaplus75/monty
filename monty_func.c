#include "monty.h"
/**
 * handlefile - runs command and reads a bytecode file
 * @textfile: the file
 * @memstack: its the top of stack
 */
void handlefile(char *textfile, stack_t **memstack)
{
	int line_size = 1, tester, l;
	instruct_func k;
	size_t j = 0;
	char *command;

/*this opens the file*/
	var_global.file = fopen(textfile, "r");
/*tocheck if its null*/
	if (var_global.file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", textfile);
		exit(EXIT_FAILURE);
	}

	while ((l = getline(&var_global.buffer, &j, var_global.file)) != -1)
	{
/*gets the command*/
		command = pline(var_global.buffer, memstack, line_size);
		if (command == NULL || command[0] == '#')
		{
			line_size++;
			continue;
		}
		k = opfunc(command);
/*for printing error*/
		if (k == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_size, command);
			exit(EXIT_FAILURE);
		}
		k(memstack, line_size);
		line_size++;
	}
/*frees the global variable*/
	free(var_global.buffer);
/*closes the opened file*/
	tester = fclose(var_global.file);
/*checks for the tester*/
	if (tester == -1)
		exit(-1);
}

/**
 * opfunc -  checks for op code
 * @strr: its  the op code
 * Return: a function or NULL
 */
instruct_func opfunc(char *strr)
{
	int num = 0;
/*the command chekcer*/
	instruction_t instarr[] = {
		{"push", pushf},
		{"pall", pallf},
		{"pint", pintfunc},
		{"pop", popfunc},
		{"swap", swapfunc},
		{"add", addfunc},
		{"nop", nopfunc},
		{NULL, NULL},
	};
/*checks for errors or if its null*/
	while (strcmp(instarr[num].opcode, strr) != 0 && instarr[num].f != NULL)
	{
		num++;
	}

	return (instarr[num].f);
}

/**
 * isnumber - is it a number?
 * @stringg: the string to be checked
 * Return: 1 if true, 0 else
 */
int isnumber(char *stringg)
{
	unsigned int num = 0;
/*checks if sth is instered or not*/
	if (stringg == NULL)
		return (0);
	while (stringg[num])
	{
		if (stringg[0] == '-')
		{
			num++;
			continue;
		}
/*ths is digit function initiated*/
		if (!isdigit(stringg[num]))
			return (0);
		num++;
	}
	return (1);
}

/**
 * pline - for parsing th eline
 * @line: the line that is going to be parsed
 * @stack: pointer to the head of stack
 * @numline: line number
 * Return: returns opcode
 */
char *pline(char *line, stack_t **stack, unsigned int numline)
{
	char *opcod, *args;
	(void)stack;
/*breaks down opcod*/
	opcod = strtok(line, "\n ");
	if (opcod == NULL)
		return (NULL);

/*checks if opcod and push r z same*/
	if (strcmp(opcod, "push") == 0)
	{
		args = strtok(NULL, "\n ");
		if (isnumber(args) == 1 && args != NULL)
		{
			var_global.push_arg = atoi(args);
		}
		else
		{
			fprintf(stderr, "L%d: usage: push integer\n", numline);
			exit(EXIT_FAILURE);
		}
	}
	return (opcod);
}
