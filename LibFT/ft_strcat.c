/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:40:00 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/12 11:40:03 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0')
	{
		dst[len + i] = src[i];
		i += 1;
	}
	dst[len + i] = '\0';
	return (dst);
}
