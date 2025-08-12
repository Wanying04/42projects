/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camel_to_snake.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:29:01 by wtang             #+#    #+#             */
/*   Updated: 2025/06/19 21:01:32 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	camel_to_snake(char *str)
{
	int	i;

	i = 0;
	//while (str[i] == " " || str[i] == '\t')题目要求处理的是lowerCamelCase格式的字符串，开头不应有空格; 原代码中 str[i] == " " 应该改为 str[i] == ' '（单引号）
	//	i++;
	while(str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			write(1, "_", 1);
			str[i] = str[i] + 32;
		}
		write(1, &str[i], 1);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
		camel_to_snake(argv[1]);
	//else
	write(1, "\n", 1);//在程序结束时总是输出换行符
	return (0);
}
