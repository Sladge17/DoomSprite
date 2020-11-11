/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:53:54 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/05 19:37:41 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_range(int min, int max)
{
	int		len;
	int		*arr;
	int		n;

	len = max - min;
	if (len <= 0)
		return (NULL);
	arr = (int *)malloc(sizeof(int) * len);
	if (arr == NULL)
		return (NULL);
	n = 0;
	while (n < len)
	{
		arr[n] = min + n;
		n += 1;
	}
	return (arr);
}
