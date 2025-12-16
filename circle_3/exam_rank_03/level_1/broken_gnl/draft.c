#include "get_next_line.h"

// #  define BUFFER_SIZE 10

// #include <unistd.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return NULL;
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return (char *)s;
	return NULL;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d = dest;
	const unsigned char	*s = src;

	while(n--)
		*d++ = *s++;
	return dest;
}

size_t	ft_strlen(const char *s)
{
	if (!s)
		return (0);
	size_t	res = 0;
	while (*s)
	{
		s++;
		res++;
	}
	return res;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
  size_t size1 = ft_strlen(*s1);
  char *tmp = malloc(size2 + size1 + 1);
  if (!tmp)
    return 0;
  ft_memcpy(tmp, *s1, size1);
  ft_memcpy(tmp + size1, s2, size2);
  tmp[size1 + size2] = '\0';
  free(*s1);
  *s1 = tmp;
  return 1; 
}

int str_append_str(char **s1, char *s2)
{
  return str_append_mem(s1, s2, ft_strlen(s2));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d = dest;
	const unsigned char	*s = src;

	if (d == s || n == 0)
		return dest;
	if (d > s && d < s + n)
	{
		d += n;
		s += n;
		while (n--)
		*--d = *--s;
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return dest;
}

char *get_next_line(int fd)
{
  static char b[BUFFER_SIZE + 1] = ""; // 静态缓冲区：存储从文件读取的数据，在多次调用间保持状态
  static int pos = 0; // 指向缓冲区中未处理数据的开始位置
  char *ret = NULL; // 最终要返回的一行字符串
  char *tmp = ft_strchr(b + pos, '\n'); // 指向当前缓冲区中的 '\n' | 从 b + pos 开始

  while(!tmp) // 没有找到换行符时进入循环
  {
	if (b[pos] != '\0') // 上一轮读剩的数据中没有换行符，但还有剩余字符没处理完
	{
		int len = ft_strlen(b + pos); // 计算当前缓冲区中剩余数据的长度
		if (len > 0) // 如果有数据
		{
			if (!str_append_str(&ret, b + pos)) // 将剩余数据追加到ret
			{
				free(ret); // 追加失败，释放已分配的内存
				return NULL;
			}
		}
	}
	int read_ret = read(fd, b, BUFFER_SIZE); // 读取新数据到缓冲区
	if (read_ret == -1)  // 处理读取错误
	{
		free(ret); // 读取错误，释放已分配的内存
		return NULL;
	}
	if (read_ret == 0) // 处理文件结束（EOF）
	{
		if (ret != NULL && *ret != '\0') // 检查是否有已读取但未返回的数据
			return ret; // 返回最后一行（可能没有换行符）
		else
		{
			free(ret); // 没有数据了，返回NULL
			return NULL;
		}
	}
	pos = 0; // 成功读取到新数据 | 重置位置：新数据从缓冲区开头开始
	b[read_ret] = '\0'; // 确保缓冲区以NULL结尾
	tmp = ft_strchr(b, '\n'); // 关键：在新读取的数据中[重新]查找换行符
  } // 循环会继续的条件： tmp == NULL（新读取的数据中还是没有换行符）

  int line_len = tmp - (b + pos) + 1; // b + pos: 缓冲区中当前要处理的起始位置 | 找到换行符，计算这一行的长度（包含换行符）
  if (!str_append_mem(&ret, b + pos, line_len)) // 将这一行（包含换行符）追加到结果字符串
  {
    free(ret);
    return NULL;
  }
  pos += line_len; // 更新位置：跳过已返回的这一行 | 剩余数据保留在缓冲区中，供下次调用使用
  return ret;
}

int	main(void)
{
	int	i;
	int	fd;
	char	*line;

	i = 0;
	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("line[%i]: %s\n", i, line);
		line = get_next_line(fd);
		i++;
	}
	return (0);
}

// 开始循环（没有找到换行符）
//     ↓
// 是否有未处理的字符？ → 是 → 保存到 ret
//     ↓ 否
// 读取新数据
//     ↓
// 读取错误？ → 是 → 释放内存，返回NULL
//     ↓ 否
// 文件结束？ → 是 → 检查ret中是否有数据 → 返回ret或NULL
//     ↓ 否
// 重置pos，给缓冲区加\0结尾
//     ↓
// 查找换行符
//     ↓
// 找到？ → 否 → 继续循环
//     ↓ 是
// 退出循环，处理换行符