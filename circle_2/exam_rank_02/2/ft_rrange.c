/*该函数必须使用 malloc() 分配一个整数数组，并用从 end 开始、到 start 结束的连续值填充该数组（包含 start 和 end！），然后
返回指向数组首值的指针。*/

#include <stdlib.h>

int	*ft_rrange(int start, int end)
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

	// 填充数组：从 end 到 start
	if (start <= end)
	{
		while (end >= start)
		{
			array[i] = end;
			end--;
			i++;
		}
	}
	else
	{
		while (end <= start)
		{
			array[i] = end;
			end++;
			i++;
		}
	}
	return array;
}

/*逆向填充数组这道题解题逻辑是这样的：首先计算出数组长度，注意start可能比end大，也可能比它小；
然后为新的数组分配内存，分配失败返回NULL；
开始填充数组，区分两种情况，start比end大，则从小到大填充；start比end小，则从大到小填充；
最后返回指向数组首值的指针，也就是 array 就行了。*/