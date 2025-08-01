#include "ft_list.h"
#include <stdlib.h>

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void *, void *))
{
	t_list *current;
	t_list *prev;
	t_list *to_free;

	if (begin_list == NULL || *begin_list == NULL || cmp == NULL)
		return;

	current = *begin_list;
	prev = NULL;
	while (current != NULL)
	{
		if (cmp(current->data, data_ref) == 0)
		{
			to_free = current;
			if (prev == NULL)
				*begin_list = current->next;
			else
				prev->next = current->next;
			current = current->next;
			free(to_free);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}