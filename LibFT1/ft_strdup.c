/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 16:27:48 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/11 16:27:55 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*nstr;
	int		len;
	int		i;

	len = 0;
	while (str[len] != '\0')
		len += 1;
	nstr = (char *)malloc(sizeof(char) * (len + 1));
	if (nstr == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		nstr[i] = str[i];
		i += 1;
	}
	nstr[i] = '\0';
	return (nstr);
}
