#include <stdlib.h>
#include <unistd.h>

void	sort_chars(char *str, int n)
{
	int	i = 0;
	while (i < n - 1)
	{
		int	j = 0;
		while (j < n - i - 1)
		{
			if (str[j] > str[j + 1])
			{
				char	tmp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	backtrack(char *str, char *result, int *used, int i, int n)
{
	if (i == n)
	{
		write(1, result, n);
		write(1, "\n", 1);
		return;
	}
	int	j = 0;
	while (j < n)
	{
		if (!used[j])
		{
			used[j] = 1;
			result[i] = str[j];
			backtrack(str, result, used, i + 1, n);
			used[j] = 0;
		}
		j++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int	n = 0;
		while (av[1][n])
			n++;
		char	*str = malloc(sizeof(char) * (n + 1));
		if (!str)
			return 1;
		int	i = 0;
		while (i < n)
		{
			str[i] = av[1][i];
			i++;
		}
		str[n] = '\0';
		sort_chars(str, n);
		char	*result = malloc(sizeof(char) * (n + 1));
		int		*used = calloc(n, sizeof(int));
		if (!result || !used)
		{
			free(str);
			return 1;
		}
		result[n] = '\0';
		backtrack(str, result, used, 0, n);
		free(str);
		free(result);
		free(used);
	}
	return 0;
}
