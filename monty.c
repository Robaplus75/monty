#include "monty.h"
global_var var_global;
/**
 * main - driver function for monty program
 * @argcount: int num of arguments
 * @argvv: opcode file
 * Return: 0
 */
int main(int argcount, char **argvv)
{
	stack_t *stack;

	stack = NULL;
	if (argcount != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	read_file(argvv[1], &stack);
	listfree(stack);
	return (0);
}
