/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 14:53:01 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/13 14:53:06 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *str1, const char *str2)
{
	if (!str1 && !str2)
		return (0);
	while (*str1 != '\0')
	{
		if (*str1 != *str2)
			return (*(unsigned char *)str1 - *(unsigned char *)str2);
		str1 += 1;
		str2 += 1;
	}
	if (*str2 != '\0')
		return ((-1) * (*(unsigned char *)str2));
	return (0);
}
