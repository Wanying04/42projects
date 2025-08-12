#include <unistd.h> //DO NOT forget head file

void	alpha_mirror(char *str)
{
	char	c;

	while (*str)
	{
		c = *str;
		if (c >= 'a' && c <= 'z')
			c = 'z' - (c - 'a'); //正确的镜像计算
		else if (c >= 'A' && c <= 'Z')
			c = 'Z' - (c - 'A'); //正确的镜像计算
		write (1, &c, 1);
		str++; //DO NOT forget the loop
	}
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
		alpha_mirror(argv[1]);
	write(1, "\n", 1);
	return (0);
}
