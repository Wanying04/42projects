/*编写一个程序，显示一个数字的乘法表。
参数始终为严格正数，且能装入 int 类型，
并且该数字乘以 9 后的值也能装入 int 类型。
如果没有参数，程序将显示 \n。*/

#include <unistd.h>

void	ft_itoa(int n)
{
	char c;
	if (n >= 10)
		ft_itoa(n / 10);  // 递归处理高位
	c = (n % 10) + '0';   // 转换为字符
	write(1, &c, 1);      // 输出当前位
}

void	tab_mult(int num)
{
	int i = 1;
	while (i <= 9)
	{
		ft_itoa(i);          // 乘数转字符串
		write(1, " x ", 3);  // 乘号
		ft_itoa(num);        // 被乘数转字符串
		write(1, " = ", 3);  // 等号
		ft_itoa(i * num);    // 结果转字符串
		write(1, "\n", 1);   // 换行
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int num = 0;
	char *ptr;

	if (argc == 2)
	{
		ptr = argv[1];
		while (*ptr)
		{
			num = num * 10 + (*ptr - '0');  // 字符串转整数
			ptr++;
		}
		tab_mult(num);
	}
	else
		write(1, "\n", 1);
	return 0;
}

/*乘法表这道题首先要检查输入参数数量，如果不是一个参数，则输出换行；
若参数数量正确，须先用一个指针指代av[1]，然后遍历指针，将字符串转整数；
字符串转整数的核心公式：n = n * 10 + (*ptr - '0')；
然后应用核心函数，利用itoa和write输出乘法表；
itoa采用递归除以10，然后取余，用write从高到低输出，核心公式：c = (n % 10) + '0'。*/