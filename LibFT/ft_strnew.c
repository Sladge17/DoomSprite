/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:00:22 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/14 15:00:25 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*memory;

	if (size > size + 1)
		return (NULL);
	if (!(memory = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(memory, size + 1);
	return (memory);
}
