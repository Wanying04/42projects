#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024  // 缓冲区大小

// memmem函数声明（部分系统可能需要）
void *memmem(const void *haystack, size_t haystacklen,
             const void *needle, size_t needlelen);

/* 
 * 处理单个缓冲区的函数
 * buffer: 当前读取的数据缓冲区
 * bytes_read: 缓冲区中实际读取的字节数
 * target: 要查找的目标字符串
 * target_len: 目标字符串长度
 * stars: 由*组成的替换字符串
 * 返回值: 成功返回0，失败返回-1
 */
int process_buffer(char *buffer, ssize_t bytes_read, char *target, ssize_t target_len, char *stars)
{
    char *pos = buffer;          // 当前处理位置指针
    ssize_t remaining = bytes_read; // 剩余待处理的字节数
    ssize_t written;             // write函数返回值

    // 当剩余字节数足够包含目标字符串时，循环查找
    while (remaining >= target_len)
    {
        // 在当前缓冲区中查找目标字符串
        char *found = memmem(pos, remaining, target, target_len);
        if (!found)  // 没找到，跳出循环
            break;
        
        // 计算目标字符串之前的字节数
        size_t before_len = found - pos;
        if (before_len > 0)  // 如果有目标字符串之前的内容
        {
            // 写入目标字符串之前的内容
            written = write(1, pos, before_len);
            if (written < 0 || (size_t)written != before_len)
                return (-1);  // 写入失败
        }
        
        // 写入*替换字符串
        written = write(1, stars, target_len);
        if (written < 0 || (size_t)written != target_len)
            return (-1);  // 写入失败
        
        // 移动指针到目标字符串之后
        pos = found + target_len;
        // 更新剩余字节数
        remaining = bytes_read - (pos - buffer);
    }
    
    // 处理缓冲区剩余的内容（不够匹配目标字符串的部分）
    if (remaining > 0)
    {
        written = write(1, pos, remaining);
        if (written < 0 || (size_t)written != remaining)
            return (-1);  // 写入失败
    }
    return (0);  // 成功
}

/*
 * 创建由*组成的字符串
 * len: 字符串长度
 * 返回值: 成功返回字符串指针，失败返回NULL
 */
char *create_stars_string(size_t len)
{
    char *stars;  // *字符串指针
    size_t i;     // 循环变量

    // 分配内存，多1个字节用于存放'\0'
    stars = malloc(len + 1);
    if (!stars)  // 内存分配失败
        return (NULL);
    
    i = 0;
    // 填充*字符
    while (i < len)
    {
        stars[i] = '*';
        i++;
    }
    stars[len] = '\0';  // 字符串结束符
    return (stars);
}

/*
 * 主要过滤函数
 * target: 要查找的目标字符串
 * target_len: 目标字符串长度
 * 返回值: 成功返回0，错误返回1
 */
int filter_input(char *target, ssize_t target_len)
{
    char *stars;              // *替换字符串
    char buffer[BUFFER_SIZE]; // 读取缓冲区
    ssize_t bytes_read;       // 实际读取的字节数
    int result;               // 函数返回值

    // 创建*替换字符串
    stars = create_stars_string(target_len);
    if (!stars)  // 创建失败
    {
        fprintf(stderr, "Error: ");
        perror("malloc");
        return (1);
    }

    result = 0;  // 初始化为成功
    // 循环读取标准输入
    while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0)
    {
        // 处理当前缓冲区
        if (process_buffer(buffer, bytes_read, target, target_len, stars) < 0)
        {
            fprintf(stderr, "Error: ");
            perror("write");
            result = 1;  // 设置错误标志
            break;       // 跳出循环
        }
    }
    
    // 检查read是否出错（不是正常结束）
    if (bytes_read < 0)
    {
        fprintf(stderr, "Error: ");
        perror("read");
        result = 1;  // 设置错误标志
    }
    free(stars);  // 释放*字符串内存
    return (result);
}

/*
 * 处理空目标字符串的情况
 * 当目标字符串为空时，直接复制输入到输出
 * 返回值: 成功返回0，错误返回1
 */
int handle_empty_target(void)
{
    char buffer[BUFFER_SIZE]; // 读取缓冲区
    ssize_t bytes_read;       // 实际读取的字节数
    ssize_t written;          // write函数返回值

    // 循环读取标准输入
    while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0)
    {
        // 直接写入读取的内容
        written = write(1, buffer, bytes_read);
        if (written < 0 || written != bytes_read)
        {
            fprintf(stderr, "Error: ");
            perror("write");
            return (1);  // 写入失败
        }
    }
    
    // 检查read是否出错
    if (bytes_read < 0)
    {
        fprintf(stderr, "Error: ");
        perror("read");
        return (1);  // 读取失败
    }
    return (0);  // 成功
}

/*
 * 主函数
 * argc: 参数个数
 * argv: 参数数组
 * 返回值: 成功返回0，错误返回1
 */
int main(int argc, char **argv)
{
    char *target;      // 目标字符串
    ssize_t target_len; // 目标字符串长度

    // 检查参数个数
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return (1);
    }

    target = argv[1];            // 获取目标字符串
    target_len = strlen(target); // 计算长度

    // 处理空字符串特殊情况
    if (target_len == 0)
        return (handle_empty_target());
    
    // 执行主要过滤逻辑
    return (filter_input(target, target_len));
}

// 开始
//   ↓
// 检查参数个数是否正确
//   ↓
// 获取目标字符串并计算长度
//   ↓
// 目标字符串为空？ → 是 → 直接复制输入到输出
//         ↓否
// 创建*替换字符串
//   ↓
// 循环：从stdin读取数据到缓冲区
//   ↓
// 在缓冲区中查找目标字符串
//   ↓
// 找到目标字符串？ → 是 → 写入*替换
//         ↓否
// 写入原字符
//   ↓
// 继续读取直到结束
//   ↓
// 释放内存并返回