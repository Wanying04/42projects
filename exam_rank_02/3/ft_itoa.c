#include <stdlib.h>

static int	ft_count_len(int nbr)
{
	int	len = 0;

	if (nbr <= 0)
		len = 1;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return len;
}

char	*ft_itoa(int nbr)
{
	int		len;
	char	*str;
	long	num;

	len = ft_count_len(nbr);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	num = nbr;
	if (num == 0)
		return (str[0] = '0', str);
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num != 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}