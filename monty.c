#include "monty.h"
gvar globalvar;
/**
 * main - the main file
 * @argcount: number of arguments
 * @argvv: the opcode
 * Return: zero
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
    else
	{
	}

/*reads the file and executes the appropirate command*/
	handlefile(argvv[1], &stack);
/*frees the stack*/
	listfree(stack);
	return (0);
}
