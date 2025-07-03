#include "list.h"

void	swap_data(t_list *a, t_list *b)
{
	int temp;
	
	temp = a->data;
	a->data = b->data;
	b->data = temp;
}

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	int	swapped;
	t_list	*current;
	t_list	*last = NULL;
	
	if (lst == NULL)
		return (NULL);
	do {
		swapped = 0;
		current = lst;
		while (current->next != last)
		{
			if (!cmp(current->data, current->next->data))
			{
				swap_data(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	} while (swapped);
	return (lst);
}