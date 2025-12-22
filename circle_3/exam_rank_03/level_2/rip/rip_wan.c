#include <stdio.h>

int	invalid(char *s)
{
	int	i = 0;
	int	open = 0;
	int	close = 0;

	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return (open + close);
}

void	backtrack(char *s, int remove, int deleted, int n, int *used)
{
	if (remove == deleted)
	{
		if (!invalid(s))
			puts(s);
		return;
	}
	int	pos = 0;
	while (s[pos] && !used[pos])
	{
		used[pos] = 1;
		if (s[pos] == '(' || s[pos] == ')')
		{
			char	c = s[pos];
			s[pos] = ' ';
			backtrack(s, remove, deleted + 1, n, used);
			s[pos] = c;
		}
		used[pos] = 0;
		pos++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	int	n = 0;
	while (av[1][n])
		n++;
	int	used[100] = {0};
	int	remove = invalid(av[1]);
	backtrack(av[1], remove, 0, n, used);
	return 0;
}
