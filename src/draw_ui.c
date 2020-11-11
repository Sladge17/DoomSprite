/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 17:42:32 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/09 12:27:18 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// void	draw_ui(int *pixel, int *img)
// {
// 	int		tex_shift_x = 0;
// 	int		tex_shift_y = 33;
// 	int		i = 0;
// 	// // for athlas.png
// 	while (i < 65 * 65)
// 	{
// 		if (img[i % 65 + 1039 * (i / 65) + (65 * tex_shift_x) + (1039 * 65 * tex_shift_y)] != 0xFF980088)
// 			pixel[i % 65 + WIDTH * (i / 65)] = img[i % 65 + 1039 * (i / 65) + (65 * tex_shift_x) + (1039 * 65 * tex_shift_y)];
// 		i += 1;
// 	}
// }

void	draw_ui(int *pixel, int *img, int tile_u, int tile_v)
{
	int		cursor[2];
	int		texel[2];
	// SDL_SetWindowIcon()

	cursor[0] = -1;
	while (++cursor[0] < (HEIGHT - 100))
	{
		cursor[1] = -1;
		while (++cursor[1] < (HEIGHT - 100))
		{
			texel[0] = (cursor[0] / (double)(HEIGHT - 100)) * 65;
			texel[1] = (cursor[1] / (double)(HEIGHT - 100)) * 65;
			if (texel[0] != 64 && texel[1] != 64 &&
				img[texel[0] + 1039 * texel[1] +
				(65 * tile_u) + (67535 * tile_v)] != 0xFF980088)
				pixel[cursor[0] + WIDTH / 4 + 50 +
				WIDTH * (cursor[1] + 120)] =
				img[texel[0] + 1039 * texel[1] +
				(65 * tile_u) + (67535 * tile_v)];
		}
	}
}

// void	draw_ui(int *pixel, int *img, int tile_u, int tile_v)
// {
// 	int		i;
// 	int		j;
// 	int		u;
// 	int		v;
// 	i = 0;
// 	while (i < (HEIGHT - 100) * (HEIGHT - 100))
// 	{

// 		u = (i / (double)(HEIGHT - 100)) * 65;
// 		v = (j / (double)(HEIGHT - 100)) * 65;
// 		if (img[u + 1039 * v + (65 * tile_u) + (1039 * 65 * tile_v)] != 0xFF980088 &&
// 			u != 64 && v != 64)
// 			pixel[i + WIDTH / 4 + 50 + WIDTH * (j + 120)] = img[u + 1039 * v + (65 * tile_u) + (1039 * 65 * tile_v)];
// 		i += 1;
// 	}

// }