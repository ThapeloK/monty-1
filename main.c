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
