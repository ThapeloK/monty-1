#include "monty.h"

/**
 * pint - prints out everything in stack
 * @stack: doubly linked list
 * @line_number: the line
 *
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (!*stack)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * check_string - verify if argument is alpha
 * @s: string passed to function
 *
 */
int check_string(char *s)
{
	int i = 0;

	while(s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			i++;
		}
		else
			return (-1);
	}
	return (1);
}

void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	(void) line_number;
	if (!*stack)
	{
		printf("\n");
	}
	else if (temp || (temp->n >= 32 && temp->n > 126) || temp->n)
	{
		printf("%c", temp->n);
		temp = temp->next;
	}
}


void pchar(stack_t **stack, unsigned int line_number)
{
	if (!*stack)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n < 32 || (*stack)->n > 126)
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%c\n", (*stack)->n);
}
