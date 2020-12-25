/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 09:42:54 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/11 09:42:59 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t count)
{
	size_t	i;

	i = 0;
	if (dst < src)
		while (i < count)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i += 1;
		}
	if (dst > src)
	{
		while (i < count)
		{
			((unsigned char *)dst)[count - 1 - i] =
			((unsigned char *)src)[count - 1 - i];
			i += 1;
		}
	}
	return ((void *)dst);
}
