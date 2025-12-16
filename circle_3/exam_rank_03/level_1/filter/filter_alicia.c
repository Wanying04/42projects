#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i = 0;
	
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	char	*buffer;
	char	c;
	int	r;
	int	i;
	int	len;
	
	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	len = strlen(argv[1]);
	buffer = malloc(100000);
	if (!buffer)
	{
		perror("Error");
		return (1);
	}
	i = 0;
	while (1)
	{
		r = read(0, &c, 1);
		if(r == -1)
		{
			perror("Error");
			free(buffer);
			return (1);
		}
		if(r == 0)
			break ;
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	i = 0;
	while (buffer[i])
	{
		if(ft_strncmp(&buffer[i], argv[1], len))
		{
			int	y = 0;
			while (y < len)
			{
				write(1, "*", 1);
				y++;
			}
			i = i + len;
		}
		else
			write(1, &buffer[i++], 1);
	}
	free(buffer);
	return (0);
}
