#include <stdio.h>

// min number of () that need to be removed
int	invalid(char *s)
{
	int i = 0;
	int open = 0;  // unmatched left (
	int close = 0;  // unmatched right )

	while (s[i])
	{
		if (s[i] == '(')  // find left (
			open++;
		else if (s[i] == ')')  // find right )
		{
			if (open > 0)  // match ( and )
				open--;
			else
				close++;  // find unmatched right )
		}
		i++;
	}
	return (open + close);  // all () that need to be removed
}

void	result(char *s, int remove, int delete, int pos)
{
	//If enough () have been removed and the current str is balanced
	if (remove == delete && !invalid(s))
	{
		puts(s);
		return ;
	}
	while (s[pos])  // remove () from position pos
	{
		if (s[pos] == '(' || s[pos] == ')')
		{
			char c = s[pos];  // save current char
			s[pos] = ' ';  // replace with space
			result(s, remove, delete + 1, pos + 1);  // recursive attempt
			s[pos] = c;  // restore original char
		}
		pos++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int remove = invalid(av[1]);  // min number of () that need to be removed
	result(av[1], remove, 0, 0);  // recursive search
	return (0);
}
