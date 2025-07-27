/*编写一个函数，能够原地(in-place)反转一个字符串，并且返回该字符串参数。*/

char *ft_strrev(char *str)
{
    int i = 0;
    int len = 0;
    char tmp;

    while (str[len])  // 计算字符串长度
        len++;
    while (i < len)   // 修正：i < len（而不是 len - 1）
    {
        len--;        // 先减 1，因为 str[len] 初始指向 '\0' 前一个字符
        tmp = str[i];
        str[i] = str[len];
        str[len] = tmp;
        i++;
    }
    return (str);
}