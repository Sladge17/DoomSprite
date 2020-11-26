/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:57:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/11/26 13:51:20 by jthuy            ###   ########.fr       */
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

#define ELIMIT 2

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
		
		node->start = node->path;
		node->end = node->start->next;
		node->pos_x = node->start->crd_x;
		node->pos_y = node->start->crd_y;
		node->normal = node->start->normal; // AVALUABLE VALUES: 0, 45, 90, 135, 180, 225, 270, 315
		node->main_tile = 156;
		node->health = 100;
		node->condition = 0b1;
		node->phase = 0;
		
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
				"...2..1........."\
				"................"\
				"...3..4........."\
				"................"\
				"................";
	if (ecounter == 1)
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
				".......2..3....."\
				"................"\
				".......1..4....."\
				"................"\
				"................";
		
	// if (!ecounter)
	// 	field =	"................"\
	// 			"................"\
	// 			"................"\
	// 			"................"\
	// 			"................"\
	// 			"................"\
	// 			"................"\
	// 			"................"\
	// 			"................"\
	// 			"................"\
	// 			"................"\
	// 			"................"\
	// 			".......2........"\
	// 			".......1........"\
	// 			"................"\
	// 			"................";

	
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
	cursor->normal = atan2(epath->crd_x - cursor->crd_x, epath->crd_y - cursor->crd_y);

	return (epath);
}

void	set_sequence(t_enemy *enemies, t_player *player)
{
	while (enemies)
	{
		if (enemies->condition == 0b1)
		{
			set_walk(enemies, player);
			enemies = enemies->next;
			continue ;
		}
		enemies = enemies->next;
	}
	
}

void	set_walk(t_enemy *enemies, t_player *player)
{
	set_position(enemies);
	set_rotation(enemies, player);
	set_walkphase(enemies);
	set_spriteparam(enemies, player);
}

void	set_position(t_enemy *enemies)
{
	int		increment;
	
	if (fabs(enemies->pos_x - enemies->end->crd_x) > 0.1 || fabs(enemies->pos_y - enemies->end->crd_y) > 0.1)
	{
		if (fabs(enemies->pos_x - enemies->end->crd_x) > 0.1)
		{
			increment = enemies->end->crd_x - enemies->start->crd_x > 0 ? 1 : -1;
			enemies->pos_x = enemies->pos_x + 0.1 * increment;
		}
		if (fabs(enemies->pos_y - enemies->end->crd_y) > 0.1)
		{
			increment = enemies->end->crd_y - enemies->start->crd_y > 0 ? 1 : -1;
			enemies->pos_y = enemies->pos_y + 0.1 * increment;
		}
		return ;
	}
	if (!enemies->end->next)
	{
		enemies->start = enemies->end;
		enemies->end = enemies->path;
		enemies->pos_x = enemies->start->crd_x;
		enemies->pos_y = enemies->start->crd_y;
		enemies->normal = enemies->start->normal;
		return ;
	}
	enemies->start = enemies->end;
	enemies->end = enemies->start->next;
	enemies->pos_x = enemies->start->crd_x;
	enemies->pos_y = enemies->start->crd_y;
	enemies->normal = enemies->start->normal;
}

void	set_rotation(t_enemy *enemies, t_player *player)
{
	enemies->p_div = enemies->normal - player->angle;
	if (enemies->p_div < -180 * M_PI / 180)
		enemies->p_div = 360 * M_PI / 180 + enemies->p_div;
	else if (enemies->p_div > 180 * M_PI / 180)
		enemies->p_div = -360 * M_PI / 180 + enemies->p_div;

	if (fabs(enemies->p_div) >= 157.5 * M_PI / 180)
	{
		enemies->shift_tile = enemies->main_tile;
		return ;
	}
	if (fabs(enemies->p_div) < 22.5 * M_PI / 180)
	{
		enemies->shift_tile = enemies->main_tile + 4;
		return ;
	}
	if (fabs(enemies->p_div) >= 112.5 * M_PI / 180 && fabs(enemies->p_div) < 157.5 * M_PI / 180)
	{
		enemies->shift_tile = enemies->main_tile + 1;
		return ;
	}
	if (fabs(enemies->p_div) >= 67.5 * M_PI / 180 && fabs(enemies->p_div) < 112.5 * M_PI / 180)
	{
		enemies->shift_tile = enemies->main_tile + 2;
		return ;
	}
	enemies->shift_tile = enemies->main_tile + 3;
}

void	set_walkphase(t_enemy *enemies)
{
	if (enemies->phase == 0)
		enemies->tile = enemies->shift_tile + 8;
	else if (enemies->phase == 1)
		enemies->tile = enemies->shift_tile + 16;
	else if (enemies->phase == 2)
		enemies->tile = enemies->shift_tile + 24;
	else // enemies->phase == 3
		enemies->tile = enemies->shift_tile + 32;
	enemies->phase += 1;
	if (enemies->phase == 4)
		enemies->phase = 0;
}

void	set_spritesparam(t_enemy *enemies, t_player *player)
{
	while (enemies)
	{
		set_spriteparam(enemies, player);
		enemies = enemies->next;
	}
}

void	set_spriteparam(t_enemy *enemies, t_player *player)
{
	enemies->p_dir = atan2(enemies->pos_x - player->pos_x, enemies->pos_y - player->pos_y);
	if (enemies->p_dir - player->angle > M_PI)
		enemies->p_dir -= 2 * M_PI; 
	else if (enemies->p_dir - player->angle < -M_PI)
		enemies->p_dir += 2 * M_PI;
	enemies->p_dir -= player->angle;
	enemies->shift_x = WIDTH / 2 - (enemies->p_dir * (WIDTH) / (player->fov));
	
	enemies->dist = sqrt(pow(enemies->pos_x - player->pos_x, 2) + pow(enemies->pos_y - player->pos_y, 2));
	enemies->size = (int)(HEIGHT * 2 / enemies->dist);
	enemies->h_offset = enemies->shift_x - enemies->size / 2;
	enemies->v_offset = HEIGHT / 2 - enemies->size / 2;
}


void	set_enemies(t_enemy *enemies, t_player *player)
{

	if (enemies->health && !enemies->punch
		&& fabs(enemies->hfov) >= 5 * M_PI / 180 && enemies->dist >= 5)
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
	}
	else
	{
		enemies->tile = enemies->shift_tile;
		// enemies->tile = enemies->main_tile + 40;
	}
	

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

	// enemies->punch = 0;
}

void	set_enemies2(t_enemy *enemies, t_player *player)
{
	while (enemies)
	{
		if (enemies->health && !enemies->punch)
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
		}
		else
		{
			enemies->tile = enemies->shift_tile;
		}
		
	
		enemies->p_dir = atan2(enemies->pos_x - player->pos_x, enemies->pos_y - player->pos_y);

		enemies->hfov = enemies->p_dir + M_PI - enemies->normal;
		if (enemies->hfov > M_PI)
			enemies->hfov -= 2 * M_PI;

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

		enemies->punch = 0;
		
		enemies = enemies->next;
	}
}

// void	set_patrol(t_enemy *enemies, t_player *player)
// {
// 	static long	time = 0;
// 	// static char	phase = 0;
// 	// t_enemy		*cursor;

// 	int			dir;


// 	if (time % 50 == 0)
// 	{
// 		// printf ("%f %f\n", enemies->pos_x, enemies->end->crd_x);
// 		// if (enemies->pos_x != enemies->end->crd_x)
		
// 		while (enemies)
// 		{
// 			if (!enemies->health)
// 			{
// 				kill_enemies(player, enemies);
// 				set_enemies(enemies, player);
// 				enemies = enemies->next;
// 				continue ;
// 			}

// 			if (fabs(enemies->hfov) < 5 * M_PI / 180 && enemies->dist < 5)
// 			{
// 				static int	phase = 46;
// 				// enemies->phase = 0;
// 				enemies->shift_tile = enemies->main_tile + phase;
// 				set_enemies(enemies, player);
// 				phase += 1;
// 				if (phase > 48)
// 					phase = 47;
// 				enemies = enemies->next;
// 				continue ;
// 			}

// 			// printf("%f\n", enemies->p_dir * 180 / M_PI);
// 			// printf("%f\n", enemies->p_div);
// 			// if (fabs(enemies->p_dir) <= 5 * M_PI / 180 && enemies->p_div > 0)
// 			// {
// 			// 	enemies->shift_tile = 204;
// 			// 	set_enemies(enemies, player);
// 			// 	enemies = enemies->next;
// 			// 	continue ;
// 			// }
			
// 			if (fabs(enemies->pos_x - enemies->end->crd_x) > 0.1 || fabs(enemies->pos_y - enemies->end->crd_y) > 0.1)
// 			{
// 				if (fabs(enemies->pos_x - enemies->end->crd_x) > 0.1)
// 				{
// 					dir = enemies->end->crd_x - enemies->start->crd_x > 0 ? 1 : -1;
// 					enemies->pos_x = enemies->pos_x + 0.1 * dir;
// 				}
// 				if (fabs(enemies->pos_y - enemies->end->crd_y) > 0.1)
// 				{
// 					dir = enemies->end->crd_y - enemies->start->crd_y > 0 ? 1 : -1;
// 					enemies->pos_y = enemies->pos_y + 0.1 * dir;
// 				}
// 			}
// 			else
// 			{
// 				if (!enemies->end->next)
// 				{
// 					enemies->start = enemies->end;
// 					enemies->end = enemies->path;
// 					enemies->pos_x = enemies->start->crd_x;
// 					enemies->pos_y = enemies->start->crd_y;
// 					enemies->normal = enemies->start->normal;
// 				}
// 				else
// 				{
// 					enemies->start = enemies->end;
// 					enemies->end = enemies->start->next;
// 					enemies->pos_x = enemies->start->crd_x;
// 					enemies->pos_y = enemies->start->crd_y;
// 					enemies->normal = enemies->start->normal;
// 				}
// 			}
			

// 			// if (enemies->punch)
// 			// {
// 			// 	set_enemies(enemies, player);
// 			// 	enemies->punch = 0;
// 			// }
// 			// else
// 			// {
// 			// 	if (enemies->phase == 0)
// 			// 		enemies->shift_tile = enemies->main_tile + 8;
// 			// 	if (enemies->phase == 1)
// 			// 		enemies->shift_tile = enemies->main_tile + 16;
// 			// 	if (enemies->phase == 2)
// 			// 		enemies->shift_tile = enemies->main_tile + 24;
// 			// 	if (enemies->phase == 3)
// 			// 		enemies->shift_tile = enemies->main_tile + 32;
				
// 			// 	// enemies->pos_y -= 0.1;
// 			// 	set_enemies(enemies, player);
// 			// 	enemies->phase += 1;
// 			// 	if (enemies->phase == 4)
// 			// 		enemies->phase = 0;
// 			// }

// 		if (enemies->phase == 0)
// 			enemies->shift_tile = enemies->main_tile + 8;
// 		if (enemies->phase == 1)
// 			enemies->shift_tile = enemies->main_tile + 16;
// 		if (enemies->phase == 2)
// 			enemies->shift_tile = enemies->main_tile + 24;
// 		if (enemies->phase == 3)
// 			enemies->shift_tile = enemies->main_tile + 32;
// 		set_enemies(enemies, player);
// 		enemies->phase += 1;
// 		if (enemies->phase == 4)
// 			enemies->phase = 0;

// 		enemies = enemies->next;
// 		}
// 	}
// 	time += 1;
// }


void	set_patrol(t_enemy *enemies, t_player *player)
{
	static long	time = 0;

	if (time % 50 == 0)
	{
		set_sequence(enemies, player);
	}
	time += 1;
}

void	kill_enemies(t_player *player, t_enemy *enemies)
{
	if (enemies->phase < 3)
	{
		enemies->shift_tile += 1;
		enemies->phase += 1;
	}
	else
		enemies->shift_tile = 201;
		
	// printf("%d\n", );
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

		//WITH ALPHA
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

void	shooting(t_enemy *enemies)
{
	while (enemies)
	{
		if (enemies->health && abs(WIDTH / 2 - enemies->shift_x) < enemies->size / 2)
		{
			enemies->health -= 20;
			if (enemies->health < 0)
				enemies->health = 0;
			enemies->shift_tile = enemies->main_tile + 40;
			enemies->phase = 0;
			enemies->punch = 1;
		}
		enemies = enemies->next;
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

// TMP FUNC
void	print_epath(t_enemy *enemies)
{
	t_enemy	*cursor;
	t_epath	*epath;

	cursor = enemies;
	while(cursor)
	{
		epath = cursor->path;
		while (epath)
		{
			printf("%f\n", epath->normal * 180 / M_PI);
			epath = epath->next;
		}
		cursor = cursor->next;
	}
}
