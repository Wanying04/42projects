int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]); //标准 strcmp 按 unsigned char 比较
		i++; //指针的差值（&s1[i] - &s2[i]）,字符值的差值（s1[i] - s2[i]）
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
