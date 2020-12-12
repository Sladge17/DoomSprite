/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:04:46 by jthuy             #+#    #+#             */
/*   Updated: 2020/12/12 15:01:19 by jthuy            ###   ########.fr       */
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
			node->sprite = (t_sprite *)malloc(sizeof(t_sprite)); // NEED PROTECT
			node->sprite->pos_x = index % map->width;
			node->sprite->pos_y = index / map->width;
			node->sprite->main_tile = 133;
			node->sprite->tile = node->sprite->main_tile;
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
			node->sprite = (t_sprite *)malloc(sizeof(t_sprite)); // NEED PROTECT
			node->sprite->pos_x = index % map->width;
			node->sprite->pos_y = index / map->width;
			node->sprite->main_tile = 134;
			node->sprite->tile = node->sprite->main_tile;
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
		set_spriteparam(props->sprite, player);
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
		props = props->next;
	}
}

void	draw_props(t_props *props, SDL_Surface *surface, int *img, double *z_buff)
{
	while (props)
	{
		draw_sprites(props->sprite, surface, img, z_buff, 0);
		props = props->next;
	}
}