#include <unistd.h>

void	inter(char *s1, char *s2)
{
	int	i;
	int	j;
	char	seen[256] = {0};

	i = 0;
	while (s1[i])
	{
		if (!seen[(unsigned char)s1[i]]) //if it's not seen before
		{
			j = 0; //always remember to set it 0
			while (s2[j]) //不用break时, !seen[(unsigned char)s1[i]])内层检查
			{
				if (s1[i] == s2[j])
				{
					write(1, &s1[i], 1);
					seen[(unsigned char)s1[i]] = 1; //set the seen to 1
					break; //no more loop
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	if (argc == 3)
		inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
