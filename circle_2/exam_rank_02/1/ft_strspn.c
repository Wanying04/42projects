/*strspn 是 C 标准库中的一个字符串函数，它的功能是计算字符串 s 起始部分连续包含在字符串 accept 中的字符的最大长度。*/

#include <stddef.h> // 为了 size_t

size_t ft_strspn(const char *s, const char *accept)
{
    size_t i = 0;
    
    while (s[i])
    {
        size_t j = 0;
        while (accept[j])
        {
            if (s[i] == accept[j])
                break;
            j++;
        }
        if (!accept[j]) // 如果遍历完 accept 都没找到匹配
            return i;
        i++;
    }
    return i;
}