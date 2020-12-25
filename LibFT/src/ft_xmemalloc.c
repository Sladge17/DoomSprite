/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmemalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:54:39 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/12 15:03:22 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_xmemalloc(size_t size)
{
	char	*str;
	
	str = ft_memalloc(sizeof(char) * size);
	if (str == NULL)
	{
		ft_putendl_fd("Error allocated (return NULL)", 2);
		exit(1);
	}
	return (str);
}