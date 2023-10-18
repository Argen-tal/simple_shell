#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point of the program.
 *
 * Description: This program prints the PPID.
 *
 * Return: 0 (Success).
 */

int main(void)
{
	int running_pp;

	running_pp = getppid();
	printf("%u\n", running_pp);

	return (0);
}
