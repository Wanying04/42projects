
int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

/* 检查字符是否在给定进制下合法 */
int	ft_isvalid(int c, int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '0' + base - 1);
	return ((c >= '0' && c <= '9') ||       // 数字
			(c >= 'a' && c <= 'a' + base - 11) ||  // 小写字母
			(c >= 'A' && c <= 'A' + base - 11));   // 大写字母
}

/* 将字符转换为对应的数值 */
int	ft_char_to_value(int c)
{
	if (c >= 'A' && c <= 'F')
		c += 32;
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else
		return (-1);
}

/* 主函数：字符串转十进制 */
int	ft_atoi_base(const char *str, int base)
{
	int	result = 0;
	int	sign = 1;
	int	i = 0;

	if (base < 2 || base > 16)  // 进制合法性检查
		return (0);

	while (ft_isspace(str[i]))  // 跳过空白符
		i++;

	if (str[i] == '-')  // 处理符号
	{
		sign = -1;
        i++;
	}

	while (str[i] && ft_isvalid(str[i], base))  // 转换数字
	{
		result = result * base + ft_char_to_value(str[i]);
		i++;
	}
	return (result * sign);
}