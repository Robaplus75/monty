#include "monty.h"
/**
 * handlefile - reads a bytecode file and runs commands
 * @textfile: pathname to file
 * @memstack: pointer to the top of the stack
 */
void handlefile(char *textfile, stack_t **memstack)
{
	char *command;
	size_t j = 0;
	int line_size = 1, check, l;
	instruct_func k;

/*this opens the file*/
	var_global.file = fopen(textfile, "r");

	if (var_global.file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", textfile);
		exit(EXIT_FAILURE);
	}

	while ((l = getline(&var_global.buffer, &j, var_global.file)) != -1)
	{
		command = parse_line(var_global.buffer, memstack, line_size);
		if (command == NULL || command[0] == '#')
		{
			line_size++;
			continue;
		}
		k = get_op_func(command);
		if (k == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_size, command);
			exit(EXIT_FAILURE);
		}
		k(memstack, line_size);
		line_size++;
	}
	free(var_global.buffer);
	check = fclose(var_global.file);
	if (check == -1)
		exit(-1);
}

/**
 * get_op_func -  checks opcode and returns the correct function
 * @str: the opcode
 * Return: returns a functions, or NULL on failure
 */
instruct_func get_op_func(char *str)
{
	int i;

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

	i = 0;
	while (instruct[i].f != NULL && strcmp(instruct[i].opcode, str) != 0)
	{
		i++;
	}

	return (instruct[i].f);
}

/**
 * isnumber - checks if a string is a number
 * @str: string being passed
 * Return: returns 1 if string is a number, 0 otherwise
 */
int isnumber(char *str)
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
 * parse_line - parses a line for an opcode and arguments
 * @line: the line to be parsed
 * @stack: pointer to the head of the stack
 * @line_number: the current line number
 * Return: returns the opcode or null on failure
 */
char *parse_line(char *line, stack_t **stack, unsigned int line_number)
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
		if (isnumber(arg) == 1 && arg != NULL)
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
