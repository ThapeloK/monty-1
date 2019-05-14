#include "monty.h"

/**
 * main - entry point
 * Return: 0 or 1
 */
int main(int argc, char **argv)
{
	extern args_t gl;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	gl.argc = argc;
	gl.argv = argv;
	gl.counter = 0;
	gl.line = NULL;
	gl.stack = NULL;
	monty();
	return (EXIT_SUCCESS);
}

/**
 * monty - monty
 */
void monty(void)
{
	FILE *file = fopen(gl.argv[1], "r");
	char line [128];

	if (file != NULL)
	{
		while (fgets(line, sizeof line, file) != NULL)
		{
			gl.counter++;
			gl.line = line;
			caller();
		}
		fclose (file);
	}
	else
	{
		fprintf(stderr, "Error: Can't open file %s\n", gl.argv[1]);
		exit(EXIT_FAILURE);
	}
}

/**
 * caller - caller
 */
void caller()
{
	instruction_t ins[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{NULL, NULL}
	};
	int i = 0;
	char *op = strtok(gl.line, " \n");

	while(ins[i].opcode && op)
	{
		if (!strcmp(op, ins[i].opcode))
		{
			return (ins[i].f(&(gl.stack), gl.counter));
		}
		i++;
	}
	fprintf(stderr, "L%ld: unknown instruction %s\n", gl.counter, op);
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
	char *param = strtok(NULL, " \n");
	int n = atoi(param);
	(void)line_number;

	*stack = add_dnodeint(stack, n);
}


void pall(stack_t **stack, unsigned int line_number)
{
	(void)line_number;
	print_dlistint(*stack);
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
