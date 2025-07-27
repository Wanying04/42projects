/*函数必须使用 malloc() 分配一个整数数组，
并用从 start 开始到 end 结束的连续值填充该数组（包括 start 和 end！），
然后返回指向该数组第一个值的指针。*/

#include <stdlib.h>

int	*ft_range(int start, int end)
{
	int *array;
	int size;
	int i = 0;

	// 计算数组长度
	if (start <= end)
		size = end - start + 1;
	else
		size = start - end + 1;

	// 分配内存
	array = (int *)malloc(size * sizeof(int));
	if (array == NULL)
		return NULL;

	// 填充数组
	if (start <= end)
	{
		while (start <= end)
		{
			array[i] = start;
			start++;
			i++;
		}
	}
	else
	{
		while (start >= end)
		{
			array[i] = start;
			start--;
			i++;
		}
	}
	return array;
}

/*顺序填充数组。先计算数组长度，然后分配内存，如果分配失败返回NULL；
接着填充数组，分两种情况，看start和end谁比较大；最后返回array。*/