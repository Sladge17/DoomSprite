/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:15:09 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/11 18:15:14 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count && src[i] != '\0')
	{
		dst[i] = src[i];
		i += 1;
	}
	while (i < count)
	{
		dst[i] = '\0';
		i += 1;
	}
	return (dst);
}
