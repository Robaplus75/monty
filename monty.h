#ifndef MON_T_Y
#define MON_Y_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

extern int push_arg;

/**
 * struct instruction_s - opcoode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * struct g_var - the opecodes and functions collection
 * @file: its opcode
 * @push_arg: handles the opcode
 * @buffer: the pointer
 */
typedef struct g_var
{
	FILE *file;
	char *buffer;
	int push_arg;
} gvar;

extern gvar globalvar;
/*the file hander is hadnlefile function*/
void handlefile(char *textfile, stack_t **memstack);
char *pline(char *line, stack_t **stack, unsigned int numline);
/*the typedef func*/
typedef void (*instruct_func)(stack_t **stack, unsigned int line_number);
/*inst func*/
instruct_func opfunc(char *strr);


void pushf(stack_t **stak, unsigned int line_number);
/*some of useful functios*/
void pintfunc(stack_t **tack, unsigned int line_number);
void listfree(stack_t *tophead);
void pallf(stack_t **tack, unsigned int line_number);
void popfunc(stack_t **tack, unsigned int line_number);

#endif
