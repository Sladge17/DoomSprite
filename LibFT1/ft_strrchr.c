/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 20:44:51 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/12 20:44:55 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*i;

	i = NULL;
	while (*str != '\0')
	{
		if (*str == (char)c)
			i = (char *)str;
		str += 1;
	}
	if (c == '\0')
		return ((char *)str);
	return (i);
}
