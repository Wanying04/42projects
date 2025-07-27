#include <unistd.h>

void	hidenp(char *s1, char *s2)
{
	while (*s2 && *s1)
	{
		if (*s1 == *s2)
			s1++;
		s2++;
	}
	if (*s1 == '\0')
		write(1, "1\n", 2);
	else
		write(1, "0\n", 2);
}

int	main(int argc, char *argv[])
{
	if (argc == 3)
		hidenp(argv[1], argv[2]);
	else
		write(1, "\n", 1);
	return (0);
}