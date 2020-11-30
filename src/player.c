/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 12:57:03 by jthuy             #+#    #+#             */
/*   Updated: 2020/11/30 13:01:39 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_player	*def_player(t_map *map)
{
	t_player	*player;
	char		*player_searcher;
	int			pos_player;

	if (!(player = (t_player *)malloc(sizeof(t_player))))
		return (NULL);
	pos_player = map->width + 1;
	player_searcher = map->field;
	while (player_searcher[pos_player] != 'P')
		pos_player += 1;
	player->pos_x = pos_player % map->width;
	player->pos_y = pos_player / map->width;
	player->angle = PLAYER_ANGLE * M_PI / 180;
	player->ray_depth = 30;
	player->fov = 90 * M_PI / 180;
	player->health = 100;
	
	player->condition = 0;

	player->shoot = 0;
	
	player->bitweapons = 0b1;
	player->weapon = 1;
	player->main_tile = 527;
	// player->phase = 0;
	return (player);
}

void	set_pcondition(t_player *player, t_enemy *enemies)
{
	if (!player->condition)
	{
		set_stay(player);
		return ;
	}
	if (player->condition == 0b1)
	{
		set_pshoot(player, enemies);
		return ;
	}
}

void	set_stay(t_player *player)
{
	player->tile = player->main_tile;
}

void	set_pshoot(t_player *player, t_enemy *enemies)
{
	player->tile = player->main_tile + player->phase;
	player->phase += 1;

	if (player->phase == 3)
	{
		while (enemies)
		{
			if (enemies->health > 0 && abs(WIDTH / 2 - enemies->shift_x) < enemies->size / 2)
			{
				// enemies->health -= 20;
				// if (enemies->health < 0)
				// 	enemies->health = 0;
				// enemies->shift_tile = enemies->main_tile + 40;
				// enemies->phase = 0;
				// enemies->punch = 1;
				enemies->condition = 0b10;
			}
			enemies = enemies->next;
		}
		return ;
	}

	if (player->phase > 4 && player->shoot)
	{
		player->phase = 2;
		// player->phase += 1;
		return ;
	}


	if (player->phase > 4)
	{
		player->condition = 0;
		player->phase = 0;
	}
}

void	shoot_player(t_player *player, t_enemy *enemies)
{
	// if (player->armweapon == 1)
	// 	player->tile_weapon = 527;
	// player->tile = player->tile_weapon;
	// player->phase += 1;

	if (player->condition != 0b1)
	{
		player->condition = 0b1;
		player->phase = 1;
	}
	// player->condition = 0b1;
	// player->phase = 1;
	
	// while (enemies)
	// {
		
	// 	if (enemies->health > 0 && abs(WIDTH / 2 - enemies->shift_x) < enemies->size / 2)
	// 	{
	// 		// enemies->health -= 20;
	// 		// if (enemies->health < 0)
	// 		// 	enemies->health = 0;
	// 		// enemies->shift_tile = enemies->main_tile + 40;
	// 		// enemies->phase = 0;
	// 		// enemies->punch = 1;
	// 		enemies->condition = 0b10;
	// 	}
	// 	enemies = enemies->next;
	// }
	
}