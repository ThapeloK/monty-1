#include "monty.h"
/**
 * main - entry point
 * Return: 0 or 1
 */
int main(int argc, char **argv)
{
	args_t arguments;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	arguments.argc = argc;
	arguments.argv = argv;
	arguments.counter = 0;
	arguments.line = NULL;
	monty(&arguments);
	return (EXIT_SUCCESS);
}

/**
 * monty - monty
 */
void monty(args_t *args)
{
	FILE *file = fopen (args->argv[1], "r" );
	char line [128];

	if (file != NULL)
	{
		while (fgets(line, sizeof line, file) != NULL)
		{
			args->counter++;
			args->line = line;
			caller(args);
			printf("Line: %ld: %s",args->counter, line);
		}
		fclose (file);
	}
	else
	{
		perror(args->argv[1]);
	}
}

/**
 * caller - caller
 */
void caller(args_t *args)
{
	instruction_t ins[] = {
		{"push", push},
		{NULL, NULL}
	};
}

void push(stack_t **stack, unsigned int line_number)
{
	
}
