/*编写一个程序，显示传递给它的参数数量，后跟一个换行符。
如果没有参数，则显示 0，后跟一个换行符。*/

#include <unistd.h>

void ft_putnbr(int n)
{
    char c;
    if (n >= 10)
	{
        ft_putnbr(n / 10);
    }
    c = (n % 10) + '0';
    write(1, &c, 1);
}

int	main(int argc, char *argv[])
{
	(void)argv;                   // 显式忽略未使用的参数
	print_number(argc - 1);
	write(1, "\n", 1);
	return 0;
}

/*打印参数数量这道题主要处理的是打印这个环节。首先 argv 这个参数要忽略；
argc - 1 已经昭示了参数数量，要利用一个函数将 int 打印出来；
在辅助函数中，利用递归不断除以 10，然后利用取余从高到低打印字符。*/