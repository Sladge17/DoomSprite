/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:48:02 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/12 11:48:07 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(dst);
	i = 0;
	while (i < n && src[i] != '\0')
	{
		dst[len + i] = src[i];
		i += 1;
	}
	dst[len + i] = '\0';
	return (dst);
}
