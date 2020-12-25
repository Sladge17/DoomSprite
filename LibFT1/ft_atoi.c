/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:28:34 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/13 15:28:38 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	unsigned long int	num;
	int					sign;

	while ((9 <= *str && *str <= 13) || *str == ' ')
		str += 1;
	sign = *str == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		str += 1;
	num = 0;
	while (*str != '\0')
	{
		if ('0' <= *str && *str <= '9')
		{
			num = 10 * num + (*str - '0');
			if (num > 9223372036854775807UL && sign == 1)
				return (-1);
			if (num > 9223372036854775808UL)
				return (0);
			str += 1;
			continue ;
		}
		return (sign * (int)num);
	}
	return (sign * (int)num);
}
