/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:27:26 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/10 15:27:36 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t cnt)
{
	size_t	i;

	i = 0;
	while (i < cnt)
	{
		if (((unsigned char *)src)[i] == (unsigned char)c)
		{
			((unsigned char *)dst)[i] = (unsigned char)c;
			return ((void *)(dst + i + 1));
		}
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i += 1;
	}
	return (NULL);
}
