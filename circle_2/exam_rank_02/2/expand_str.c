/*编写一个程序，输入一个字符串，并显示该字符串，每个单词之间恰好有三个空格，开头和结尾都没有空格或制表符，最后显示一个换行符。
单词是由空格/制表符或字符串的开头/结尾分隔的一段字符串。
如果参数个数不为 1，或者没有单词，则直接显示一个换行符。*/

#include <unistd.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	expand_str(char *str)
{
	int in_word = 0;
	int need_space = 0;

	// 跳过前导空格
	while (is_space(*str))
		str++;

	// 处理字符串主体
	while (*str)
	{
		if (!is_space(*str))
		{
			// 非空格字符：输出单词分隔符（若非首个单词）和当前字符
			if (need_space)
				write(1, "   ", 3);
			write(1, str, 1);
			in_word = 1;
			need_space = 0;
		}
		else if (in_word)
		{
			// 空格字符且之前在单词内：标记需要分隔符
			in_word = 0;
			need_space = 1;
		}
		str++;
	}
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
		expand_str(argv[1]);
	write(1, "\n", 1);
	return 0;
}

/*固定三个空格这道题解题思路如下：首先利用辅助函数is_space循环跳过前导空格，因为字符串开头不能有空格；
然后开始处理字符串主体。区分两种情况：非空格字符以及空格字符且之前在单词内，in_word 和 need_space 参数初始都是 0；
当当前字符是非空格字符时，若 need_space 为真，输出三个空格，然后输出该字符，并将 in_word 设为真， need_space 重置为 0；
当当前字符是空格字符且之前在单词内，即 in_word 为真， in_word 重置为 0，need_space 设为真；
循环直到字符串末尾。*/