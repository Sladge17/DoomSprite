/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:57:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/12/12 19:54:41 by jthuy            ###   ########.fr       */
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
		node->start = node->path;
		node->end = node->start->next;

		node->sprite = (t_sprite *)malloc(sizeof(t_sprite)); // NEED PROTECT
		node->sprite->pos_x = node->start->crd_x;
		node->sprite->pos_y = node->start->crd_y;
		node->sprite->main_tile = 156;
		
		node->normal = node->start->normal; // AVALUABLE VALUES: 0, 45, 90, 135, 180, 225, 270, 315
		node->health = 100;
		node->condition = 0b1;
		node->phase = 0; //maybe not need
		
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
				"...3..2........."\
				"................"\
				"...4..1........."\
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

void	set_econdition(t_enemy *enemies, t_player *player)
{
	while (enemies)
	{
		if (enemies->condition == 0b1000)
		{
			set_eshoot(enemies, player);
			enemies = enemies->next;
			continue ;
		}
		if (enemies->condition == 0b100)
		{
			set_edetect(enemies, player);
			enemies = enemies->next;
			continue ;
		}
		if (!enemies->condition)
		{
			set_edead(enemies, player);
			enemies = enemies->next;
			continue ;
		}
		if (enemies->condition == 0b10)
		{
			set_epunch(enemies, player);
			enemies = enemies->next;
			continue ;
		}
		if (enemies->condition == 0b1)
		{
			set_ewalk(enemies, player);
			enemies = enemies->next;
			continue ;
		}
		enemies = enemies->next;
	}
}

void	set_eshoot(t_enemy *enemies, t_player *player)
{
	enemies->shift_tile = enemies->sprite->main_tile + 47;
	if (enemies->phase == 1 || enemies->phase == 0 || enemies->phase == 2)
		enemies->sprite->tile = enemies->shift_tile;
	if (enemies->phase == 3)
		enemies->sprite->tile = enemies->shift_tile + 1;
	// if (fabs(enemies->hfov) < (45 / 2) * M_PI / 180 && enemies->dist < 5)
	if (enemies->sprite->dist < 8)
	{
		///
		enemies->normal = atan2(enemies->sprite->p_dirx, enemies->sprite->p_diry);
		if (enemies->normal < 0)
			enemies->normal += M_PI;
		///
		// enemies->phase ^= 1;
		enemies->phase += 1;
		if (enemies->phase == 4)
			enemies->phase = 0;
		if (enemies->phase == 0) // MAYBEE NEEED enemies->phase == 1
			player->health -= 10;
		enemies->condition = 0b1000;
		return ;
	}
	enemies->normal = enemies->start->normal;
	enemies->phase = 0;
	enemies->condition = 0b1;
}

void	set_edetect(t_enemy *enemies, t_player *player)
{
	enemies->sprite->tile = enemies->sprite->main_tile + 46;
	enemies->phase = 0;
	if (fabs(enemies->hfov) < (45 / 2) * M_PI / 180 && enemies->sprite->dist < 5)
	{
		enemies->condition = 0b1000;
		return ;
	}
	enemies->condition = 0b1;
}

void	set_edead(t_enemy *enemies, t_player *player)
{
	if (enemies->phase == 3)
	{
		enemies->sprite->tile = enemies->sprite->main_tile + 45;
		return ;
	}
	enemies->shift_tile = enemies->sprite->main_tile + 41;
	enemies->sprite->tile = enemies->shift_tile + enemies->phase;
	enemies->phase += 1;
}

void	set_epunch(t_enemy *enemies, t_player *player)
{
	enemies->sprite->tile = enemies->sprite->main_tile + 40;
	enemies->health -= 40;
	// printf("%d\n", enemies->health);
	if (enemies->health <= 0)
	{
		enemies->condition = 0;
		enemies->phase = 0;
		return ;
	}
	// enemies->condition = 0b1;
	/// NEED CHECK
	enemies->normal = atan2(enemies->sprite->p_dirx, enemies->sprite->p_diry);
	if (enemies->normal < 0)
		enemies->normal += M_PI;
	/// ///
	enemies->condition = 0b1000;
	enemies->phase = 0;
}

void	set_ewalk(t_enemy *enemies, t_player *player)
{
	set_eposition(enemies);
	set_erotation(enemies, player);
	set_ewalkphase(enemies);
	set_spriteparam(enemies->sprite, player);

	enemies->hfov = atan2(enemies->sprite->p_dirx, enemies->sprite->p_diry) + M_PI - enemies->normal;
	if (enemies->hfov > M_PI)
		enemies->hfov -= 2 * M_PI;
	
	if (fabs(enemies->hfov) < (45 / 2) * M_PI / 180 && enemies->sprite->dist < 5)
		enemies->condition = 0b100;
}

void	set_eposition(t_enemy *enemies)
{
	int		increment;
	
	if (fabs(enemies->sprite->pos_x - enemies->end->crd_x) > 0.1 || fabs(enemies->sprite->pos_y - enemies->end->crd_y) > 0.1)
	{
		if (fabs(enemies->sprite->pos_x - enemies->end->crd_x) > 0.1)
		{
			increment = enemies->end->crd_x - enemies->start->crd_x > 0 ? 1 : -1;
			enemies->sprite->pos_x = enemies->sprite->pos_x + 0.1 * increment;
		}
		if (fabs(enemies->sprite->pos_y - enemies->end->crd_y) > 0.1)
		{
			increment = enemies->end->crd_y - enemies->start->crd_y > 0 ? 1 : -1;
			enemies->sprite->pos_y = enemies->sprite->pos_y + 0.1 * increment;
		}
		return ;
	}
	if (!enemies->end->next)
	{
		enemies->start = enemies->end;
		enemies->end = enemies->path;
		enemies->sprite->pos_x = enemies->start->crd_x;
		enemies->sprite->pos_y = enemies->start->crd_y;
		enemies->normal = enemies->start->normal;
		return ;
	}
	enemies->start = enemies->end;
	enemies->end = enemies->start->next;
	enemies->sprite->pos_x = enemies->start->crd_x;
	enemies->sprite->pos_y = enemies->start->crd_y;
	enemies->normal = enemies->start->normal;
}

void	set_erotation(t_enemy *enemies, t_player *player)
{
	enemies->p_div = enemies->normal - player->angle;
	if (enemies->p_div < -180 * M_PI / 180)
		enemies->p_div = 360 * M_PI / 180 + enemies->p_div;
	else if (enemies->p_div > 180 * M_PI / 180)
		enemies->p_div = -360 * M_PI / 180 + enemies->p_div;

	if (fabs(enemies->p_div) >= 157.5 * M_PI / 180)
	{
		enemies->shift_tile = enemies->sprite->main_tile;
		return ;
	}
	if (fabs(enemies->p_div) < 22.5 * M_PI / 180)
	{
		enemies->shift_tile = enemies->sprite->main_tile + 4;
		return ;
	}
	if (fabs(enemies->p_div) >= 112.5 * M_PI / 180 && fabs(enemies->p_div) < 157.5 * M_PI / 180)
	{
		enemies->shift_tile = enemies->sprite->main_tile + 1;
		return ;
	}
	if (fabs(enemies->p_div) >= 67.5 * M_PI / 180 && fabs(enemies->p_div) < 112.5 * M_PI / 180)
	{
		enemies->shift_tile = enemies->sprite->main_tile + 2;
		return ;
	}
	enemies->shift_tile = enemies->sprite->main_tile + 3;
}

void	set_ewalkphase(t_enemy *enemies)
{
	if (enemies->phase == 0)
		enemies->sprite->tile = enemies->shift_tile + 8;
	else if (enemies->phase == 1)
		enemies->sprite->tile = enemies->shift_tile + 16;
	else if (enemies->phase == 2)
		enemies->sprite->tile = enemies->shift_tile + 24;
	else // enemies->phase == 3
		enemies->sprite->tile = enemies->shift_tile + 32;
	enemies->phase += 1;
	if (enemies->phase == 4)
		enemies->phase = 0;
}

void	set_enemiesparam(t_enemy *enemies, t_player *player)
{
	while (enemies)
	{
		set_spriteparam(enemies->sprite, player);
		// set_erotation(enemies, player);
		
		// NEED OPIMIZE
		// enemies->hfov = atan2(enemies->sprite->p_dirx, enemies->sprite->p_diry) + M_PI - enemies->normal;
		// if (enemies->hfov > M_PI)
		// 	enemies->hfov -= 2 * M_PI;
		// if (fabs(enemies->hfov) < (45 / 2) * M_PI / 180 && enemies->sprite->dist < 5)
		// enemies->condition = 0b100;
		// set_econdition(enemies, player);
		
		
		// if (enemies->condition == 0b01)
		// 	enemies->condition = 0b1;
		enemies = enemies->next;
	}
}

void	set_spriteparam(t_sprite *sprite, t_player *player)
{
	sprite->p_dirx = sprite->pos_x - player->pos_x;
	sprite->p_diry = sprite->pos_y - player->pos_y;
	sprite->p_dir = atan2(sprite->p_dirx, sprite->p_diry);
	if (sprite->p_dir - player->angle > M_PI)
		sprite->p_dir -= 2 * M_PI; 
	else if (sprite->p_dir - player->angle < -M_PI)
		sprite->p_dir += 2 * M_PI;
	sprite->p_dir -= player->angle;
	
	// // NEED OPIMIZE
	// enemies->hfov = atan2(enemies->sprite->p_dirx, enemies->sprite->p_diry) + M_PI - enemies->normal;
	// if (enemies->hfov > M_PI)
	// 	enemies->hfov -= 2 * M_PI;

	sprite->shift_x = WIDTH / 2 - (sprite->p_dir * (WIDTH) / (player->fov));
	
	sprite->dist = sqrt(pow(sprite->p_dirx, 2) + pow(sprite->p_diry, 2));
	sprite->size = (int)(HEIGHT * 2 / sprite->dist);
	sprite->h_offset = sprite->shift_x - sprite->size / 2;
	sprite->v_offset = HEIGHT / 2 - sprite->size / 2;
}

// void	draw_enemies(t_player *player, t_enemy *enemies, int *pixel, int *img, double *z_buff)
// {
// 	int		cursor_x;
	
// 	while (enemies)
// 	{
// 		cursor_x = 0;
// 		while (cursor_x < enemies->sprite->size)
// 		{
// 			if (enemies->sprite->h_offset + cursor_x < 0 || enemies->sprite->h_offset + cursor_x >= WIDTH)
// 			{
// 				cursor_x += 1;
// 				continue;
// 			}
// 			draw_vertlenemy(enemies, pixel, img, z_buff, cursor_x, player);
// 			cursor_x += 1;
// 		}
// 		enemies = enemies->next;
// 	}
// }

// void	draw_vertlenemy(t_enemy *enemies, int *pixel, int *img, double *z_buff, int cursor_x, t_player *player)
// {
// 	int		tile_u;
// 	int		tile_v;
// 	int		cursor_y;

// 	tile_u = enemies->sprite->tile % 16;
// 	tile_v = enemies->sprite->tile / 16;
// 	cursor_y = 0;
// 	while (cursor_y < enemies->sprite->size)
// 	{
// 		if (enemies->sprite->v_offset + cursor_y < 0 || enemies->sprite->v_offset + cursor_y >= HEIGHT)
// 		{
// 			cursor_y += 1;
// 			continue;
// 		}

// 		// //WITH ALPHA
// 		// if (enemies->p_div < 0 * M_PI / 180 && enemies->shift_tile != enemies->main_tile && enemies->shift_tile != enemies->main_tile + 4)
// 		// {
// 		// 	if (img[(int)(64 * ((enemies->size - cursor_x - 1) / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFF980088 &&
// 		// 		enemies->dist < z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)])
// 		// 	{
// 		// 		pixel[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = img[(int)(64 * ((enemies->size - cursor_x - 1) / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65];
// 		// 		z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = enemies->dist;
// 		// 	}
// 		// }
// 		// else
// 		// {
// 		// 	if (img[(int)(64 * (cursor_x / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFF980088 &&
// 		// 		enemies->dist < z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)])
// 		// 	{
// 		// 		pixel[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = img[(int)(64 * (cursor_x / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65];
// 		// 		z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = enemies->dist;
// 		// 	}
// 		// }	
		
// 		//WITHOUT ALPHA
// 		if (enemies->p_div < 0 * M_PI / 180 && enemies->shift_tile != enemies->sprite->main_tile && enemies->shift_tile != enemies->sprite->main_tile + 4)
// 		{
// 			if (img[(int)(64 * ((enemies->sprite->size - cursor_x - 1) / (double)enemies->sprite->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->sprite->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xffffffff &&
// 				enemies->sprite->dist < z_buff[enemies->sprite->h_offset + cursor_x + WIDTH * (enemies->sprite->v_offset + cursor_y)])
// 			{
// 				pixel[enemies->sprite->h_offset + cursor_x + WIDTH * (enemies->sprite->v_offset + cursor_y)] = img[(int)(64 * ((enemies->sprite->size - cursor_x - 1) / (double)enemies->sprite->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->sprite->size)) + tile_u * 65 + tile_v * 1039 * 65];
// 				z_buff[enemies->sprite->h_offset + cursor_x + WIDTH * (enemies->sprite->v_offset + cursor_y)] = enemies->sprite->dist;
// 			}
// 		}
// 		else
// 		{
// 			if (img[(int)(64 * (cursor_x / (double)enemies->sprite->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->sprite->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFFffffff &&
// 				enemies->sprite->dist < z_buff[enemies->sprite->h_offset + cursor_x + WIDTH * (enemies->sprite->v_offset + cursor_y)])
// 			{
// 				pixel[enemies->sprite->h_offset + cursor_x + WIDTH * (enemies->sprite->v_offset + cursor_y)] = img[(int)(64 * (cursor_x / (double)enemies->sprite->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->sprite->size)) + tile_u * 65 + tile_v * 1039 * 65];
// 				z_buff[enemies->sprite->h_offset + cursor_x + WIDTH * (enemies->sprite->v_offset + cursor_y)] = enemies->sprite->dist;
// 			}
// 		}	
		
// 		// // WITHOUT ALPHA
// 		// if (enemies->p_div < 0 * M_PI / 180 && enemies->tile != enemies->shift_tile && enemies->tile != enemies->shift_tile + 4)
// 		// {
// 		// 	if (enemies->dist < z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)])
// 		// 	{
// 		// 		pixel[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = img[(int)(64 * ((enemies->size - cursor_x - 1) / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65];
// 		// 		z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = enemies->dist;
// 		// 	}
// 		// }
// 		// else
// 		// {
// 		// 	if (enemies->dist < z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)])
// 		// 	{
// 		// 		pixel[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = img[(int)(64 * (cursor_x / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65];
// 		// 		z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = enemies->dist;
// 		// 	}
// 		// }	
		
	
// 		// // ENEMY_MASK
// 		// if (enemies->p_div < 0 * M_PI / 180 && enemies->tile != enemies->shift_tile && enemies->tile != enemies->shift_tile + 4)
// 		// {
// 		// 	if (img[(int)(64 * ((enemies->size - cursor_x - 1) / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFF980088 &&
// 		// 		enemies->dist < z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)])
// 		// 	{
// 		// 		pixel[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = 0xFFFFFF;
// 		// 		z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = enemies->dist;
// 		// 	}
// 		// }
// 		// else
// 		// {
// 		// 	if (img[(int)(64 * (cursor_x / (double)enemies->size)) + 1039 * (int)(64 * (cursor_y / (double)enemies->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFF980088 &&
// 		// 		enemies->dist < z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)])
// 		// 	{
// 		// 		pixel[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = 0xFFFFFF;
// 		// 		z_buff[enemies->h_offset + cursor_x + WIDTH * (enemies->v_offset + cursor_y)] = enemies->dist;
// 		// 	}
// 		// }	
		
// 		cursor_y += 1;
// 	}
// }


void	draw_enemies(t_enemy *enemies, SDL_Surface *surface, int *img, double *z_buff)
{
	while (enemies)
	{
		if (enemies->p_div < 0 * M_PI / 180 &&
			enemies->shift_tile != enemies->sprite->main_tile &&
			enemies->shift_tile != enemies->sprite->main_tile + 4)
			draw_sprites(enemies->sprite, surface, img, z_buff, 1);
		else
			draw_sprites(enemies->sprite, surface, img, z_buff, 0);
		enemies = enemies->next;
	}
}

void	draw_sprites(t_sprite *sprite, SDL_Surface *surface, int *img, double *z_buff, char invers)
{
	int		cursor_x;
	
	cursor_x = 0;
	while (cursor_x < sprite->size)
	{
		if (sprite->h_offset + cursor_x < 0 || sprite->h_offset + cursor_x >= WIDTH)
		{
			cursor_x += 1;
			continue;
		}
		draw_vertlenemy(sprite, (int *)surface->pixels, img, z_buff, cursor_x, invers);
		cursor_x += 1;
	}
}

// alpha color 0xFF980088
void	draw_vertlenemy(t_sprite *sprite, int *pixel, int *img, double *z_buff, int cursor_x, char invers)
{
	int		tile_u;
	int		tile_v;
	int		cursor_y;

	tile_u = sprite->tile % 16;
	tile_v = sprite->tile / 16;
	cursor_y = 0;
	while (cursor_y < sprite->size)
	{
		if (sprite->v_offset + cursor_y < 0 || sprite->v_offset + cursor_y >= HEIGHT)
		{
			cursor_y += 1;
			continue;
		}
		
		//WITHOUT ALPHA
		if (invers)
		{
			if (img[(int)(64 * ((sprite->size - cursor_x - 1) / (double)sprite->size)) + 1039 * (int)(64 * (cursor_y / (double)sprite->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xffffffff &&
				sprite->dist < z_buff[sprite->h_offset + cursor_x + WIDTH * (sprite->v_offset + cursor_y)])
			{
				pixel[sprite->h_offset + cursor_x + WIDTH * (sprite->v_offset + cursor_y)] = img[(int)(64 * ((sprite->size - cursor_x - 1) / (double)sprite->size)) + 1039 * (int)(64 * (cursor_y / (double)sprite->size)) + tile_u * 65 + tile_v * 1039 * 65];
				z_buff[sprite->h_offset + cursor_x + WIDTH * (sprite->v_offset + cursor_y)] = sprite->dist;
			}
		}
		else
		{
			if (img[(int)(64 * (cursor_x / (double)sprite->size)) + 1039 * (int)(64 * (cursor_y / (double)sprite->size)) + tile_u * 65 + tile_v * 1039 * 65] != 0xFFffffff &&
				sprite->dist < z_buff[sprite->h_offset + cursor_x + WIDTH * (sprite->v_offset + cursor_y)])
			{
				pixel[sprite->h_offset + cursor_x + WIDTH * (sprite->v_offset + cursor_y)] = img[(int)(64 * (cursor_x / (double)sprite->size)) + 1039 * (int)(64 * (cursor_y / (double)sprite->size)) + tile_u * 65 + tile_v * 1039 * 65];
				z_buff[sprite->h_offset + cursor_x + WIDTH * (sprite->v_offset + cursor_y)] = sprite->dist;
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
		printf("%f, %f\n", cursor->sprite->pos_x, cursor->sprite->pos_y);
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
