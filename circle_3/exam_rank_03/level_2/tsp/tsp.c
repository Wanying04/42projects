/*
 * 旅行商问题（TSP）暴力解法
 * 目标：寻找访问所有城市一次并返回起点的最短闭环路线
 * 方法：生成所有排列组合（固定起点以优化），计算总距离，找出最小值
 * 限制：最多处理约11个城市（O(n!)复杂度）
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

/* 城市结构体：存储x, y坐标 */
typedef struct {
    float x, y;
} City;

/* 计算两点间欧几里得距离 */
float calculate_distance(City a, City b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx * dx + dy * dy);
}

/* 计算一条完整闭环路线的总距离 */
float calculate_total_distance(City *cities, int *path, int n)
{
    float total = 0.0f;
    int i;
    
    // 路线中相邻城市间的距离
    for (i = 0; i < n - 1; i++)
    {
        total += calculate_distance(cities[path[i]], cities[path[i + 1]]);
    }
    
    // 加上从终点返回起点的距离，形成闭环
    total += calculate_distance(cities[path[n - 1]], cities[path[0]]);
    
    return total;
}

/* 交换两个整数 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* 递归生成排列并寻找最短路径 */
void find_shortest_path(City *cities, int *path, int n, int pos, float *min_distance)
{
    // 基线条件：生成了一个完整排列
    if (pos == n)
    {
        float current_distance = calculate_total_distance(cities, path, n);
        
        if (current_distance < *min_distance)
            *min_distance = current_distance;
        
        return;
    }
    
    // 递归生成所有可能的排列
    for (int i = pos; i < n; i++)
    {
        swap(&path[pos], &path[i]);              // 选择
        find_shortest_path(cities, path, n, pos + 1, min_distance);  // 递归
        swap(&path[pos], &path[i]);              // 回溯，恢复状态
    }
}

int main(void)
{
    City cities[12];  // 存储城市坐标
    int n = 0;        // 实际城市数量
    
    // 从标准输入读取城市坐标，格式为 "x, y"
    while (n < 11 && fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)
    {
        n++;
    }
    
    // 处理特殊情况：城市数少于2
    if (n < 2)
    {
        printf("0.00\n");
        return 0;
    }
    
    int path[12];
    // 初始化路径：城市索引的初始顺序 [0, 1, 2, ..., n-1]
    for (int i = 0; i < n; i++)
    {
        path[i] = i;
    }
    
    float min_distance = FLT_MAX; // 初始化为最大浮点数
    
    /* 关键优化：由于是闭环，固定第一个城市（索引0）在起点位置，
     * 只排列剩余的城市。这能将计算量从 n! 减少到 (n-1)!
     */
    find_shortest_path(cities, path, n, 1, &min_distance);
    
    // 输出最短距离，保留两位小数
    printf("%.2f\n", min_distance);
    
    return 0;
}