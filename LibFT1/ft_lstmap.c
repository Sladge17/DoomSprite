/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:22:32 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/19 13:22:37 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	f_link(t_list **head, t_list **end, t_list *w_list)
{
	if (!*head)
	{
		*head = w_list;
		*end = w_list;
		return ;
	}
	(*end)->next = w_list;
	*end = w_list;
}

static void	f_clear(t_list **head, t_list **w_list)
{
	while (head)
	{
		*w_list = *head;
		*head = (*head)->next;
		free((*w_list)->content);
		free(*w_list);
		*w_list = NULL;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*end;
	t_list	*w_list;

	if (!lst || !f)
		return (NULL);
	head = NULL;
	end = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		w_list = (t_list *)malloc(sizeof(t_list));
		if (!w_list)
		{
			f_clear(&head, &w_list);
			return (NULL);
		}
		w_list = f(lst);
		w_list->next = NULL;
		f_link(&head, &end, w_list);
		lst = lst->next;
	}
	return (head);
}
