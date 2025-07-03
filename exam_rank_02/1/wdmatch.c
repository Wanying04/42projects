/*编写一个程序，检查是否可以使用第二个字符串中的字符（按顺序）拼出第一个字符串。*/

#include <unistd.h>

// 核心功能函数：检查是否可以用s2中的字符按顺序组成s1
int is_wdmatch(const char *s1, const char *s2)
{
    int i = 0;
    
    while (s1[i] && *s2)
    {
        if (s1[i] == *s2++)
            i++;
    }
    
    return (s1[i] == '\0');  // 如果s1全部匹配完成则返回1
}

// 计算字符串长度
int ft_strlen(const char *s)
{
    int len = 0;
    while (s[len])
        len++;
    return len;
}

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        const char *s1 = argv[1];
        const char *s2 = argv[2];
        
        if (is_wdmatch(s1, s2))
            write(1, s1, ft_strlen(s1));
    }
    write(1, "\n", 1);
    return 0;
}