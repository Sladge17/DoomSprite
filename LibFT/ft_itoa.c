/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:42:13 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/16 16:42:17 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	f_len(int abs)
{
	int		len;

	len = 1;
	while (abs >= 10)
	{
		abs /= 10;
		len += 1;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int		abs;
	int		sign;
	int		len;
	char	*number;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = n < 0 ? 1 : 0;
	abs = sign == 1 ? (-1) * n : n;
	len = f_len(abs);
	number = ft_strnew(len + sign);
	if (!number)
		return (NULL);
	if (sign == 1)
		number[0] = '-';
	abs = sign == 1 ? (-1) * n : n;
	i = 0;
	while (i < len)
	{
		number[len + sign - 1 - i] = ((abs % 10) + 48);
		abs /= 10;
		i += 1;
	}
	return (number);
}
