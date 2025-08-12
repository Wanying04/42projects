#include <unistd.h>

void	rev_wstr(char *str)
{
	int i = 0;
	int first_word = 0;
	int end = 0;

	// Find the end of the string
	while (str[i] != '\0')
		i++;
	i--; // Point to last character

	while (i >= 0)
	{
		// Skip spaces
		while (i >= 0 && str[i] == ' ')
			i--;
		
		// Mark the end of current word
		end = i;
		
		// Find the start of current word
		while (i >= 0 && str[i] != ' ')
			i--;
		
		// Print the word if valid
		if (end > i)
		{
			if (first_word)
				write(1, " ", 1);
			write(1, &str[i + 1], end - i);
			first_word = 1;
		}
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	rev_wstr(av[1]);
	write(1, "\n", 1);
	return (0);
}