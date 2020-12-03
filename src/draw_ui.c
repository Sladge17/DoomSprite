/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 17:42:32 by jthuy             #+#    #+#             */
/*   Updated: 2020/12/03 15:46:11 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// void	draw_ui(int *pixel, int *img, int tile_u, int tile_v)
// {
// 	int		cursor[2];
// 	int		texel[2];
// 	// SDL_SetWindowIcon()

// 	cursor[0] = -1;
// 	while (++cursor[0] < (HEIGHT - 100))
// 	{
// 		cursor[1] = -1;
// 		while (++cursor[1] < (HEIGHT - 100))
// 		{
// 			texel[0] = (cursor[0] / (double)(HEIGHT - 100)) * 65;
// 			texel[1] = (cursor[1] / (double)(HEIGHT - 100)) * 65;
// 			if (texel[0] != 64 && texel[1] != 64 &&
// 				img[texel[0] + 1039 * texel[1] +
// 				(65 * tile_u) + (67535 * tile_v)] != 0xFF980088)
// 				pixel[cursor[0] + WIDTH / 4 + 50 +
// 				WIDTH * (cursor[1] + 120)] =
// 				img[texel[0] + 1039 * texel[1] +
// 				(65 * tile_u) + (67535 * tile_v)];
// 		}
// 	}
// }

void	draw_ui(int *pixel, int *img, int tile)
{
	int		cursor[2];
	int		texel[2];
	
	int		tile_u;
	int		tile_v;

	tile_u = tile % 16;
	tile_v = tile / 16;

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

void	draw_cross(int *pixel, t_enemy *enemies)
{
	int		i;
	int		ontarget;
	
	while (enemies)
	{
		if (abs(WIDTH / 2 - enemies->sprite->shift_x) < enemies->sprite->size / 2)
		{
			ontarget = 0xFF0000;
			break ;
		}
		else
			ontarget = 0xFF;
		enemies = enemies->next;
	}
	i = WIDTH / 2 + WIDTH * 300;
	while (i < WIDTH * HEIGHT - WIDTH * 300)
	{
		pixel[i] = ontarget;
		i += WIDTH;
	}
	i = WIDTH * HEIGHT / 2 + 700;
	while (i < WIDTH * HEIGHT / 2 + WIDTH - 700)
	{
		pixel[i] = ontarget;
		i += 1;
	}
}
