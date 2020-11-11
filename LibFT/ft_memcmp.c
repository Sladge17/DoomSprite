/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:42:34 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/11 15:42:39 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *src1, const void *src2, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (((unsigned char *)src1)[i] != ((unsigned char *)src2)[i])
			return (((unsigned char *)src1)[i] - ((unsigned char *)src2)[i]);
		i += 1;
	}
	return (0);
}
