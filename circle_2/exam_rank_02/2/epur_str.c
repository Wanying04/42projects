/*编写一个程序，输入一个字符串，并显示该字符串，每个单词之间只有一个空格，开头和结尾都没有空格或制表符，后跟一个 \n。
“单词”定义为字符串的一部分，该字符串由空格/制表符或字符串的开头/结尾分隔。
如果参数数量不为 1，或者没有要显示的单词，则程序显示 \n。*/

#include <unistd.h>

int	ft_strlen(char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return len;
}

void	epur_str(char *str)
{
	int start = 0;
	int end = ft_strlen(str) - 1;
	int space_flag = 0;
	int i;

	// 跳过前导空格
	while (str[start] == ' ' || str[start] == '\t')
		start++;

	// 跳过尾部空格
	while (end >= 0 && (str[end] == ' ' || str[end] == '\t'))
		end--;

	// 处理中间部分
	i = start;
    while (i <= end)
    {
        if (str[i] != ' ' && str[i] != '\t')
		{
            write(1, &str[i], 1);
            space_flag = 0;
        }
		else if (!space_flag)
		{
            write(1, " ", 1);
            space_flag = 1;
        }
        i++;
	}
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
		epur_str(argv[1]);
	write(1, "\n", 1);
	return 0;
}

/*只有一个空格这道题是这样做：
跳过前导空格：找到第一个非空格字符的位置 start。
跳过尾部空格：找到最后一个非空格字符的位置 end。
遍历处理中间部分：
遇到非空格字符直接输出。
遇到空格/\t 时，仅输出一个空格（跳过后续多余空格）。*/