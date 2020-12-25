/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:46:18 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/15 14:46:23 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	f_start(char const *s, size_t len)
{
	size_t	start;

	start = 0;
	while ((s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		&& start < len)
		start += 1;
	return (start);
}

static size_t	f_end(char const *s, size_t start, size_t len)
{
	size_t	end;

	end = 0;
	if (start == len)
		return (end);
	while (s[len - 1 - end] == ' ' ||
		s[len - 1 - end] == '\n' || s[len - 1 - end] == '\t')
		end += 1;
	return (end);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	size_t	len;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	start = f_start(s, len);
	end = f_end(s, start, len);
	str = ft_strnew(len - start - end);
	if (!str)
		return (NULL);
	i = 0;
	while (i < (len - start - end))
	{
		str[i] = s[start + i];
		i += 1;
	}
	return (str);
}
