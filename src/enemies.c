/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:57:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/11/16 20:00:04 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_enemy	*def_enemies(t_map *map)
{
	t_enemy		*enemies;
	t_enemy		*node;
	t_enemy		*end;
	int			cursor;

	enemies = NULL;
	cursor = 0; // MAYBE NEED OPTIMIZE !!!!
	while (cursor < map->width * map->height)
	{
		if (map->field[cursor] == 'E')
		{
			node = (t_enemy *)malloc(sizeof(t_enemy));
			node->pos_x = cursor % map->width + 0.5;
			node->pos_y = cursor / map->width + 0.5;
			node->normal = 0 * M_PI / 180;
			node->main_tile = 156;
			
			if (!enemies)
			{
				enemies = node;
				end = node;
				cursor += 1;
				continue ;
			}
			end->next = node;
			end = end->next;
		}
		cursor += 1;
	}
	end->next = NULL;
	return(enemies);
}

void	set_enemies(t_enemy *enemies, t_player *player)
{
	while (enemies)
	{
		enemies->g_dir = atan2(enemies->pos_x - player->pos_x, enemies->pos_y - player->pos_y);

		// if (enemies->g_dir >= -22.5 * M_PI / 180 && enemies->g_dir < 22.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile;
		// else if (enemies->g_dir >= 22.5 * M_PI / 180 && enemies->g_dir < 67.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile + 1;
		// else if (enemies->g_dir >= 67.5 * M_PI / 180 && enemies->g_dir < 112.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile + 2;
		// else if (enemies->g_dir >= 112.5 * M_PI / 180 && enemies->g_dir < 157.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile + 3;
		// else if (enemies->g_dir >= -157.5 * M_PI / 180 && enemies->g_dir < -112.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile + 3;
		// else if (enemies->g_dir >= -112.5 * M_PI / 180 && enemies->g_dir < -67.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile + 2;
		// else if (enemies->g_dir >= -67.5 * M_PI / 180 && enemies->g_dir < -22.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile + 1;
		// else
		// 	enemies->tile = enemies->main_tile + 4;


		if (fabs(player->angle - enemies->normal) <= 22.5 * M_PI / 180)
			enemies->tile = enemies->main_tile;
		else if (fabs(player->angle - enemies->normal) <= 67.5 * M_PI / 180)
			enemies->tile = enemies->main_tile + 1;
		else if (fabs(player->angle - enemies->normal) <= 112.5 * M_PI / 180)
			enemies->tile = enemies->main_tile + 2;
		else if (fabs(player->angle - enemies->normal) <= 157.5 * M_PI / 180)
			enemies->tile = enemies->main_tile + 3;
		else
		{
			enemies->tile = enemies->main_tile + 4;
		}
		



		// if (enemies->g_dir >= -22.5 * M_PI / 180 && enemies->g_dir < 22.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile;
		// else if (enemies->g_dir >= 22.5 * M_PI / 180 && enemies->g_dir < 67.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile;
		// else if (enemies->g_dir >= 67.5 * M_PI / 180 && enemies->g_dir < 112.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile;
		// else if (enemies->g_dir >= 112.5 * M_PI / 180 && enemies->g_dir < 157.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile;
		// else if (enemies->g_dir >= -157.5 * M_PI / 180 && enemies->g_dir < -112.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile;
		// else if (enemies->g_dir >= -112.5 * M_PI / 180 && enemies->g_dir < -67.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile;
		// else if (enemies->g_dir >= -67.5 * M_PI / 180 && enemies->g_dir < -22.5 * M_PI / 180)
		// 	enemies->tile = enemies->main_tile;
		// else
		// 	enemies->tile = enemies->main_tile;

		enemies->p_dir = enemies->g_dir;
		if (enemies->p_dir - player->angle > M_PI)
			enemies->p_dir -= 2 * M_PI; 
		if (enemies->p_dir - player->angle < -M_PI)
			enemies->p_dir += 2 * M_PI;
		enemies->p_dir = enemies->p_dir - player->angle;
		
		enemies->dist = sqrt(pow(enemies->pos_x - player->pos_x, 2) + pow(enemies->pos_y - player->pos_y, 2));
		enemies->size = (int)(HEIGHT * 2 / enemies->dist);
		enemies->shift_x = WIDTH / 2 - (enemies->p_dir * (WIDTH) / (player->fov));
		enemies->h_offset = enemies->shift_x - enemies->size / 2;
		enemies->v_offset = HEIGHT / 2 - enemies->size / 2;
		
		enemies = enemies->next;
	}
}

void	draw_enemies(t_player *player, t_enemy *enemies, int *pixel, int *img, double *z_buff)
{
	int		cursor_x;
	
	while (enemies)
	{
		cursor_x = 0;
		while (cursor_x < enemies->size)
		{
			if (enemies->h_offset + cursor_x < 0 || enemies->h_offset + cursor_x >= WIDTH)
			{
				cursor_x += 1;
				continue;
			}
			draw_vertline2(enemies, pixel, img, z_buff, cursor_x);
			cursor_x += 1;
		}
		enemies = enemies->next;
	}
}

void	draw_vertline2(t_enemy *enemies, int *pixel, int *img, double *z_buff, int cursor_x)
{
	int		tile_u;
	int		tile_v;
	int		cursor_y;

	tile_u = enemies->tile % 16;
	tile_v = enemies->tile / 16;
	cursor_y = 0;
	while (cursor_y < enemies->size)
	{
		if (enemies->v_offset + cursor_y < 0 || enemies->v_offset + cursor_y >= HEIGHT)
		{
			cursor_y += 1;
			continue;
		}
		if (enemies->g_dir < -22.5 * M_PI / 180 && enemies->g_dir >= -157.5 * M_PI / 180)
		{
			if (img[(int)(64 * ((enemies->size - cursor_x - 1) / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFF980088 &&
				enemies->dist < z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)])
			{
				pixel[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = img[(int)(64 * ((enemies->size - cursor_x - 1) / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65];
				z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = enemies->dist;
			}
		}
		else
		{
			if (img[(int)(64 * (cursor_x / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFF980088 &&
				enemies->dist < z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)])
			{
				pixel[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = img[(int)(64 * (cursor_x / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65];
				z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = enemies->dist;
			}
		}
		cursor_y += 1;
	}
}



// TMP FUNC
void	print_enemies(t_enemy *enemies)
{
	t_enemy	*cursor;

	cursor = enemies;
	while(cursor)
	{
		printf("%f, %f\n", cursor->pos_x, cursor->pos_y);
		cursor = cursor->next;
	}
}
