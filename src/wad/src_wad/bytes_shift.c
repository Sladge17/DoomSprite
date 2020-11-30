/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:38:16 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/28 13:19:31 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

// void		print_bit(void *data)
// {
// 	uint16_t	size;
// 	uint16_t	i;
// 	uint32_t	temp;

// 	size = sizeof(data);
// 	temp = (int)data;
// 	i = 0;
// 	while (i < size)
// 	{
// 		if (i % 4 == 0)
// 			write(1, " ", 1);
// 		if (temp & (1 << i))
// 			write(1, "1", 1);
// 		else
// 			write(1, "0", 1);
// 		i++;
// 	}
// }

uint16_t	bytes_to_short(const uint8_t *data, int offset)
{
	return ((data[offset + 1] << 8) | data[offset]);
}

uint32_t	bytes_to_int(const uint8_t *data, int offset)
{
	return ((data[offset + 3] << 24) |
			(data[offset + 2] << 16) |
			(data[offset + 1] << 8) | data[offset]);
}
