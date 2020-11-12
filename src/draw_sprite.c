/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:24:05 by jthuy             #+#    #+#             */
/*   Updated: 2020/11/12 19:26:16 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_sprite(t_map *map, t_player *player, int *pixel, int *img, int sprite_poz, int tile_numb, double *z_buff)
{
	t_sprite	*sprite;

	sprite = (t_sprite *)malloc(sizeof(t_sprite));

	def_spriteparam(sprite, sprite_poz, map, player);

	if (sprite->rotator >= -22.5 * M_PI / 180 && sprite->rotator < 22.5 * M_PI / 180)
		tile_numb = tile_numb;
	else if (sprite->rotator >= 22.5 * M_PI / 180 && sprite->rotator < 67.5 * M_PI / 180)
		tile_numb = tile_numb + 1;
	else if (sprite->rotator >= 67.5 * M_PI / 180 && sprite->rotator < 112.5 * M_PI / 180)
		tile_numb = tile_numb + 2;
	else if (sprite->rotator >= 112.5 * M_PI / 180 && sprite->rotator < 157.5 * M_PI / 180)
		tile_numb = tile_numb + 3;
	// else if (sprite->rotator >= 157.5 * M_PI / 180 && sprite->rotator < -157.5 * M_PI / 180)
	// 	tile_numb = 160;
	else if (sprite->rotator >= -157.5 * M_PI / 180 && sprite->rotator < -112.5 * M_PI / 180)
		tile_numb = tile_numb + 3;
	else if (sprite->rotator >= -112.5 * M_PI / 180 && sprite->rotator < -67.5 * M_PI / 180)
		tile_numb = tile_numb + 2;
	else if (sprite->rotator >= -67.5 * M_PI / 180 && sprite->rotator < -22.5 * M_PI / 180)
		tile_numb = tile_numb + 1;
	else
		tile_numb = tile_numb + 4;
	
	
	
	
	sprite->cursor_x = 0;
	while (sprite->cursor_x < sprite->size)
	{
		if (sprite->h_offset + sprite->cursor_x < 0 || sprite->h_offset + sprite->cursor_x >= WIDTH)
		{
			sprite->cursor_x += 1;
			continue;
		}
		draw_vertline(sprite, pixel, img, tile_numb, z_buff);
		sprite->cursor_x += 1;
	}
}

void	def_spriteparam(t_sprite *sprite, int sprite_poz, t_map *map, t_player *player)
{
	sprite->pos_x = sprite_poz % map->width + 0.5;
	sprite->pos_y = sprite_poz / map->width + 0.5;

	sprite->direction = atan2(sprite->pos_x - player->pos_x, sprite->pos_y - player->pos_y);
	sprite->rotator = sprite->direction;
	while (sprite->direction - player->angle > M_PI)
		sprite->direction -= 2 * M_PI; 
	while (sprite->direction - player->angle < -M_PI)
		sprite->direction += 2 * M_PI;


	
	sprite->dist = sqrt(pow(sprite->pos_x - player->pos_x, 2) + pow(sprite->pos_y - player->pos_y, 2));
	// sprite->size = (int)(HEIGHT / sprite->dist) < 4000 ? (int)(HEIGHT * 2 / sprite->dist) : 4000;
	sprite->size = (int)(HEIGHT * 2 / sprite->dist);
	
	double sp_dir_pl = sprite->direction - player->angle;
	int shift_x = WIDTH / 2 - (sp_dir_pl * (WIDTH) / (player->fov));
	sprite->h_offset = shift_x - sprite->size / 2;

	sprite->v_offset = HEIGHT / 2 - sprite->size / 2;
}

// void	draw_vertline(t_sprite *sprite, int *pixel, int *img, int tile_numb, double *z_buff)
// {
// 	sprite->cursor_y = 0;
// 	while (sprite->cursor_y < sprite->size)
// 	{
// 		if (sprite->v_offset + sprite->cursor_y < 0 || sprite->v_offset + sprite->cursor_y >= HEIGHT)
// 		{
// 			sprite->cursor_y += 1;
// 			continue;
// 		}
// 		if (img[(int)(65 * (sprite->cursor_x / (double)sprite->size)) + 1039 * (int)(65 * (sprite->cursor_y / (double)sprite->size)) + tile_numb % 16 * 65 + tile_numb / 16 * 1039 * 65] != 0xFF980088 &&
// 			(int)(65 * (sprite->cursor_x / (double)sprite->size)) != 64 && (int)(65 * (sprite->cursor_y / (double)sprite->size)) != 64 &&
// 			sprite->dist < z_buff[sprite->h_offset + sprite->cursor_x + WIDTH * (sprite->v_offset + sprite->cursor_y)])
// 		{
// 			pixel[sprite->h_offset + sprite->cursor_x + WIDTH * (sprite->v_offset + sprite->cursor_y)] = img[(int)(65 * (sprite->cursor_x / (double)sprite->size)) + 1039 * (int)(65 * (sprite->cursor_y / (double)sprite->size)) + tile_numb % 16 * 65 + tile_numb / 16 * 1039 * 65];
// 			z_buff[sprite->h_offset + sprite->cursor_x + WIDTH * (sprite->v_offset + sprite->cursor_y)] = sprite->dist;
// 		}
// 		sprite->cursor_y += 1;
// 	}
// }
void	draw_vertline(t_sprite *sprite, int *pixel, int *img, int tile_numb, double *z_buff)
{
	int		tile_u;
	int		tile_v;

	tile_u = tile_numb % 16;
	tile_v = tile_numb / 16;
	
	
	sprite->cursor_y = 0;
	while (sprite->cursor_y < sprite->size)
	{
		if (sprite->v_offset + sprite->cursor_y < 0 || sprite->v_offset + sprite->cursor_y >= HEIGHT)
		{
			sprite->cursor_y += 1;
			continue;
		}
		
		if (sprite->rotator < -22.5 * M_PI / 180 && sprite->rotator > -157.5 * M_PI / 180) // NEED THINK ABOUT LIMITS
		{
			if (img[(int)(64 * ((sprite->size - sprite->cursor_x - 1) / (double)sprite->size)) + 1039 * (int)(64 * (sprite->cursor_y / (double)sprite->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFF980088 &&
				sprite->dist < z_buff[sprite->h_offset + sprite->cursor_x + WIDTH * (sprite->v_offset + sprite->cursor_y)])
			{
				pixel[sprite->h_offset + sprite->cursor_x + WIDTH * (sprite->v_offset + sprite->cursor_y)] = img[(int)(64 * ((sprite->size - sprite->cursor_x - 1) / (double)sprite->size)) + 1039 * (int)(64 * (sprite->cursor_y / (double)sprite->size)) + tile_u * 65 + tile_v * 1039 * 65];
				z_buff[sprite->h_offset + sprite->cursor_x + WIDTH * (sprite->v_offset + sprite->cursor_y)] = sprite->dist;
			}
		}
		else
		{
			if (img[(int)(64 * (sprite->cursor_x / (double)sprite->size)) + 1039 * (int)(64 * (sprite->cursor_y / (double)sprite->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFF980088 &&
				sprite->dist < z_buff[sprite->h_offset + sprite->cursor_x + WIDTH * (sprite->v_offset + sprite->cursor_y)])
			{
				pixel[sprite->h_offset + sprite->cursor_x + WIDTH * (sprite->v_offset + sprite->cursor_y)] = img[(int)(64 * (sprite->cursor_x / (double)sprite->size)) + 1039 * (int)(64 * (sprite->cursor_y / (double)sprite->size)) + tile_u * 65 + tile_v * 1039 * 65];
				z_buff[sprite->h_offset + sprite->cursor_x + WIDTH * (sprite->v_offset + sprite->cursor_y)] = sprite->dist;
			}
		}
		
		sprite->cursor_y += 1;
	}
}





// int		def_pixel(t_drawer *drawer, int tile_u, int tile_v, char inverse)
// {
// 	drawer->athlas_pix = 65 * tile_u +
// 		(63 * (drawer->cursor_y - drawer->wall_up) /
// 		drawer->wall_len) * 1039 + (67535 * tile_v);
// 	drawer->athlas_pix = inverse ?
// 		63 - drawer->tex_u + drawer->athlas_pix :
// 		drawer->tex_u + drawer->athlas_pix;
// 	return (drawer->athlas_pix);
// }