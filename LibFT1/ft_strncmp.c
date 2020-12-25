/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:15:32 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/13 15:15:36 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *str1, const char *str2, size_t cnt)
{
	size_t	i;

	if (!str1 && !str2)
		return (0);
	i = 0;
	while (*str1 != '\0' && i < cnt)
	{
		if (*str1 != *str2)
			return (*(unsigned char *)str1 - *(unsigned char *)str2);
		str1 += 1;
		str2 += 1;
		i += 1;
	}
	if (*str2 != '\0' && i < cnt)
		return ((-1) * (*(unsigned char *)str2));
	return (0);
}
