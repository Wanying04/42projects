#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int	main(int ac, char **av)
{
	int i = 0;
	int leido = 1;
	int len;
	int j;
	char buffer[99999];

	if (ac != 2)
		return (1);
	len = strlen(av[1]);
	while (leido > 0)
		leido = read(0, &buffer[i++], 1);
	buffer[--i] = 0;
	i = 0;
	while(buffer[i])
	{
		j = 0;
		while (buffer[i + j] && av[1][j] && buffer[i + j] == av[1][j])
			j++;
		if (j == len)
		{
			while (j--)
			{
				write(1, "*", 1);
				i++;
			}
		}
		else
			write(1, &buffer[i++], 1);
	}
	return (0);
}
