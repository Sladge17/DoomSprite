/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:04:15 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/16 12:04:18 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	f_count(char const *s, char c)
{
	size_t	count;

	count = (*s == c || *s == '\0') ? 0 : 1;
	while (*s != '\0')
	{
		if (*s == c && *(s + 1) != c)
			if (*(s + 1) != '\0')
				count += 1;
		s += 1;
	}
	return (count);
}

static size_t	f_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*(s + len) != c && *(s + len) != '\0')
		len += 1;
	return (len);
}

static char		**f_freemem(char **str, size_t number)
{
	size_t	i;

	i = 0;
	while (i < number)
	{
		free(str[i]);
		str[i] = NULL;
		i += 1;
	}
	free(str);
	str = NULL;
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	size_t	len;
	size_t	count;
	size_t	i;

	if (!s || !c)
		return (NULL);
	count = f_count(s, c);
	str = ft_memalloc(sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < count)
	{
		while (*s == c && *s != '\0')
			s += 1;
		len = f_len(s, c);
		str[i] = ft_strnew(len);
		if (!str[i])
			return (f_freemem(str, i));
		ft_strncpy(str[i], s, len);
		s += len;
		i += 1;
	}
	return (str);
}
