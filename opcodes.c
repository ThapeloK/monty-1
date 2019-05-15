#include "monty.h"

/**
 * push - adds data to top of stack
 * @stack: doubly linked list
 * @line_number: the line
 *
 */
void push(stack_t **stack, unsigned int line_number)
{
	char *param = strtok(NULL, " \n");
	int n;

	if (check_string(param) == -1)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	n = atoi(param);

	 *stack = add_dnodeint(stack, n);
 }

void pop(stack_t **stack, unsigned int line_number)
{
	if (!*stack)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	delete_dnodeint_at_index(stack, 0);
}

void swap(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
}

void nop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}

void pall(stack_t **stack, unsigned int line_number)
{
		(void)line_number;
		print_dlistint(*stack);
}
