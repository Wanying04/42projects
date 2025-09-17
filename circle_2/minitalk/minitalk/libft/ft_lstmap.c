/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:19:20 by wtang             #+#    #+#             */
/*   Updated: 2024/12/20 15:39:22 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_null(t_list *new_list, void (*del)(void *))
{
	t_list	*temp;

	while (new_list)
	{
		temp = new_list->next;
		del(new_list->content);
		free(new_list);
		new_list = temp;
	}
}

static t_list	*ft_lstnew_content(void *content, void *(*f)(void *))
{
	t_list	*new_node;
	void	*new_content;

	new_content = f(content);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = new_content;
	new_node->next = NULL;
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*temp;

	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew_content(lst->content, f);
		if (!new_node)
		{
			ft_null(new_list, del);
			return (NULL);
		}
		if (!new_list)
			new_list = new_node;
		else
		{
			temp = new_list;
			while (temp->next)
				temp = temp->next;
			temp->next = new_node;
		}
		lst = lst->next;
	}
	return (new_list);
}
