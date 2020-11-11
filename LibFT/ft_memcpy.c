/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:45:35 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/10 13:45:39 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (!count || dst == src)
			return ((void *)dst);
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i += 1;
	}
	return ((void *)dst);
}
