/*在一个字符串 s1 中查找任何属于字符串 s2 的字符，并返回第一次出现的位置。*/

char *ft_strpbrk(const char *s1, const char *s2)
{
    if (!s1 || !s2)  // 可选：检查 NULL 指针
        return 0;

    const char *p1 = s1;  // 用于遍历 s1
    const char *p2;       // 用于遍历 s2

    while (*p1 != '\0')   // 遍历 s1
    {
        p2 = s2;          // 每次比较前重置 p2
        while (*p2 != '\0')  // 遍历 s2
        {
            if (*p1 == *p2)
                return (char *)p1;  // 找到匹配，返回当前位置
            p2++;
        }
        p1++;
    }
    return 0;  // 未找到匹配
}