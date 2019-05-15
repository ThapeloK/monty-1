#include "monty.h"

/**
 * main - entry point
 * Return: 0 or 1
 */
int main(int argc, char **argv)
{
	args_t args;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	args.argv = argv;
	args.counter = 0;
	args.line = NULL;
	args.stack = NULL;
	monty(&args);
	free_dlistint(args.stack);
	return (EXIT_SUCCESS);
}

/**
 * monty - monty
 */
void monty(args_t *args)
{
	FILE *file = fopen(args->argv[1], "r");
	char line [128];

	if (file != NULL)
	{
		while (fgets(line, sizeof line, file) != NULL)
		{
			args->counter++;
			args->line = line;
			caller(args);
		}
	       	fclose (file);
	}
	else
	{
		fprintf(stderr, "Error: Can't open file %s\n", args->argv[1]);
		exit(EXIT_FAILURE);
	}
}

/**
 * caller - caller
 */
void caller(args_t *args)
{
	instruction_t ins[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{"sub", sub},
		{"div", divide},
		{"mul", mul},
		{"mod", mod},
		{"pchar", pchar},
		{"pstr", pstr},
		{NULL, NULL}
	};
	int i = 0;
	char *op = NULL;

	/* if (*(args->line) == ' ' || *(args->line) == '\n') */
	/* 	return; */
	op = strtok(args->line, " \n");
	if (!op || *op == '#')
		return;
	while(ins[i].opcode && op)
	{
		if (!strcmp(op, ins[i].opcode))
		{
			return (ins[i].f(&(args->stack), args->counter));
		}
		i++;
	}
	fprintf(stderr, "L%ld: unknown instruction %s\n", args->counter, op);
	exit(EXIT_FAILURE);
}

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


void pint(stack_t **stack, unsigned int line_number)
{
	if (!*stack)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf(*stack-n);
}


		void pall(stack_t **stack, unsigned int line_number)
	{
		(void)line_number;
		print_dlistint(*stack);
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

void add(stack_t **stack, unsigned int line_number)
{
	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n += (*stack)->n;
	delete_dnodeint_at_index(stack, 0);
}

void sub(stack_t **stack, unsigned int line_number)
{
	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n -= (*stack)->n;
	delete_dnodeint_at_index(stack, 0);
}

void mul(stack_t **stack, unsigned int line_number)
{
	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n *= (*stack)->n;
	delete_dnodeint_at_index(stack, 0);
}

void divide(stack_t **stack, unsigned int line_number)
{
	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n /= (*stack)->n;
	delete_dnodeint_at_index(stack, 0);
}

void mod(stack_t **stack, unsigned int line_number)
{
	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n %= (*stack)->n;
	delete_dnodeint_at_index(stack, 0);
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


void nop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}



/**
 * add_dnodeint - adds a node at the beginning
 * @head: doubly linked list
 * @n: data of a node
 * Return: Doubly linked list
 */
		stack_t *add_dnodeint(stack_t **head, const int n)
		{
			stack_t *new_node = NULL;

			new_node = malloc(sizeof(stack_t));
			if (!new_node)
			{
				fprintf(stderr, "Error: malloc failed\n");
				exit(EXIT_FAILURE);
	}
	new_node->n = n;
	new_node->prev = NULL;

	new_node->next = *head;
	if (*head)
		(*head)->prev = new_node;
	*head = new_node;
	return (new_node);
}

/**
 * print_dlistint - prints doubly linked list
 * @h: doubly linked list
 * Return: Size of linked list
 */
size_t print_dlistint(const stack_t *h)
{
	size_t c = 0;

	while (h)
	{
		c++;
		printf("%d\n", h->n);
		h = h->next;
	}
	return (c);
}

/**
 * print_dlistint - prints doubly linked list
 * @h: doubly linked list
 * Return: Size of linked list
 */
size_t stack_size(const stack_t *h)
{
	size_t c = 0;

	while (h)
	{
		c++;
		h = h->next;
	}
	return (c);
}


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

/**
 * delete_dnodeint_at_index - Delete node at index
 * @head: Doubly linked list
 * @index: index
 * Return: 1 on success, -1 on failure
 */
int delete_dnodeint_at_index(stack_t **head, unsigned int index)
{
	stack_t *temp = *head;
	uint i = 0;

	if (!head || !*head)
		return (-1);
	if (index == 0)
	{
		*head = (*head)->next;
		if (*head)
			(*head)->prev = NULL;
		free(temp);
		return (1);
	}
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	if (index >= i)
		return (-1);
	temp = *head;
	while (temp && temp->next)
	{
		if (index == 0)
			break;
		index--;
		temp = temp->next;
	}
	temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	free(temp);
	return (1);
}


/**
 * free_dlistint - frees doubly linked list
 * @head: doubly linked list
 * Return: Nothing
 */
void free_dlistint(stack_t *head)
{
	stack_t *temp = head;

	while (head)
	{
		head = head->next;
		free(temp);
		temp = head;
	}
}
