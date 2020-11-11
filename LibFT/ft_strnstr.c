/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 13:23:37 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/13 13:23:40 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *dst, size_t count)
{
	size_t	i;
	size_t	j;

	if (*dst == '\0')
		return ((char *)src);
	j = 0;
	while (*src != '\0' && j < count)
	{
		i = 0;
		while (*(src + i) == *(dst + i) && (j + i) < count)
		{
			if (*(dst + i + 1) == '\0')
				return ((char *)src);
			i += 1;
		}
		src += 1;
		j += 1;
	}
	return (NULL);
}
