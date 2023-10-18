#include <stdio.h>
#include <unistd.h>

/**
 * main - Program entry point.
 *
 * Description: A program that prints all the arguments, without using
 * ac
 * @ac: argument count
 * @av: argument pointer
 *
 * Return: 0 (Successs);
 */
int main(int ac, char **av)
{
	char i;

	for (i = 0; av[i] != NULL; i++)

		printf("%s\n", av[i]);
	return (0);
}
