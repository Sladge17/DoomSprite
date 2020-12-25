/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:50:40 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/18 19:50:45 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*w_list;

	if (!alst || !*alst || !del)
		return ;
	while (*alst)
	{
		w_list = *alst;
		del(w_list->content, w_list->content_size);
		free(*alst);
		*alst = NULL;
		*alst = w_list->next;
	}
}
