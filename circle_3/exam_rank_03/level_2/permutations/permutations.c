#include <stdlib.h>

void	swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_chars(char *str, int n)  // bubble sort
{
	int		i = 0;

	while (i < n - 1)
	{
		int	j = 0;
		while (j < n - 1)
		{
			if (str[j] > str[j + 1])
			{
				swap(&str[j], &str[j + 1]);
			}
			j++;
		}
		i++;
	}
}

void	backtrack(char *str, int i, int n)
{
	if (i == n)  // 所有位置都确定了
	{
		puts(str);
		return;
	}
	int j = i;  // 让每个字母都有机会出现在位置i
	while (j < n)
	{
		swap(&str[i], &str[j]);  // 1. 交换：让str[j]出现在位置i
		backtrack(str, i + 1, n);  // 2. 递归：确定下一个位置
		swap(&str[i], &str[j]);  // 3. 回溯：恢复原状，让其他字母也有机会
		j++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int	n = 0;  // count str len
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
		str[i] = '\0';
		sort_chars(str, n);  // sort the str
		backtrack(str, 0, n);
		free(str);
	}
	return 0;
}
