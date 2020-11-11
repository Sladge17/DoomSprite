/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:20:46 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/14 17:20:50 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len_s;
	unsigned int	i;
	char			*str;

	if (!s || !f)
		return (NULL);
	len_s = ft_strlen(s);
	str = ft_strnew(len_s);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i += 1;
	}
	str[i] = '\0';
	return (str);
}
