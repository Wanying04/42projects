#include <unistd.h>

unsigned int	ft_atoi(const char *str)
{
	unsigned int	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

void	print_hex(unsigned int num)
{
	const char	*hex_digits;
	char		c;

	hex_digits = "0123456789abcdef";
	if (num >= 16)
		print_hex(num / 16);
	c = hex_digits[num % 16];
	write(1, &c, 1);
}

int	main(int argc, char *argv[])
{
	unsigned int	num;
	
	if (argc == 2)
	{
		num = ft_atoi(argv[1]);
		print_hex(num);
	}
	write(1, "\n", 1);
	return (0);
}