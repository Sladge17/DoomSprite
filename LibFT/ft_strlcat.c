/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:19:26 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/12 12:19:30 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t buf)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	if (buf >= len_dst + 1)
	{
		while (len_dst + i < buf - 1 && src[i] != '\0')
		{
			dst[len_dst + i] = src[i];
			i += 1;
		}
		dst[len_dst + i] = '\0';
		return (len_dst + len_src);
	}
	return (buf + len_src);
}
