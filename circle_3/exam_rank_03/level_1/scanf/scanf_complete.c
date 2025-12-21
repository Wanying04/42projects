/*
 * 题目：实现简化版 scanf
 * 
 * 描述：
 * 实现一个只支持 %s、%d 和 %c 的简化版 scanf 函数。
 * 
 * 关键概念：
 * 1. 可变参数：va_list, va_start, va_arg, va_end
 * 2. 格式字符串解析：逐个字符分析格式字符串
 * 3. 文件读取：使用 fgetc() 和 ungetc() 控制输入流
 * 4. 类型转换：将字符串转换为数字，处理空白字符
 * 
 * 支持的格式说明符：
 * - %s: 读取一个字符串（遇到空白字符停止）
 * - %d: 读取一个有符号十进制整数（可选的 +/- 符号）
 * - %c: 读取一个字符
 */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

/* 跳过输入流中的空白字符 */
int match_space(FILE *f)
{
    /*
     * 处理空白字符：
     * - 读取并丢弃连续的空白字符
     * - 将第一个非空白字符放回输入流
     * - 返回 -1 表示错误
     */
    int ch = fgetc(f);
    if (ch == EOF && ferror(f))
        return -1;
    
    while (ch != EOF)
    {
        if (!isspace(ch))
        {
            ungetc(ch, f); // 将非空白字符放回流中
            break;
        }
        ch = fgetc(f);
    }
    
    if (ferror(f))
        return -1;
    return 1;
}

/* 检查输入流中的下一个字符是否与指定字符匹配 */
int match_char(FILE *f, char c)
{
    /*
     * 匹配字面量字符：
     * - 从输入流读取一个字符
     * - 检查是否与预期字符匹配
     * - 如果不匹配，将字符放回输入流
     */
    int ch = fgetc(f);
    if (ch == c)
        return 1;
    if (ch != EOF)
        ungetc(ch, f);
    return -1;
}

/* 读取单个字符（%c 格式） */
int scan_char(FILE *f, va_list ap)
{
    /*
     * %c 转换说明符处理：
     * - 精确读取一个字符
     * - 不跳过空白字符（与标准 scanf 一致）
     * - 将字符存储到提供的指针中
     */
    int ch = fgetc(f);
    char *cp = va_arg(ap, char *);

    if (ch == EOF)
        return -1;
    
    *cp = (char)ch;
    return 1;
}

/* 读取整数（%d 格式） */
int scan_int(FILE *f, va_list ap)
{
    /*
     * %d 转换说明符处理：
     * - 跳过前导空白字符
     * - 处理可选的符号（+/-）
     * - 读取数字字符并构建整数
     * - 将最后一个非数字字符放回输入流
     */
    int sign = 1;   // 符号，默认为正
    int value = 0;  // 累加的值
    int ch = fgetc(f);
    int *ip = va_arg(ap, int *); // 获取存储结果的指针
    int count = 0;  // 成功读取的数字字符数

    if (ch == EOF)
        return -1;
    
    // 跳过空白字符
    while (isspace(ch))
        ch = fgetc(f);
    
    // 处理符号
    if (ch == '-')
    {
        sign = -1;
        ch = fgetc(f);
    }
    else if (ch == '+')
    {
        ch = fgetc(f);
    }
    
    // 检查第一个字符是否为数字
    if (!isdigit(ch))
    {
        ungetc(ch, f);
        return -1;
    }
    
    // 读取数字字符并计算值
    while (isdigit(ch))
    {
        value = value * 10 + (ch - '0'); // 将字符转换为数字并累加
        count++;
        ch = fgetc(f);
    }
    
    // 将最后一个非数字字符放回输入流
    if (ch != EOF)
        ungetc(ch, f);

    if (count == 0) // 没有读取到任何数字
        return -1;
    
    *ip = value * sign; // 存储结果（考虑符号）
    return 1;
}

/* 读取字符串（%s 格式） */
int scan_string(FILE *f, va_list ap)
{
    /*
     * %s 转换说明符处理：
     * - 跳过前导空白字符
     * - 读取字符直到遇到空白字符
     * - 在末尾添加字符串终止符 '\0'
     * - 将空白字符放回输入流
     */
    int ch = fgetc(f);
    char *sp = va_arg(ap, char *); // 获取存储字符串的指针
    int i = 0; // 字符串索引

    // 跳过前导空白字符
    while (ch != EOF && isspace(ch))
        ch = fgetc(f);
    
    if (ch == EOF)
        return -1;

    // 读取字符直到遇到空白字符
    do
    {
        sp[i] = ch;
        i++;
        ch = fgetc(f);
    } while (ch != EOF && !isspace(ch));
    
    sp[i] = '\0'; // 字符串终止符

    // 将空白字符放回输入流
    if (ch != EOF)
        ungetc(ch, f);
    
    if (i == 0) // 没有读取到任何字符
        return -1;
    return 1;
}

/* 根据格式字符调用相应的转换函数 */
int match_conv(FILE *f, const char **format, va_list ap)
{
    /*
     * 转换说明符分发器：
     * - 分析格式字符串中的转换字符
     * - 调用相应的处理函数
     * - 为 %d 和 %s 自动处理空白字符
     */
    switch (**format)
    {
        case 'c':
            return scan_char(f, ap); // %c：读取字符
        case 'd':
            match_space(f); // %d：先跳过空白字符
            return scan_int(f, ap);
        case 's':
            match_space(f); // %s：先跳过空白字符
            return scan_string(f, ap);
        case '\0':
            return -1; // 格式字符串意外结束
        default:
            return -1; // 不支持的转换说明符
    }
}

/* 简化版 scanf 的核心实现 */
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    /*
     * scanf 主要逻辑：
     * - 逐个字符解析格式字符串
     * - 处理字面量字符和转换说明符（%）
     * - 统计成功完成的转换次数
     * - 在第一个错误时停止
     */
    int nconv = 0; // 成功完成的转换次数

    // 检查输入流中是否有数据
    int c = fgetc(f);
    if (c == EOF)
        return EOF;
    ungetc(c, f);

    // 遍历格式字符串
    while (*format)
    {
        if (*format == '%')
        {
            // 找到转换说明符
            format++; // 跳过 '%'
            if (match_conv(f, &format, ap) != 1)
                break; // 转换失败，停止解析
            else
                nconv++; // 转换成功，计数增加
        }
        else if (isspace(*format))
        {
            // 格式字符串中的空白字符：匹配输入中的任意空白字符
            if (match_space(f) == -1)
                break;
        }
        else
        {
            // 字面量字符：必须精确匹配
            if (match_char(f, *format) != 1)
                break;
        }
        format++; // 继续处理下一个字符
    }
    
    // 检查文件错误
    if (ferror(f))
        return EOF;
    
    return nconv; // 返回成功完成的转换次数
}

/* 包装函数，提供类似标准 scanf 的接口 */
int ft_scanf(const char *format, ...)
{
    /*
     * 可变参数包装器：
     * - 初始化 va_list
     * - 使用标准输入 stdin 调用核心函数
     * - 清理 va_list
     */
    va_list ap;

    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    
    return ret;
}

/*
 * 使用示例：
 * 
 * int main(void)
 * {
 *     int x;
 *     char str[100];
 *     char c;
 * 
 *     // 读取：整数、空格、字符串、空格、字符
 *     int converted = ft_scanf("%d %s %c", &x, str, &c);
 *     
 *     printf("成功转换: %d\n", converted);
 *     printf("整数: %d, 字符串: %s, 字符: %c\n", x, str, c);
 *     
 *     return 0;
 * }
 */

/*
 * 考试重点：
 * 
 * 1. 可变参数处理：
 *    - 用 va_start(ap, last_param) 初始化
 *    - 用 va_arg(ap, type) 获取下一个参数
 *    - 用 va_end(ap) 清理
 * 
 * 2. 输入流控制：
 *    - fgetc() 读取单个字符
 *    - ungetc() 将字符放回输入流
 *    - ferror() 检查文件错误
 * 
 * 3. 空白字符处理：
 *    - %c 不跳过空白字符
 *    - %d 和 %s 跳过前导空白字符
 *    - 格式字符串中的空白字符匹配输入中的任意空白字符序列
 * 
 * 4. 返回值：
 *    - 返回成功完成的转换次数
 *    - 如果发生文件错误或遇到 EOF，返回 EOF
 *    - 在第一个失败的转换处停止
 */