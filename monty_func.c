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
		command = parsline(var_global.buffer, memstack, line_size);
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
	instruction_t instruct[] = {
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
	while (instruct[num].f != NULL && strcmp(instruct[num].opcode, strr) != 0)
	{
		num++;
	}

	return (instruct[num].f);
}

/**
 * checknum - checks if a string is a number
 * @str: string being passed
 * Return: returns 1 if string is a number, 0 otherwise
 */
int checknum(char *str)
{
	unsigned int i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[0] == '-')
		{
			i++;
			continue;
		}
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * parsline - parses a line for an opcode and arguments
 * @line: the line to be parsed
 * @stack: pointer to the head of the stack
 * @line_number: the current line number
 * Return: returns the opcode or null on failure
 */
char *parsline(char *line, stack_t **stack, unsigned int line_number)
{
	char *op_code, *push, *arg;
	(void)stack;

	push = "push";
	op_code = strtok(line, "\n ");
	if (op_code == NULL)
		return (NULL);

	if (strcmp(op_code, push) == 0)
	{
		arg = strtok(NULL, "\n ");
		if (checknum(arg) == 1 && arg != NULL)
		{
			var_global.push_arg = atoi(arg);
		}
		else
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
	}
	return (op_code);
}
