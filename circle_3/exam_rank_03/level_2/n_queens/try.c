#include <stdlib.h>
#include <unistd.h>

int	is_valid_pos(int *table, int x, int y)
{
	int	i = 0;
	while (i < y)
	{
		if ((x == table[i] || (x - y) == (table[i] - i) || (x + y) == (table[i] + i)))
			return 0;
		i++;
	}
	return 1;
}

void	print_table(int *table, int size)
{
	int	i = 0;
	while (i < size)
	{
		char	c = table[i++] + '0';
		write(1, &c, 1);
		if (i < size)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void	n_queens(int *table, int y, int size)
{
	int	x = 0;

	if (y == size)
		return print_table(table, size);
	while(x < size)
	{
		if (is_valid_pos(table, x, y))
		{
			table[y] = x;
			n_queens(table, y + 1, size);
		}
		x++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	int	size = atoi(av[1]);
	int	table[size];
	n_queens(table, 0, size);
	return 0;
}

#include <unistd.h>
#include <stdlib.h>

int	is_valid_pos(int *table, int x, int y)
{
	int	i = 0;
	while (i < y)
	{
		if (x == table[i] || (x - y) == (table[i] - i) || (x + y) == (table[i] + i))
			return 0;
		i++;
	}
	return 1;
}

void	print_table(int *table, int size)
{
	int	i = 0;
	while (i < size)
	{
		char	c = table[i++] + '0';
		write(1, &c, 1);
		if (i < size)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void	n_queens(int *table, int y, int size)
{
	int	x = 0;

	if (y == size)
		return print_table(table, size);
	while (x < size)
	{
		if (is_valid_pos(table, x, y))
		{
			table[y] = x;
			n_queens(table, y + 1, size);
		}
		x++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	int	size = atoi(av[1]);
	int	table[size];
	n_queens(table, 0, size);
	return 0;
}
