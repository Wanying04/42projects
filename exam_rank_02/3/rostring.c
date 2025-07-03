#include <unistd.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	rostring(char *str)
{
	int i = 0, j = 0, f = 0;

	while (is_space(str[i]))
		i++;
	if (!str[i])
	{
		write(1, "\n", 1);
		return;
	}

	j = i; // Start of first word

	// Move i to end of first word
	while (str[i] && !is_space(str[i]))
		i++;

	// Print the rest of the words
	while (str[i])
	{
		while (is_space(str[i]))
			i++;
		if (str[i])
		{
			if (f++)
				write(1, " ", 1);
			while (str[i] && !is_space(str[i]))
				write(1, &str[i++], 1);
		}
	}

	// Print the first word
	if (f) // Only if there were other words
		write(1, " ", 1);
	while (str[j] && !is_space(str[j]))
		write(1, &str[j++], 1);

	write(1, "\n", 1);
}

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		write(1, "\n", 1);
		return 0;
	}
	rostring(av[1]);
	return 0;
}