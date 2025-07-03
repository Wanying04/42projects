#include <stdio.h>
#include <stdlib.h>

void	fprime(int num)
{
	int	i = 2;
	
	if (num == 1)
	{                 // 处理输入为1的特殊情况
		printf("1");
		return;
	}
	
	while (i <= num)
	{                         // 寻找质因数
		if (num % i == 0)
		{                     // 如果i是num的因数
			printf("%d", i);  // 打印该因数
			if (num != i)     // 如果不是最后一个因数，打印 *
				printf("*");
			num = num / i;   // 更新num的值
		}
		else
		{
			i++;  // 否则检查下一个数
		}
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("\n");
		return 0;
	}
	
	int num = atoi(av[1]);  // 将字符串转换为整数
	fprime(num);         // 调用质因数分解函数
	printf("\n");           // 最后打印换行
	
	return 0;
}