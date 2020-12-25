/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:06:43 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/18 16:06:47 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_node;

	if (content_size > content_size + 1)
		return (NULL);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	if (content == NULL)
	{
		new_node->content = NULL;
		new_node->content_size = 0;
		new_node->next = NULL;
		return (new_node);
	}
	new_node->content = (void *)malloc(sizeof(content_size));
	if (!new_node->content)
	{
		free(new_node);
		return (NULL);
	}
	ft_memcpy(new_node->content, content, content_size);
	new_node->content_size = content_size;
	new_node->next = NULL;
	return (new_node);
}
