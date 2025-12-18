#include <unistd.h>
#include <string.h>

int	main(int ac, char **av)
{
	char	buffer[100000];
	int		i = 0;
	int		leido = 1;
	int		j;
	int		len = 0;

	if (ac != 2)  // Parameter Check
		return (1);
	len = strlen(av[1]);
	while (leido > 0)  // read char by char into buffer
		leido = read(0, &buffer[i++], 1);
	buffer[--i] = 0;  // \0
	i = 0;
	while (buffer[i])
	{
		j = 0;  // compare each char
		while (buffer[i + j] && av[1][j] && buffer[i + j] == av[1][j])
			j++;
		if (j == len)  // if they are the same
		{	
			while (j--)
			{	
				write(1, "*", 1);
				i++;
			}
		}
		else  // if they are different
			write(1, &buffer[i++], 1);
	}
	return (0);
}
