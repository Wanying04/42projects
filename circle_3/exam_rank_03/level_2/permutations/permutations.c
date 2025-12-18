#include <stdlib.h>
#include <unistd.h>

void	sort_chars(char *str, int n)  // bubble sort
{
	int i = 0;
	while (i < n - 1)
	{
		int j = 0;
		while (j < n - i - 1)
		{
			if (str[j] > str[j + 1])
			{
				char tmp = str[j];
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
	if (i == n)  // print result
	{
		write(1, result, n);
		write(1, "\n", 1);
		return;
	}
	int j = 0;
	while (j < n)  // select char for current i
	{
		if (!used[j])  // if it has not been used
		{
			used[j] = 1;  // mark as used
			result[i] = str[j];  // use this char
			backtrack(str, result, used, i + 1, n);  // recursively process the next position
			used[j] = 0;  // reset this char as unused
		}
		j++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int n = 0;  // count str len
		while (av[1][n])
			n++;
		char *str = malloc(sizeof(char) * (n + 1));  // allocate memory
		if (!str)
			return 1;
		int	i = 0;  // copy original str
		while (i < n)
		{
			str[i] = av[1][i];
			i++;
		}
		str[n] = '\0';
		sort_chars(str, n);  // sort the str
		char *result = malloc(sizeof(char) * (n + 1));  // memory allocation for auxiliary arrays
		int *used = calloc(n, sizeof(int));
		if (!result || !used)
		{
			free(str);
			return 1;
		}
		result[n] = '\0';
		backtrack(str, result, used, 0, n);  // generate permutations
		free(str);  // Release memory
		free(result);
		free(used);
	}
	return 0;
}
