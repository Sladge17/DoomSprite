/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:57:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/11/19 18:09:23 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// t_enemy	*def_enemies(t_map *map)
// {
// 	t_enemy		*enemies;
// 	t_enemy		*node;
// 	t_enemy		*end;
// 	int			cursor;

// 	enemies = NULL;
// 	cursor = 0; // MAYBE NEED OPTIMIZE !!!!
// 	while (cursor < map->width * map->height)
// 	{
// 		if (map->field[cursor] == 'E')
// 		{
// 			node = (t_enemy *)malloc(sizeof(t_enemy));  // NEED PROTECT
// 			node->pos_x = cursor % map->width + 0.5;
// 			node->pos_y = cursor / map->width + 0.5;
// 			node->normal = 180 * M_PI / 180; // AVALUABLE VALUES: 0, 45, 90, 135, 180, 225, 270, 315
// 			node->main_tile = 156;
// 			node->shift_tile = node->main_tile;
			
// 			if (!enemies)
// 			{
// 				enemies = node;
// 				end = node;
// 				cursor += 1;
// 				continue ;
// 			}
// 			end->next = node;
// 			end = end->next;
// 		}
// 		cursor += 1;
// 	}
// 	end->next = NULL;
// 	return(enemies);
// }

#define ELIMIT 1

t_enemy	*def_enemies(t_map *map)
{
	t_enemy		*enemies;
	t_enemy		*node;
	t_enemy		*end;
	int			ecounter;

	enemies = NULL;
	ecounter = 0; 
	while (ecounter < ELIMIT)
	{
		node = (t_enemy *)malloc(sizeof(t_enemy)); // NEED PROTECT
		node->path = def_epath(ecounter);

		// print_epath(node->path);
		// exit(0);
		
		// node->pos_x = ecounter % map->width + 0.5;
		// node->pos_y = ecounter / map->width + 0.5;
		// node->normal = 180 * M_PI / 180; // AVALUABLE VALUES: 0, 45, 90, 135, 180, 225, 270, 315
		
		node->pos_x = node->path->crd_x;
		node->pos_y = node->path->crd_y;
		node->normal = node->path->normal; // AVALUABLE VALUES: 0, 45, 90, 135, 180, 225, 270, 315

		
		
		node->main_tile = 156;
		node->shift_tile = node->main_tile;
		
		if (!enemies)
		{
			enemies = node;
			end = node;
			ecounter += 1;
			continue ;
		}
		end->next = node;
		end = end->next;

		ecounter += 1;
	}
	end->next = NULL;
	return(enemies);
}

t_epath	*def_epath(int ecounter)
{
	t_epath	*epath;
	t_epath	*node;
	t_epath	*cursor;
	char	*field;
	int		counter;
	
	epath = NULL;
	if (!ecounter)
		field =	"................"\
				"................"\
				"................"\
				"................"\
				"................"\
				"................"\
				"................"\
				"................"\
				"................"\
				"................"\
				"................"\
				"...3...2........"\
				"................"\
				"................"\
				"...4...1........"\
				"................";
				
		// field =	"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"..2...1........."\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................";
				
		// field =	"..1......2......"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"..4......3......"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................"\
		// 		"................";

	counter = 0;
	while (*field != '\0')
	{
		// if ((int)field > 48 && (int)field < 58)
		if (*field > '0' && *field <= '9')
		{
			node = (t_epath *)malloc(sizeof(t_epath)); // NEED PROTECT
			node->index = atoi(field); // NEED ft_atoi()
			node->crd_x = (counter % 16) + 0.5; // 16 is map->width
			node->crd_y = (counter / 16) + 0.5; // 16 is map->width
			node->next = NULL;
			
			if (!epath)
				epath = node;
			else
			{
				cursor = epath;
				if (node->index < cursor->index)
				{
					node->next = cursor;
					epath = node;
				}
				else
				{
					while(cursor->next && node->index > cursor->next->index)
						cursor = cursor->next;
					if (!cursor->next)
						cursor->next = node;
					else
					{
						node->next = cursor->next;
						cursor->next = node;
					}
					
				}
				
			}
			
		}
		field += 1;
		counter += 1;
	}
	cursor = epath;
	while (cursor->next)
	{
		cursor->normal = atan2(cursor->next->crd_x - cursor->crd_x, cursor->next->crd_y - cursor->crd_y);
		if (cursor->normal < 0)
			cursor->normal += 2 * M_PI;

		cursor = cursor->next;
	}
	

	return (epath);
}

void	print_epath(t_epath	*epath)
{
	while (epath)
	{
		printf("%d\n", epath->index);
		epath = epath->next;
	}
	
}








void	set_enemies(t_enemy *enemies, t_player *player)
{
	while (enemies)
	{
		enemies->p_div = enemies->normal - player->angle;
		if (enemies->p_div < -180 * M_PI / 180)
			enemies->p_div = 360 * M_PI / 180 + enemies->p_div;
		if (enemies->p_div > 180 * M_PI / 180)
			enemies->p_div = -360 * M_PI / 180 + enemies->p_div;

		if (fabs(enemies->p_div) >= 157.5 * M_PI / 180)
			enemies->tile = enemies->shift_tile;
		if (fabs(enemies->p_div) >= 112.5 * M_PI / 180 && fabs(enemies->p_div) < 157.5 * M_PI / 180)
			enemies->tile = enemies->shift_tile + 1;
		if (fabs(enemies->p_div) >= 67.5 * M_PI / 180 && fabs(enemies->p_div) < 112.5 * M_PI / 180)
			enemies->tile = enemies->shift_tile + 2;
		if (fabs(enemies->p_div) >= 22.5 * M_PI / 180 && fabs(enemies->p_div) < 67.5 * M_PI / 180)
			enemies->tile = enemies->shift_tile + 3;
		if (fabs(enemies->p_div) < 22.5 * M_PI / 180)
			enemies->tile = enemies->shift_tile + 4;
	
		enemies->p_dir = atan2(enemies->pos_x - player->pos_x, enemies->pos_y - player->pos_y);
		if (enemies->p_dir - player->angle > M_PI)
			enemies->p_dir -= 2 * M_PI; 
		if (enemies->p_dir - player->angle < -M_PI)
			enemies->p_dir += 2 * M_PI;
		enemies->p_dir -= player->angle;
		enemies->shift_x = WIDTH / 2 - (enemies->p_dir * (WIDTH) / (player->fov));
		
		enemies->dist = sqrt(pow(enemies->pos_x - player->pos_x, 2) + pow(enemies->pos_y - player->pos_y, 2));
		enemies->size = (int)(HEIGHT * 2 / enemies->dist);
		enemies->h_offset = enemies->shift_x - enemies->size / 2;
		enemies->v_offset = HEIGHT / 2 - enemies->size / 2;
		
		enemies = enemies->next;
	}
}

void	set_patrol(t_enemy *enemies, t_player *player)
{
	static long	time = 0;
	static char	phase = 0;
	static char	reverse = 0;


	if (time % 50 == 0)
	{
		if (enemies->pos_y < 10 || enemies->pos_y > 16 - 2)
		{
			reverse ^= 1;
			enemies->normal = reverse == 0 ? 180 * M_PI / 180 : 0;
		}
			
		if (phase == 0)
			enemies->shift_tile = enemies->main_tile + 8;
		if (phase == 1)
			enemies->shift_tile = enemies->main_tile + 16;
		if (phase == 2)
			enemies->shift_tile = enemies->main_tile + 24;
		if (phase == 3)
			enemies->shift_tile = enemies->main_tile + 32;
		
		if (!reverse)
			enemies->pos_y -= 0.1;
		else
			enemies->pos_y += 0.1;
		set_enemies(enemies, player);
		phase += 1;
		if (phase == 4)
			phase = 0;
		
	}
	time += 1;
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
			draw_vertlenemy(enemies, pixel, img, z_buff, cursor_x, player);
			cursor_x += 1;
		}
		enemies = enemies->next;
	}
}

void	draw_vertlenemy(t_enemy *enemies, int *pixel, int *img, double *z_buff, int cursor_x, t_player *player)
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

		if (enemies->p_div < 0 * M_PI / 180 && enemies->tile != enemies->shift_tile && enemies->tile != enemies->shift_tile + 4)
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
