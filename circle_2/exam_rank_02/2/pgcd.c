/*编写一个程序，输入两个字符串，分别代表两个严格正整数，且这两个整数可以放在一个 int 类型中。
显示它们的最大公约数，后面加换行符（它总是一个严格意义上的正整数）。
如果参数数量不是 2，则显示一个换行符。*/

#include <stdio.h>
#include <stdlib.h>

void	pgcd(char *s1, char *s2)
{
	int n1 = atoi(s1);
	int n2 = atoi(s2);
	int temp;

	while (n2 != 0)
	{
		temp = n1 % n2; // 欧几里得算法
		n1 = n2;
		n2 = temp;
	}
	printf("%d", n1);  // 输出 GCD
}

int	main(int argc, char **argv)
{
	if (argc == 3)
		pgcd(argv[1], argv[2]);
	printf("\n");
	return 0;
}

/*找最大公约数的这道题核心是欧几里得算法：gcd(a, b) = gcd(b, a % b)，直到 b = 0。
首先验证参数数量，正确则进入核心函数，然后无论如何都要换行；
先用atoi将字符串转整数；
利用辗转相除法不停用 n1 % n2, n2 % temp 等，直到 n2 为 0，这时 n1 就是最大公约数。*/