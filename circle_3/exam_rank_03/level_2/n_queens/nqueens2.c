#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	validation(int *table, int val, int col)
{
	int i = 0;
	while (i < col)
	{
		if (val == table[i])
			return (0);
		if ((val - col) == table[i] - i)
			return (0);
		if ((val + col) == table[i] + i)
			return (0);
		i++;
	}
	return (1);
}

void	n_queen(int val, int col, int size, int *table)
{
	if (col == size)
	{
		int i = 0;
		while (i < size)
		{
			fprintf(stdout, "%d", table[i]);
			if (i < size - 1)
				printf(" ");
			if (i == size - 1)
				fprintf(stdout, "\n");
			i++;
		}
		return ;
	}
	while (val < size)
	{
		if (validation(table, val, col))
		{
			table[col] = val;
			n_queen(0, col + 1, size, table);
		}
		val++;
	}
	return ;
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int size = atoi(av[1]);
	int table[size];
	n_queen(0, 0, size, table);
	return (0);
}