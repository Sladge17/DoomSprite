/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 11:48:17 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/13 11:48:20 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *src, const char *dst)
{
	size_t	i;

	if (*dst == '\0')
		return ((char *)src);
	while (*src != '\0')
	{
		i = 0;
		while (*(src + i) == *(dst + i))
		{
			if (*(dst + i + 1) == '\0')
				return ((char *)src);
			i += 1;
		}
		src += 1;
	}
	return (NULL);
}
