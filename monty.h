#ifndef __MONTY__
#define __MONTY__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * struct arguments - Values to be accessed by various functions
 * @argv: Name of the executable
 * @argc: argument count
 */
typedef struct arguments
{
	/* int count; */
	char **argv;
	int argc;
	ssize_t counter;
	char *line;
} args_t;


void monty(args_t *); /*main.c*/
void caller(args_t *args);

/*    Global Variable, i.e. stack   */
stack_t *global = NULL;

#endif /*__MONTY__*/
