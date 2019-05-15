#include "monty.h"

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: array of argc
 * Return: 0 or 1
 */
int main(int argc, char **argv)
{
	extern args_t args;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	args.argv = argv;
	args.counter = 0;
	args.line = NULL;
	args.stack = NULL;
	args.file = NULL;
	monty();
	free_dlistint(args.stack);
	return (EXIT_SUCCESS);
}
