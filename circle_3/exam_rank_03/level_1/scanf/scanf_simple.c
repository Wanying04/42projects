#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

/* 简化版 scanf 函数 */
int ft_scanf(const char *format, ...)
{
	va_list args;               // 可变参数列表
	va_start(args, format);     // 初始化可变参数列表
	int count = 0;              // 成功完成的转换次数
	int c;                      // 当前读取的字符

	// 逐个字符解析格式字符串
	while (*format)
	{
		if (*format == '%')     // 遇到格式说明符
		{
			format++;           // 跳过 '%' 字符
			if (*format == 'd') // 处理整数格式 %d
			{
				int *num = va_arg(args, int *);  // 获取存储整数的指针
				int temp = 0, sign = 1;           // temp:累加值, sign:符号

				// 跳过前导空白字符
				while (isspace(c = fgetc(stdin))) // 读取字符直到非空白
					;                              // 空循环体，只读字符
				
				// 处理可选符号
				if (c == '-' || c == '+')
				{
					if (c == '-')
						sign = -1;              // 负号
					c = fgetc(stdin);           // 读取符号后的字符
				}
				
				// 检查第一个字符是否为数字
				if (!isdigit(c))
				{
					ungetc(c, stdin);          // 放回字符
					break;                     // 转换失败，退出循环
				}
				
				// 读取数字字符并构建整数
				while (isdigit(c))
				{
					temp = temp * 10 + (c - '0'); // 将字符转换为数字并累加
					c = fgetc(stdin);             // 读取下一个字符
				}
				
				*num = temp * sign;              // 存储结果（考虑符号）
				ungetc(c, stdin);                // 将最后一个非数字字符放回输入流
				count++;                         // 成功计数加一
			}
			else if (*format == 's')             // 处理字符串格式 %s
			{
				char *str = va_arg(args, char *); // 获取存储字符串的指针
				int i = 0;                        // 字符串索引
				
				// 跳过前导空白字符
				while (isspace(c = fgetc(stdin))) // 读取字符直到非空白
					;
				
				// 检查是否遇到文件结束
				if (c == EOF)
					break;                       // 输入结束，退出循环
				
				// 读取字符直到遇到空白字符或文件结束
				while (c != EOF && !isspace(c))
				{
					str[i++] = c;                // 存储字符
					c = fgetc(stdin);            // 读取下一个字符
				}
				
				str[i] = '\0';                   // 添加字符串终止符
				
				if (c != EOF)
					ungetc(c, stdin);            // 将空白字符放回输入流
				
				count++;                         // 成功计数加一
			}
			else if (*format == 'c')             // 处理字符格式 %c
			{
				char *ch = va_arg(args, char *); // 获取存储字符的指针
				
				// %c 不跳过空白字符，直接读取下一个字符
				c = fgetc(stdin);
				
				if (c == EOF)
					break;                       // 输入结束，退出循环
				
				*ch = (char)c;                   // 存储字符
				count++;                         // 成功计数加一
			}
		}
		else if (isspace(*format))               // 格式字符串中的空白字符
		{
			// 匹配输入中的任意空白字符序列
			c = fgetc(stdin);
			while (isspace(c))                   // 跳过连续的空白字符
				c = fgetc(stdin);
			ungetc(c, stdin);                    // 将非空白字符放回输入流
		}
		else                                      // 字面量字符
		{
			// 从输入中读取一个字符，必须与格式字符串中的字符完全匹配
			c = fgetc(stdin);
			if (c != *format)                    // 字符不匹配
			{
				ungetc(c, stdin);                // 放回读取的字符
				break;                           // 解析失败，退出循环
			}
		}
		format++;                                 // 移动到格式字符串的下一个字符
	}
	
	va_end(args);                                 // 清理可变参数列表
	return (count);                               // 返回成功完成的转换次数
}

/* 测试函数 */
int main()
{
	int num;                                      // 存储读取的整数
	char str[100];                                // 存储读取的字符串
	
	printf("请输入一个整数和一个单词: ");
	ft_scanf("%d %s", &num, str);                // 调用自定义的 scanf 函数
	
	printf("整数: %d\n", num);
	printf("单词: %s\n", str);
	
	return 0;
}