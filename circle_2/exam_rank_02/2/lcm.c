/*编写一个函数，接受两个无符号整数作为参数，并返回计算出的这两个参数的最小公倍数 (LCM)。
两个非零整数的最小公倍数 (LCM) 是能被这两个整数整除的最小正整数。
LCM(x, y) = | x * y | / HCF(x, y)。
如果至少有一个整数为空，则 LCM 等于 0。*/

unsigned int	gcd(unsigned int a, unsigned int b)
{
	unsigned int temp;

	while (b != 0)
	{
		temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

unsigned int	lcm(unsigned int a, unsigned int b)
{
	// 处理至少一个参数为0的情况
	if (a == 0 || b == 0)
		return 0;
	
	// 使用公式LCM = (a / GCD) * b 避免a*b溢出
	return (a / gcd(a, b)) * b;
}

/*实现一个函数 lcm，计算两个无符号整数的最小公倍数（LCM），需注意：

如果任一参数为 0，直接返回 0（因为 LCM 无定义）。

计算方式：

方法二：利用最大公约数（HCF/GCD）公式：

由于输入是无符号整数，绝对值可忽略。

关键点
HCF（最大公约数）计算：需先实现 HCF（如欧几里得算法）。
防溢出处理：a * b 可能导致溢出，需优化计算顺序。*/