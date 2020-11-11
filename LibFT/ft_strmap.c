/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:19:40 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/14 16:19:44 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len_s;
	char	*str;

	if (!s || !f)
		return (NULL);
	len_s = ft_strlen(s);
	str = ft_strnew(len_s);
	if (!str)
		return (NULL);
	while (*s != '\0')
	{
		*str = f(*s);
		str += 1;
		s += 1;
	}
	*str = '\0';
	str -= len_s;
	return (str);
}
