/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_quads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:42:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/04 13:39:27 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	calc_firstquad(t_map *map, t_player *player, t_drawer *drawer)
{
	int		i;

	i = 0;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[0][0] = (int)(player->pos_x + i);
		drawer->barrier_f[0][1] = player->pos_y +
			(drawer->barrier_f[0][0] - player->pos_x) / drawer->ray_tan[0];
		drawer->barrier_d[0] = (int)drawer->barrier_f[0][0];
		drawer->barrier_d[1] = (int)drawer->barrier_f[0][1];
		if (check_barrier(map, player, drawer))
			break ;
	}
	i = 0;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[1][1] = (int)(player->pos_y + i);
		drawer->barrier_f[1][0] = player->pos_x +
			(drawer->barrier_f[1][1] - player->pos_y) * drawer->ray_tan[0];
		drawer->barrier_d[0] = (int)drawer->barrier_f[1][0];
		drawer->barrier_d[1] = (int)drawer->barrier_f[1][1];
		if (check_barrier(map, player, drawer))
			break ;
	}
	def_barrierparam(player, drawer, 0b1);
}

void	calc_secondquad(t_map *map, t_player *player, t_drawer *drawer)
{
	int		i;

	i = 0;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[0][0] = (int)(player->pos_x + i);
		drawer->barrier_f[0][1] = player->pos_y -
			(drawer->barrier_f[0][0] - player->pos_x) * drawer->ray_tan[1];
		drawer->barrier_d[0] = (int)drawer->barrier_f[0][0];
		drawer->barrier_d[1] = (int)drawer->barrier_f[0][1];
		if (check_barrier(map, player, drawer))
			break ;
	}
	i = -1;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[1][1] = (int)(player->pos_y) - i;
		drawer->barrier_f[1][0] = player->pos_x +
			(player->pos_y - drawer->barrier_f[1][1]) / drawer->ray_tan[1];
		drawer->barrier_d[0] = (int)drawer->barrier_f[1][0];
		drawer->barrier_d[1] = (int)drawer->barrier_f[1][1] - 1;
		if (check_barrier(map, player, drawer))
			break ;
	}
	def_barrierparam(player, drawer, 0b10);
}

void	calc_thirdquad(t_map *map, t_player *player, t_drawer *drawer)
{
	int		i;

	i = -1;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[0][0] = (int)(player->pos_x) - i;
		drawer->barrier_f[0][1] = player->pos_y -
			(player->pos_x - drawer->barrier_f[0][0]) / drawer->ray_tan[0];
		drawer->barrier_d[0] = (int)drawer->barrier_f[0][0] - 1;
		drawer->barrier_d[1] = (int)drawer->barrier_f[0][1];
		if (check_barrier(map, player, drawer))
			break ;
	}
	i = -1;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[1][1] = (int)(player->pos_y) - i;
		drawer->barrier_f[1][0] = player->pos_x -
			(player->pos_y - drawer->barrier_f[1][1]) * drawer->ray_tan[0];
		drawer->barrier_d[0] = (int)drawer->barrier_f[1][0];
		drawer->barrier_d[1] = (int)drawer->barrier_f[1][1] - 1;
		if (check_barrier(map, player, drawer))
			break ;
	}
	def_barrierparam(player, drawer, 0b100);
}

void	calc_fourthquad(t_map *map, t_player *player, t_drawer *drawer)
{
	int		i;

	i = -1;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[0][0] = (int)(player->pos_x) - i;
		drawer->barrier_f[0][1] = player->pos_y +
			(player->pos_x - drawer->barrier_f[0][0]) * drawer->ray_tan[1];
		drawer->barrier_d[0] = (int)drawer->barrier_f[0][0] - 1;
		drawer->barrier_d[1] = (int)drawer->barrier_f[0][1];
		if (check_barrier(map, player, drawer))
			break ;
	}
	i = 0;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[1][1] = (int)(player->pos_y + i);
		drawer->barrier_f[1][0] = player->pos_x -
			(drawer->barrier_f[1][1] - player->pos_y) / drawer->ray_tan[1];
		drawer->barrier_d[0] = (int)drawer->barrier_f[1][0];
		drawer->barrier_d[1] = (int)drawer->barrier_f[1][1];
		if (check_barrier(map, player, drawer))
			break ;
	}
	def_barrierparam(player, drawer, 0b1000);
}
