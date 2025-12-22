#include <stdlib.h>
#include <stdio.h>

int	*nums;			// 存储输入的数字集合
int	target;			// 目标和
int	actual[100];	// 临时存储当前构建的子集

/*
 * @param p_num   当前处理的数字在nums中的索引
 * @param size    数字集合的大小
 * @param p_act   当前actual数组中已存储的数字个数
 * @param suma    当前actual数组中数字的总和
 */
void	powerset(int p_num, int size, int p_act, int suma)
{
	// 基线条件1：找到符合条件的子集
	if (suma == target)
	{
		int	i = 0;
		// 输出找到的子集
		while (i < p_act)
		{
			if (i > 0)
				printf(" ");	// 数字间用空格分隔
			printf("%d", actual[i++]);
		}
		printf("\n");
		return;
	}
	
	// 基线条件2：已处理完所有数字
	if (p_num >= size)
		return;
	
	// ================= 递归的核心部分 =================
	// 选择1：不包含当前数字
	// 保持当前总和和子集不变，处理下一个数字
	powerset(p_num + 1, size, p_act, suma);
	
	// 选择2：包含当前数字
	// 1. 将当前数字加入子集
	actual[p_act] = nums[p_num];
	// 2. 递归处理：总和增加，子集大小增加，处理下一个数字
	powerset(p_num + 1, size, p_act + 1, suma + nums[p_num]);
	
	// 注意：这里没有显式的回溯恢复操作！
	// 因为当递归返回时，上层函数的actual[p_act]会被新的值覆盖
	// 或者p_act参数回到之前的值，实现了隐式回溯
}

int	main(int ac, char **av)
{
	int i = 0;
	
	if (ac < 3 || !(nums = malloc(sizeof(int) * (ac - 2)))) // 参数验证：至少需要目标值和一些数字 // 为数字集合分配内存（排除目标值和程序名）
		return (1);
	target = atoi(av[1]); // 解析目标值（第一个参数）
	while (i < ac - 2) // 将命令行参数转换为整数并存入nums数组 // argv[0]是程序名，argv[1]是目标值，所以从argv[2]开始
		nums[i] = atoi(av[(i++) + 2]);
	powerset(0, ac - 2, 0, 0); // 开始递归搜索 // 参数说明：// 0 - 从第一个数字开始处理// argc-2 - 数字的总个数// 0 - 初始子集为空// 0 - 初始总和为0
	free(nums); // 清理内存
	return (0);
}

// 递归决策树：

// 每个数字是一个决策点：选或不选
// 所有可能的组合构成一棵深度为n的二叉树

// 隐式回溯：

// 没有显式的actual[p_act] = 0恢复操作
// 通过函数参数的独立性和数组覆盖实现回溯

// 状态传递：

// p_num: 控制处理进度
// suma: 记录当前路径的和
// p_act: 记录当前子集大小