/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:04:46 by jthuy             #+#    #+#             */
/*   Updated: 2020/12/04 13:17:06 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_props	*def_props(t_map *map)
{
	t_props	*props;
	t_props	*node;
	t_props	*cursor;
	int		index;

	props = NULL;
	index = 0;
	while (map->field[index] != '\0')
	{
		if (map->field[index] == 'H')
		{
			node = (t_props *)malloc(sizeof(t_props)); // NEED PROTECT
			node->pos_x = index % map->width;
			node->pos_y = index / map->width;
			node->main_tile = 133;
			if (!props)
			{
				props = node;
				cursor = props;
				index += 1;
				continue ;
			}
			cursor->next = node;
			cursor = cursor->next;
		}
		if (map->field[index] == 'A')
		{
			node = (t_props *)malloc(sizeof(t_props)); // NEED PROTECT
			node->pos_x = index % map->width;
			node->pos_y = index / map->width;
			node->main_tile = 134;
			if (!props)
			{
				props = node;
				cursor = props;
				index += 1;
				continue ;
			}
			cursor->next = node;
			cursor = cursor->next;
		}
		index += 1;
	}
	if (cursor)
		cursor->next = NULL;
	return (props);
}

void	set_propsparam(t_props *props, t_player *player)
{
	while (props)
	{
		props->p_dir = atan2(props->pos_x - player->pos_x, props->pos_y - player->pos_y);
		if (props->p_dir - player->angle > M_PI)
			props->p_dir -= 2 * M_PI; 
		else if (props->p_dir - player->angle < -M_PI)
			props->p_dir += 2 * M_PI;
		props->p_dir -= player->angle;
		props->shift_x = WIDTH / 2 - (props->p_dir * (WIDTH) / (player->fov));
		
		props->dist = sqrt(pow(props->pos_x - player->pos_x, 2) + pow(props->pos_y - player->pos_y, 2));
		props->size = (int)(HEIGHT * 2 / props->dist);
		props->h_offset = props->shift_x - props->size / 2;
		props->v_offset = HEIGHT / 2 - props->size / 2;
		props = props->next;
	}
}

void	draw_props(t_player *player, t_props *props, int *pixel, int *img, double *z_buff)
{
	int		cursor_x;
	
	while (props)
	{
		cursor_x = 0;
		while (cursor_x < props->size)
		{
			if (props->h_offset + cursor_x < 0 || props->h_offset + cursor_x >= WIDTH)
			{
				cursor_x += 1;
				continue;
			}
			draw_vertlprops(props, pixel, img, z_buff, cursor_x, player);
			cursor_x += 1;
		}
		props = props->next;
	}
}

void	draw_vertlprops(t_props *props, int *pixel, int *img, double *z_buff, int cursor_x, t_player *player)
{
	int		tile_u;
	int		tile_v;
	int		cursor_y;

	tile_u = props->main_tile % 16;
	tile_v = props->main_tile / 16;
	cursor_y = 0;
	while (cursor_y < props->size)
	{
		if (props->v_offset + cursor_y < 0 || props->v_offset + cursor_y >= HEIGHT)
		{
			cursor_y += 1;
			continue;
		}

		//WITH ALPHA
		if (img[(int)(64 * (cursor_x / (double)props->size)) + 1039 * (int)(64 * (cursor_y / (double)props->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFF980088 &&
			props->dist < z_buff[props->h_offset + cursor_x + WIDTH * (props->v_offset + cursor_y)])
		{
			pixel[props->h_offset + cursor_x + WIDTH * (props->v_offset + cursor_y)] = img[(int)(64 * (cursor_x / (double)props->size)) + 1039 * (int)(64 * (cursor_y / (double)props->size)) + tile_u * 65 + tile_v * 1039 * 65];
			z_buff[props->h_offset + cursor_x + WIDTH * (props->v_offset + cursor_y)] = props->dist;
		}
		
		// // WITHOUT ALPHA
		// if (enemies->p_div < 0 * M_PI / 180 && enemies->tile != enemies->shift_tile && enemies->tile != enemies->shift_tile + 4)
		// {
		// 	if (enemies->dist < z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)])
		// 	{
		// 		pixel[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = img[(int)(64 * ((enemies->size - cursor_x - 1) / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65];
		// 		z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = enemies->dist;
		// 	}
		// }
		// else
		// {
		// 	if (enemies->dist < z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)])
		// 	{
		// 		pixel[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = img[(int)(64 * (cursor_x / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65];
		// 		z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = enemies->dist;
		// 	}
		// }	
		
	
		// // ENEMY_MASK
		// if (enemies->p_div < 0 * M_PI / 180 && enemies->tile != enemies->shift_tile && enemies->tile != enemies->shift_tile + 4)
		// {
		// 	if (img[(int)(64 * ((enemies->size - cursor_x - 1) / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFF980088 &&
		// 		enemies->dist < z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)])
		// 	{
		// 		pixel[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = 0xFFFFFF;
		// 		z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = enemies->dist;
		// 	}
		// }
		// else
		// {
		// 	if (img[(int)(64 * (cursor_x / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFF980088 &&
		// 		enemies->dist < z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)])
		// 	{
		// 		pixel[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = 0xFFFFFF;
		// 		z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = enemies->dist;
		// 	}
		// }	
		
		cursor_y += 1;
	}
}

// TMP FUNC
void	print_props(t_props *props)
{
	while (props)
	{
		printf("%f, %f\n", props->pos_x, props->pos_y);
		props = props->next;
	}
}