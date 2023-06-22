#include "monty.h"
/**
 * pushf - push int data to stack
 * @stak: the list of stack
 * @line_number: num of lines
 */
void pushf(stack_t **stak, __attribute__ ((unused))unsigned int line_number)
{
	stack_t *stacktop;
	(void)line_number;

/*allocates memory for stacktop*/
	stacktop = malloc(sizeof(stack_t));
	if (stacktop == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
/*assinging values*/
	stacktop->n = var_global.push_arg;
	stacktop->next = *stak;
	stacktop->prev = NULL;
	if (*stak != NULL)
		(*stak)->prev = stacktop;
	*stak = stacktop;
}

/**
 * pallf - output all funcs
 * @tack: poiter to stack
 * @line_number: number of lines
 */
void pallf(stack_t **tack, __attribute__ ((unused))unsigned int line_number)
{
	stack_t *begin = *tack;

/*tHE PRINTING PART*/
	while (begin != NULL)
	{
		printf("%d\n", begin->n);
		begin = begin->next;
	}
}

/**
 * pintfunc - output the top of stack
 * @tack: pointer to stack
 * @line_number: number of lines
 *
 */
void pintfunc(stack_t **tack, unsigned int line_number)
{
	stack_t *begin = *tack;

	if (begin == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", begin->n);
}

/**
 * popfunc - kickout elemetn fo a list
 *@tack: pointer to stack
 *@line_number: number of lines
 *Return: none
 */
void popfunc(stack_t **tack, unsigned int line_number)
{
	stack_t *nth = *tack;

/*checks if tack is Null or not*/
	if (tack == NULL || *tack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
/*setting values*/
	*tack = nth->next;
	if (*tack != NULL)
		(*tack)->prev = NULL;
	free(nth);
}

/**
 * listfree - frees or removes the list
 * @tophead: poitner to node
 *
 */
void listfree(stack_t *tophead)
{
	stack_t *temporary;

/*frees the tophead*/
	while (tophead != NULL)
	{
		temporary = tophead->next;
		free(tophead);
		tophead = temporary;
	}
}
