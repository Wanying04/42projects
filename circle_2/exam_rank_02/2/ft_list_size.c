/*编写一个函数，返回传递给它的链表中元素的数量。*/

typedef struct s_list
{
	struct s_list *next;
	void          *data;
} t_list;

int	ft_list_size(t_list *begin_list)
{
	int count = 0;
	
	while (begin_list != 0)  // 或写成 begin_list != NULL
	{
		count++;
		begin_list = begin_list->next;
	}
	return count;
}

/*1、初始化计数器：从 0 开始。

2、遍历链表：

从头节点 (begin_list) 开始，依次访问每个节点的 next 指针。

每访问一个节点，计数器加 1。

3、终止条件：当 next 为 NULL（或 0）时停止。*/