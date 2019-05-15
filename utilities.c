#include "monty.h"

/**
 * monty - custom interpretor
 * @args: the argument to be interpreted
 *
 */
void monty(args_t *args)
{
	FILE *file = fopen(args->argv[1], "r");
	char line[128];

	if (file != NULL)
	{
		while (fgets(line, sizeof(line), file) != NULL)
		{
			args->counter++;
			args->line = line;
			caller(args);
		}
		fclose(file);
	}
	else
	{
		fprintf(stderr, "Error: Can't open file %s\n", args->argv[1]);
		exit(EXIT_FAILURE);
	}
}

/**
 * caller - caller
 * @args: arguments passed to function
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

	op = strtok(args->line, " \n");
	if (!op || *op == '#')
		return;
	while (ins[i].opcode && op)
	{
		if (!strcmp(op, ins[i].opcode))
		{
			ins[i].f(&(args->stack), args->counter);
			return;
		}
		i++;
	}
	fprintf(stderr, "L%ld: unknown instruction %s\n", args->counter, op);
	exit(EXIT_FAILURE);
}
