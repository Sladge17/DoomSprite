/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:00:03 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/17 13:00:06 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	if (!s || fd == -1)
		return ;
	while (*s != '\0')
	{
		ft_putchar_fd(*s, fd);
		s += 1;
	}
}
