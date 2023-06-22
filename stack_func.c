#include "monty.h"
/**
 * pushf - push int to a stack
 * @stack: linked lists for monty stack
 * @line_number: number of line opcode occurs on
 */
void pushf(stack_t **filestack, __attribute__ ((unused))unsigned int line_number)
{
	stack_t *fileop;
	(void)line_number;

	fileop = malloc(sizeof(stack_t));
	if (fileop == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	fileop->n = var_global.push_arg;
	fileop->next = *filestack;
	fileop->prev = NULL;
	if (*filestack != NULL)
		(*filestack)->prev = fileop;
	*filestack = fileop;
}

/**
 * pallf - print all function
 * @stack: pointer to linked list stack
 * @line_number: number of line opcode occurs on
 */
void pallf(stack_t **stack, __attribute__ ((unused))unsigned int line_number)
{
	stack_t *runner;

	runner = *stack;
	while (runner != NULL)
	{
		printf("%d\n", runner->n);
		runner = runner->next;
	}
}

/**
 * pintfunc - print int a top of stack
 * @stack: pointer to linked list stack
 * @line_number: number of line opcode occurs on
 *
 */
void pintfunc(stack_t **stack, unsigned int line_number)
{
	stack_t *runner;

	runner = *stack;
	if (runner == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", runner->n);
}

/**
 * popfunc - remove element a list
 *@stack: pointer to first node
 *@line_number: integer
 *Return: void
 */
void popfunc(stack_t **stack, unsigned int line_number)
{
	stack_t *nodo = *stack;

	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	*stack = nodo->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(nodo);
}

/**
 * listfree - free a list
 * @head: pointer to first node
 *
 */
void listfree(stack_t *head)
{
	stack_t *tmp;

	while (head != NULL)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
