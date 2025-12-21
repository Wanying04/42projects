#include <stdlib.h>
#include <unistd.h>

/**
 * 检查在棋盘的第y列、第x行放置皇后是否安全
 * @param table 一维数组表示的棋盘，table[col] = row 表示第col列的皇后在第row行
 * @param x 要检查的行位置（0-based）
 * @param y 要检查的列位置（0-based）
 * @return 1表示位置安全，0表示冲突
 */
int is_valid_pos(int *table, int x, int y)
{
	int i = 0;
	// 只需要检查前y列（已经放置了皇后的列）
	while (i < y)
	{
		// 条件1: 检查同一行 (x == table[i])
		// 条件2: 检查左上到右下对角线 (x - y == table[i] - i)
		//        在同一对角线上时，行坐标差 = 列坐标差
		// 条件3: 检查左下到右上对角线 (x + y == table[i] + i)
		//        在同一对角线上时，行坐标和 = 列坐标和
		if ((x == table[i]) || (x - y) == (table[i] - i) || (x + y) == (table[i] + i))
			return (0); // 发现冲突
		i++;
	}
	return (1); // 当前位置安全
}

/**
 * 打印一个合法的皇后放置方案
 * @param table 棋盘数组，table[col] = row
 * @param size 棋盘大小（N x N）
 * 
 * 输出格式：每列皇后的行位置（从0开始），用空格分隔
 * 例如："1 3 0 2" 表示：
 *   - 第0列皇后在第1行
 *   - 第1列皇后在第3行
 *   - 第2列皇后在第0行
 *   - 第3列皇后在第2行
 */
void print_table(int *table, int size)
{
	int i = 0;
	while (i < size)
	{
		// 将行索引（整数）转换为ASCII字符
		// 注意：此代码假设size <= 10，对于size>9的棋盘，数字会显示为ASCII符号
		char c = table[i++] + '0';
		write(1, &c, 1);
		
		// 在数字之间添加空格（最后一个数字后不加空格）
		if (i < size)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

/**
 * 递归回溯求解N皇后问题的主函数
 * @param table 棋盘数组
 * @param y 当前正在处理的列（0-based）
 * @param size 棋盘大小
 * 
 * 算法思想：
 * 1. 逐列放置皇后，每列只放一个
 * 2. 在当前列y中，尝试每一行x（0到size-1）
 * 3. 如果位置(x,y)安全，则放置皇后并递归处理下一列(y+1)
 * 4. 当y==size时，表示所有列都成功放置了皇后，得到一个合法解
 * 
 * 回溯机制：
 * 递归调用返回后，自动"回溯"到当前状态，尝试当前列的其他行。
 * 不需要显式移除皇后，因为table[y]会被后续尝试覆盖。
 */
void n_queen(int *table, int y, int size)
{
	int x = 0; // 尝试从第0行开始
	
	// 基线条件：所有列都已成功放置皇后
	if (y == size)
		return (print_table(table, size));
	
	// 尝试在当前列y的每一行放置皇后
	while(x < size)
	{
		// 检查在(x,y)位置放置皇后是否安全
		if (is_valid_pos(table, x, y))
		{
			// 放置皇后：记录第y列的皇后在第x行
			table[y] = x;
			
			// 递归处理下一列（深度优先搜索）
			n_queen(table, y + 1, size);
			
			// 递归返回后，继续尝试当前列的其他行
			// 隐式回溯：无需显式"移除"皇后，下次循环会覆盖table[y]的值
		}
		x++;
	}
}

/**
 * 程序主函数
 * @param ac 命令行参数个数
 * @param av 命令行参数数组
 * 
 * 使用方法：./program N
 * 其中N是棋盘大小，例如 ./program 4 求解4皇后问题
 * 
 * 注意：此代码假设N <= 9，因为打印函数使用单字符数字
 */
int main(int ac, char **av)
{
	// 验证参数：需要一个参数（棋盘大小N）
	if (ac != 2)
		return(1);
	
	// 将命令行参数转换为整数
	int size = atoi(av[1]);
	
	// 在栈上分配棋盘数组
	// table[col] = row 表示第col列的皇后在第row行
	int table[size];
	
	// 从第0列开始递归求解
	n_queen(table, 0, size);
	
	return (0);
}
