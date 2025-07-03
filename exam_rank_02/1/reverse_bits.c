/*编写一个函数，能够逐位反转一个字节(8位)的数据，并返回反转后的结果。*/

unsigned char reverse_bits(unsigned char octet)
{
    unsigned int i;          // 循环计数器
    unsigned char res = 0;   // 存储反转结果
    
    i = 8;                  // 一个字节8位
    while (i--)             // 循环8次
    {
        res = (res << 1) | (octet & 1);  // 关键操作步骤
        octet = octet >> 1;              // 准备处理下一位
    }
    return (res);
}