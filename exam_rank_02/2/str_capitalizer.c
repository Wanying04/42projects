/*编写一个程序，接受一个或多个字符串作为参数，并为每个参数将每个单词的首字母大写（当然，如果是字母的话），
其余字母小写，并将结果显示在标准输出上，后跟一个 \n。
“单词”定义为字符串的一部分，由空格/制表符或字符串的首尾分隔。如果单词只有一个字母，则必须大写。
如果没有参数，程序必须显示 \n。*/

#include <unistd.h>

void	str_capitalizer(char *str)
{
	int is_word_start = 1;  // 标记是否在新单词的开头

	while (*str)
	{
		if (*str == ' ' || *str == '\t')
		{
			is_word_start = 1;  // 遇到空格/制表符，标记下一个字符是新单词
			write(1, str, 1);
		}
		else
		{
			if (is_word_start)
			{
				if (*str >= 'a' && *str <= 'z')
					*str -= 32;                 // 只有首字符是小写字母时才大写
				is_word_start = 0;
			}
			else
			{
				if (*str >= 'A' && *str <= 'Z')
					*str += 32;                 // 其余字母如果是大写的话转小写
			}
			write(1, str, 1);
		}
		str++;
	}
}

int	main(int argc, char *argv[])
{
	int	i = 1;

	if (argc >= 2)
	{
		while (i < argc)
		{
			str_capitalizer(argv[i]);
			i++;
		}
	}
	write(1, "\n", 1);
	return 0;
}

/*字符串单词首字母大写这道题是这样的：首先，可以接受多个字符串，所以需要在 main 中运用一个循环；
在核心函数中遍历字符串，区分两种情况：如果是空格，则标记 is_word_start = 1，下一个是新单词，并输出空格；
如果不是空格，当看到了标记，只有首字符是小写字母时才大写，并将 is_word_start 重设为 0；
其余字母如果是大写的话转小写；
经历了上述一切操作后输出字符。*/