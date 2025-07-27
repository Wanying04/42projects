/*编写一个程序，接受一个正整数作为参数，并显示所有小于或等于该正整数的素数之和，后跟一个换行符。
如果参数个数不为 1，或者参数不是正数，则显示 0，后跟一个换行符。*/

#include <unistd.h>

int is_prime(int n)
{
    int i = 3;
    
    if (n <= 1)
        return 0;
    if (n == 2)
        return 1;
    if (n % 2 == 0)
        return 0;
    while (i * i <= n)
    {
        if (n % i == 0)
            return 0;
        i += 2;
    }
    return 1;
}

int ft_atoi(char *s)
{
    int n = 0;
    
    if (!*s) return -1;
    while (*s)
    {
        if (*s < '0' || *s > '9')
            return -1;
        n = n * 10 + (*s++ - '0');
    }
    return n;
}

void ft_putnbr(int n)
{
    char c;
    
    if (n >= 10)
        ft_putnbr(n / 10);
    c = n % 10 + '0';
    write(1, &c, 1);
}

int main(int ac, char **av)
{
    int n, sum = 0, i = 2;
    
    if (ac == 2 && (n = ft_atoi(av[1])) > 0)
    {
        while (i <= n)
        {
            if (is_prime(i))
                sum += i;
            i++;
        }
        ft_putnbr(sum);
    }
    write(1, "\n", 1);
    return 0;
}

/*1/参数检查

判断 argc == 2，确保有且只有一个参数。

使用自定义 ft_atoi 把参数字符串转成整数，并验证是否是正整数。

2/素数判断

编写 is_prime 函数，判断一个数是否为素数。
判断方法：从 2 开始试除到 √n，如果能整除则不是素数。

3/遍历求和

从 2 到 n 遍历每个整数。

如果是素数，就累加到 sum 中。

4/输出结果

使用递归版 ft_putnbr 输出 sum。

最后输出换行符 \n。

5/无效输入处理

若参数非法，直接输出 "0\n"。*/