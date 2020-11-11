/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 13:55:30 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/02 16:03:51 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

# define COLOR_1 0xFF
# define COLOR_2 0xFF00
# define COLOR_3 0xFF0000

double		*z_buff;

void	clear_pixel(int *pixel)
{
	int		i = 0;
	while (i < WIDTH * HEIGHT)
	{
		pixel[i] = 0;
		i += 1;
	}
}

int		main()
{
	t_map		*map;
	t_player	*player;
	t_drawer	*drawer;

	if (SDL_Init(SDL_INIT_VIDEO))
		exit(0);

	SDL_Window	*window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface	*surface = SDL_GetWindowSurface(window);
	int			*pixel = (int *)surface->pixels;
	SDL_Surface	*athlas = IMG_Load("resurses/athlas.png");
	int			*img = (int *)athlas->pixels;

	if (!(map = def_map()))
	{
		SDL_FreeSurface(athlas);
		SDL_FreeSurface(surface);
		SDL_DestroyWindow(window);
		exit(0);
	}

	if (!(player = def_player(map)))
	{
		SDL_FreeSurface(athlas);
		SDL_FreeSurface(surface);
		SDL_DestroyWindow(window);
		exit(0);
	}

	if (!(drawer = def_drawer()))
	{
		SDL_FreeSurface(athlas);
		SDL_FreeSurface(surface);
		SDL_DestroyWindow(window);
		exit(0);
	}

	SDL_Event	windowEvent;
	
	while (1)
	{
		clear_pixel(pixel);
		drawing(map, player, drawer, pixel, img);
		handling_event(windowEvent, player);
		SDL_UpdateWindowSurface(window);
	}
	return (0);
}

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
	// player->pos_x = 0;
	// player->pos_y = 0;
	player->angle = PLAYER_ANGLE * M_PI / 180;
	player->ray_depth = 30;
	player->fov = 60 * M_PI / 180;
	return (player);
}

t_drawer	*def_drawer()
{
	t_drawer	*drawer;

	if (!(drawer = (t_drawer *)malloc(sizeof(t_drawer))))
		return (NULL);
	return (drawer);
}

t_map		*def_map()
{
	t_map	*map;
	
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	// map->field =	"3212121212121213"\
	// 				"2..............2"\
	// 				"1..............1"\
	// 				"2..............2"\
	// 				"1..............1"\
	// 				"2..............2"\
	// 				"1..............1"\
	// 				"2......P.......2"\
	// 				"1..............1"\
	// 				"2..............2"\
	// 				"1..............1"\
	// 				"2..............2"\
	// 				"1..............1"\
	// 				"2..............2"\
	// 				"1..............1"\
	// 				"3212121212121213";
	
	map->field =	"3211111211111123"\
					"2..............2"\
					"1..3........2..1"\
					"1..............1"\
					"1..............1"\
					"1..............1"\
					"1..............1"\
					"2......P.......2"\
					"1..............1"\
					"1..............1"\
					"1..............1"\
					"1..............1"\
					"1..............1"\
					"1..2.......1...1"\
					"2..............2"\
					"3211112121111123";
	map->width = 16;
	map->height = 16;
	return (map);
}

void	drawing(t_map *map, t_player *player, t_drawer *drawer, int *pixel, int *img)
{
	static int qw = 0;
	
	drawer->cursor_x = 0;
	while (drawer->cursor_x < WIDTH)
	{
		drawer->ray_angle = ((drawer->cursor_x / (double)WIDTH) * player->fov) + (player->angle - player->fov / (double)2);
		drawer->ray_sin = sin(drawer->ray_angle);
		drawer->ray_cos = cos(drawer->ray_angle);

		// if (!qw)
			// printf("%f %f\n", drawer->ray_angle, tan(drawer->ray_angle));
			// printf("%f\n", drawer->barrier_x_f);
		
		def_raylen(map, player, drawer);

		// printf("%f %f\n", drawer->barrier_x_f, drawer->barrier_y_f);
		
		drawer->barrier_x_d = drawer->barrier_x_f;
		drawer->barrier_y_d = drawer->barrier_y_f;
		
		if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == '1')
		{
			drawer->wall_color = '1';
		}
		if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == '2')
		{
			drawer->wall_color = '2';
		}
		if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == '3')
		{
			drawer->wall_color = '3';
		}


		
		// drawer->ray_len = 0; // Расстояние до препятствия в направлении fRayAngle
		// while (drawer->ray_len < player->ray_depth) // Пока не столкнулись со стеной, Или не вышли за радиус видимости
		// {
		// 	drawer->barrier_x_f = player->pos_x + drawer->ray_len * drawer->ray_sin;
		// 	drawer->barrier_y_f = player->pos_y + drawer->ray_len * drawer->ray_cos;
		// 	drawer->barrier_x_d = (int)drawer->barrier_x_f;
		// 	drawer->barrier_y_d = (int)drawer->barrier_y_f;

		// 	if (check_barrier(map, player, drawer))
		// 		break ;
		// 	drawer->ray_len += 0.01;
		// }

		drawer->texel_x = drawer->barrier_x_f - (int)(drawer->barrier_x_f + 0.5); // floor -> int
		drawer->texel_y = drawer->barrier_y_f - (int)(drawer->barrier_y_f + 0.5); //

		if (fabs(drawer->texel_y) > fabs(drawer->texel_x))
		{
			drawer->tex_u = (int)(drawer->texel_y * 64);
			drawer->wall_part = 0;
		}
		else
		{
			drawer->tex_u = (int)(drawer->texel_x * 64);
			drawer->wall_part = 1;
		}
		if (drawer->tex_u < 0)
			drawer->tex_u += 64;

		// printf("%d\n", drawer->tex_u);

		// def_raylen1(map, player, drawer);
		def_wallparams(player, drawer);
		draw_room(player, drawer, pixel, img);
		drawer->cursor_x += 1;
	}

	// qw = 1;
	
	// drawer->cursor_x = 0;
	// while (drawer->cursor_x < WIDTH)
	// {
	// 	drawer->ray_angle = ((drawer->cursor_x / (double)WIDTH) * player->fov) + (player->angle - player->fov / (double)2);
	// 	drawer->ray_sin = sin(drawer->ray_angle);
	// 	drawer->ray_cos = cos(drawer->ray_angle);

	// 	// def_raylen(map, player, drawer);
	// 	// drawer->ray_len = 0; // Расстояние до препятствия в направлении fRayAngle
	// 	// while (drawer->ray_len < player->ray_depth) // Пока не столкнулись со стеной, Или не вышли за радиус видимости
	// 	// {
	// 	// 	drawer->barrier_x_f = player->pos_x + drawer->ray_len * drawer->ray_sin;
	// 	// 	drawer->barrier_y_f = player->pos_y + drawer->ray_len * drawer->ray_cos;
	// 	// 	drawer->barrier_x_d = (int)drawer->barrier_x_f;
	// 	// 	drawer->barrier_y_d = (int)drawer->barrier_y_f;

	// 	// 	if (check_barrier(map, player, drawer))
	// 	// 		break ;
	// 	// 	drawer->ray_len += 0.01;
	// 	// }

	// 	// drawer->texel_x = drawer->barrier_x_f - (int)(drawer->barrier_x_f + 0.5); // floor -> int
	// 	// drawer->texel_y = drawer->barrier_y_f - (int)(drawer->barrier_y_f + 0.5); //

	// 	// if (fabs(drawer->texel_y) > fabs(drawer->texel_x))
	// 	// {
	// 	// 	drawer->tex_u = (int)(drawer->texel_y * 64);
	// 	// 	drawer->wall_part = 0;
	// 	// }
	// 	// else
	// 	// {
	// 	// 	drawer->tex_u = (int)(drawer->texel_x * 64);
	// 	// 	drawer->wall_part = 1;
	// 	// }
	// 	// if (drawer->tex_u < 0)
	// 	// 	drawer->tex_u += 64;

	// 	def_raylen2(map, player, drawer);
	// 	def_wallparams(player, drawer);
	// 	draw_room(player, drawer, pixel, img);
	// 	drawer->cursor_x += 1;
	// }
	
}

// // VERSION 1 ITERATION
// void	def_raylen(t_map *map, t_player *player, t_drawer *drawer)
// {
// 	drawer->ray_len = 0; // Расстояние до препятствия в направлении fRayAngle
// 	while (drawer->ray_len < player->ray_depth) // Пока не столкнулись со стеной, Или не вышли за радиус видимости
// 	{
// 		drawer->barrier_x_f = player->pos_x + drawer->ray_len * drawer->ray_sin;
// 		drawer->barrier_y_f = player->pos_y + drawer->ray_len * drawer->ray_cos;
// 		drawer->barrier_x_d = (int)drawer->barrier_x_f;
// 		drawer->barrier_y_d = (int)drawer->barrier_y_f;

// 		if (check_barrier(map, player, drawer))
// 			break ;
// 		drawer->ray_len += 0.01;
// 	}
// }

// // VERSION 2 tan CALCULATION
// void	def_raylen(t_map *map, t_player *player, t_drawer *drawer)
// {
// 	int		i;
// 	double lenray1;
// 	double lenray2;

// 	double angle;
	
// 	angle = drawer->ray_angle;
// 	// while (angle > M_PI_2)
// 	// 	angle -= M_PI_2;

	
// 	lenray1 = player->ray_depth;
// 	lenray2 = player->ray_depth;

// 	// printf("%f\n", player->angle);
// 	// printf("%f\n", -M_PI);
// 	// exit(0);
	
// 	i = 0;
// 	while (i < player->ray_depth)
// 	{
// 		// drawer->barrier_x_f = (int)(player->pos_x + i);
// 		// if (drawer->ray_angle >= 0)
// 		// 	drawer->barrier_x_f = (int)(player->pos_x + i);
// 		// else
// 		// 	drawer->barrier_x_f = (int)(player->pos_x - i);

// 		// printf("%d %d\n", (int)(2.2) - 1, (int)(2.2 + 1 + 1));
// 		// exit(0);

// 		drawer->barrier_x_f = angle < 0 ? (int)(player->pos_x) - i : (int)(player->pos_x + 1 + i);

// 		if (angle > -M_PI_2 && angle < M_PI_2)
// 			drawer->barrier_y_f = player->pos_y + (drawer->barrier_x_f - player->pos_x) / tan(angle);
// 			// drawer->barrier_y_f = player->pos_y + (drawer->barrier_x_f - player->pos_x) / fabs(tan(angle));
// 		else
// 			drawer->barrier_y_f = player->pos_y + (drawer->barrier_x_f - player->pos_x) * tan(angle - M_PI_2);
// 		// else
// 		// {
// 		// 	if (angle > 0)
// 		// 		drawer->barrier_y_f = player->pos_y + (drawer->barrier_x_f - player->pos_x) * tan(angle - M_PI_2);
// 		// 	else
// 		// 		drawer->barrier_y_f = player->pos_y + (drawer->barrier_x_f - player->pos_x) * tan(angle + M_PI_2);
// 		// }
		
		
		
// 		lenray1 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
// 		drawer->barrier_x_d = (int)drawer->barrier_x_f;
// 		drawer->barrier_y_d = (int)drawer->barrier_y_f;
		
// 		if (check_barrier(map, player, drawer))
// 		{
// 			// lenray1 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
// 			// lenray1 = sqrt(pow(drawer->barrier_x_d - player->pos_x, 2) + pow(drawer->barrier_y_d - player->pos_y, 2));
// 			break ;
// 		}
// 		i += 1;
// 	}
// 	i = 0;
// 	while (i < player->ray_depth)
// 	{
// 		// drawer->barrier_y_f = (int)(player->pos_y + 1 + i);
// 		// drawer->barrier_y_f = angle > M_PI_2 ? (int)(player->pos_y) - i : (int)(player->pos_y + 1 + i);

// 		drawer->barrier_y_f = angle > -M_PI_2 && angle < M_PI_2 ? (int)(player->pos_y + 1 + i) : (int)(player->pos_y) - i;
		
// 		if (angle < M_PI_2)
// 			drawer->barrier_x_f = player->pos_x + (drawer->barrier_y_f - player->pos_y) * tan(angle);
// 		else
// 			drawer->barrier_x_f = player->pos_x + (drawer->barrier_y_f - player->pos_y) / tan(angle - M_PI_2);

// 		// printf("%f\n", drawer->barrier_x_f);
		
// 		lenray2 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
// 		drawer->barrier_x_d = (int)drawer->barrier_x_f;
// 		drawer->barrier_y_d = (int)drawer->barrier_y_f;
		
// 		if (check_barrier(map, player, drawer))
// 		{
// 			// lenray2 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
// 			// lenray2 = sqrt(pow(drawer->barrier_x_d - player->pos_x, 2) + pow(drawer->barrier_y_d - player->pos_y, 2));
// 			break ;
// 		}
// 		i += 1;
// 	}
	
// 	// drawer->ray_len = lenray1;
// 	drawer->ray_len = lenray1 < lenray2 ? lenray1 : lenray2;
// 	// printf("%f %f = %f\n", lenray1, lenray2, drawer->ray_len);
// }


// VERSION 3 tan KVADRANT
void	def_raylen(t_map *map, t_player *player, t_drawer *drawer)
{
	int		i;
	double lenray1;
	double lenray2;
	double angle;

	double xf1;
	double yf1;
	double xf2;
	double yf2;
	
	
	// lenray1 = player->ray_depth;
	// lenray2 = player->ray_depth;
	// drawer->ray_angle = drawer->ray_angle;
	
	if (drawer->ray_angle >= 2 * M_PI)
		drawer->ray_angle -= 2 * M_PI;
	if (drawer->ray_angle < 0)
		drawer->ray_angle = 2 * M_PI + drawer->ray_angle;
	

	// printf("%f\n", drawer->ray_angle);

	if (drawer->ray_angle >= 0 && drawer->ray_angle < M_PI_2)
	{
		// printf("I\n");
		i = 0;
		while (i < player->ray_depth)
		{
			drawer->barrier_x_f = (int)(player->pos_x + 1 + i);
			drawer->barrier_y_f = player->pos_y + (drawer->barrier_x_f - player->pos_x) / tan(drawer->ray_angle);
			drawer->barrier_x_d = (int)drawer->barrier_x_f;
			drawer->barrier_y_d = (int)drawer->barrier_y_f;
			xf1 = drawer->barrier_x_f;
			yf1 = drawer->barrier_y_f;
			
			if (check_barrier(map, player, drawer))
			{
				lenray1 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
				break ;
			}
			i += 1;
		}
		i = 0;
		while (i < player->ray_depth)
		{
			drawer->barrier_y_f = (int)(player->pos_y + 1 + i);
			drawer->barrier_x_f = player->pos_x + (drawer->barrier_y_f - player->pos_y) * tan(drawer->ray_angle);
			drawer->barrier_x_d = (int)drawer->barrier_x_f;
			drawer->barrier_y_d = (int)drawer->barrier_y_f;
			xf2 = drawer->barrier_x_f;
			yf2 = drawer->barrier_y_f;
			if (check_barrier(map, player, drawer))
			{
				lenray2 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
				break ;
			}
			i += 1;
		}
		drawer->ray_len = lenray1 < lenray2 ? lenray1 : lenray2;
		if (lenray1 < lenray2)
		{
			drawer->barrier_x_f = xf1;
			drawer->barrier_y_f = yf1;
		}
		else
		{
			drawer->barrier_x_f = xf2;
			drawer->barrier_y_f = yf2;
		}
		return ;
	}
	
	if (drawer->ray_angle >= M_PI_2 && drawer->ray_angle < M_PI)
	{
		// printf("II\n");
		i = 0;
		while (i < player->ray_depth)
		{
			drawer->barrier_x_f = (int)(player->pos_x + 1 + i);
			drawer->barrier_y_f = player->pos_y - (drawer->barrier_x_f - player->pos_x) * tan(drawer->ray_angle - M_PI_2);
			drawer->barrier_x_d = (int)drawer->barrier_x_f;
			drawer->barrier_y_d = (int)drawer->barrier_y_f;
			xf1 = drawer->barrier_x_f;
			yf1 = drawer->barrier_y_f;
			if (check_barrier(map, player, drawer))
			{
				lenray1 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
				break ;
			}
			i += 1;
		}
		i = 0;
		while (i < player->ray_depth)
		{
			drawer->barrier_y_f = (int)(player->pos_y) - i;
			drawer->barrier_x_f = player->pos_x + (player->pos_y - drawer->barrier_y_f) / tan(drawer->ray_angle - M_PI_2);
			drawer->barrier_x_d = (int)drawer->barrier_x_f;
			drawer->barrier_y_d = (int)drawer->barrier_y_f - 1;
			xf2 = drawer->barrier_x_f;
			yf2 = drawer->barrier_y_f - 1;
			if (check_barrier(map, player, drawer))
			{
				lenray2 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
				break ;
			}
			i += 1;
		}
		drawer->ray_len = lenray1 < lenray2 ? lenray1 : lenray2;
		if (lenray1 < lenray2)
		{
			drawer->barrier_x_f = xf1;
			drawer->barrier_y_f = yf1;
		}
		else
		{
			drawer->barrier_x_f= xf2;
			drawer->barrier_y_f= yf2;
		}
		return ;
	}

	if (drawer->ray_angle >= M_PI && drawer->ray_angle < (M_PI + M_PI_2))
	{
		// printf("III\n");
		i = 0;
		while (i < player->ray_depth)
		{
			drawer->barrier_x_f = (int)(player->pos_x) - i;
			drawer->barrier_y_f = player->pos_y - (player->pos_x - drawer->barrier_x_f) / tan(drawer->ray_angle - M_PI);
			drawer->barrier_x_d = (int)drawer->barrier_x_f - 1;
			drawer->barrier_y_d = (int)drawer->barrier_y_f;
			xf1 = drawer->barrier_x_f - 1;
			yf1 = drawer->barrier_y_f;
			if (check_barrier(map, player, drawer))
			{
				lenray1 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
				break ;
			}
			i += 1;
		}
		i = 0;
		while (i < player->ray_depth)
		{
			drawer->barrier_y_f = (int)(player->pos_y) - i;
			drawer->barrier_x_f = player->pos_x - (player->pos_y - drawer->barrier_y_f) * tan(drawer->ray_angle - M_PI);
			drawer->barrier_x_d = (int)drawer->barrier_x_f;
			drawer->barrier_y_d = (int)drawer->barrier_y_f - 1;
			xf2 = drawer->barrier_x_f;
			yf2 = drawer->barrier_y_f - 1;
			if (check_barrier(map, player, drawer))
			{
				lenray2 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
				break ;
			}
			i += 1;
		}
		drawer->ray_len = lenray1 < lenray2 ? lenray1 : lenray2;
		if (lenray1 < lenray2)
		{
			drawer->barrier_x_f = xf1;
			drawer->barrier_y_f = yf1;
		}
		else
		{
			drawer->barrier_x_f = xf2;
			drawer->barrier_y_f = yf2;
		}
		return ;
	}

	if (drawer->ray_angle >= (M_PI + M_PI_2) && drawer->ray_angle < 2 * M_PI)
	{
		// printf("IIII\n");
		i = 0;
		while (i < player->ray_depth)
		{
			drawer->barrier_x_f = (int)(player->pos_x) - i;
			drawer->barrier_y_f = player->pos_y + (player->pos_x - drawer->barrier_x_f) * tan(drawer->ray_angle - (M_PI + M_PI_2));
			drawer->barrier_x_d = (int)drawer->barrier_x_f - 1;
			drawer->barrier_y_d = (int)drawer->barrier_y_f;
			xf1 = drawer->barrier_x_f - 1;
			yf1 = drawer->barrier_y_f;
			if (check_barrier(map, player, drawer))
			{
				lenray1 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
				break ;
			}
			i += 1;
		}
		i = 0;
		while (i < player->ray_depth)
		{
			drawer->barrier_y_f = (int)(player->pos_y + 1 + i);
			drawer->barrier_x_f = player->pos_x - (drawer->barrier_y_f - player->pos_y) / tan(drawer->ray_angle - (M_PI + M_PI_2));
			// drawer->barrier_x_d = (int)drawer->barrier_x_f + 1;
			drawer->barrier_x_d = (int)drawer->barrier_x_f;
			drawer->barrier_y_d = (int)drawer->barrier_y_f;
			xf2 = drawer->barrier_x_f;
			yf2 = drawer->barrier_y_f;
			if (check_barrier(map, player, drawer))
			{
				lenray2 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
				break ;
			}
			i += 1;
		}
		drawer->ray_len = lenray1 < lenray2 ? lenray1 : lenray2;
		if (lenray1 < lenray2)
		{
			drawer->barrier_x_f= xf1;
			drawer->barrier_y_f= yf1;
		}
		else
		{
			drawer->barrier_x_f = xf2;
			drawer->barrier_y_f = yf2;
		}
		return ;
	}
	printf("wrong\n");
}




// // VERSION 2 sin/cos CALCULATION
// void	def_raylen(t_map *map, t_player *player, t_drawer *drawer)
// {
// 	int		i;
// 	double len_x;
// 	double len_y;
// 	double lenray1;
// 	double lenray2;

// 	lenray1 = player->ray_depth;
// 	lenray2 = player->ray_depth;
	
// 	i = 0;
// 	while (i < player->ray_depth)
// 	{
// 		drawer->barrier_x_f = (int)(player->pos_x + i);
// 		len_x = drawer->barrier_x_f - player->pos_x;
// 		lenray1 = len_x / drawer->ray_sin;
// 		len_y = lenray1 * drawer->ray_cos;
// 		drawer->barrier_y_f = len_y + player->pos_y;
// 		drawer->barrier_x_d = (int)drawer->barrier_x_f;
// 		drawer->barrier_y_d = (int)drawer->barrier_y_f;
		
// 		if (check_barrier(map, player, drawer))
// 		{
// 			// lenray1 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
// 			// lenray1 = sqrt(pow(drawer->barrier_x_d - player->pos_x, 2) + pow(drawer->barrier_y_d - player->pos_y, 2));
// 			break ;
// 		}
// 		i += 1;
// 	}

// 	i = 0;
// 	while (i < player->ray_depth)
// 	{
// 		drawer->barrier_y_f = (int)(player->pos_y + i);
// 		len_y = drawer->barrier_y_f - player->pos_x;
// 		lenray2 = len_y / drawer->ray_cos;
// 		len_x = lenray2 * drawer->ray_sin;
// 		drawer->barrier_x_f = len_x + player->pos_x;
// 		drawer->barrier_x_d = (int)drawer->barrier_x_f;
// 		drawer->barrier_y_d = (int)drawer->barrier_y_f;
		
// 		if (check_barrier(map, player, drawer))
// 		{
// 			// lenray2 = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
// 			// lenray2 = sqrt(pow(drawer->barrier_x_d - player->pos_x, 2) + pow(drawer->barrier_y_d - player->pos_y, 2));
// 			break ;
// 		}
// 		i += 1;
// 	}
// 	drawer->ray_len = lenray2;
// 	// drawer->ray_len = lenray1 < lenray2 ? lenray1 : lenray2;
// 	// printf("%f %f = %f\n", lenray1, lenray2, drawer->ray_len);
// }

// char	check_barrier(t_map *map, t_player *player, t_drawer *drawer)
// {
//  	if (drawer->barrier_x_d < 0 || drawer->barrier_x_d >= map->width || drawer->barrier_y_d < 0 || drawer->barrier_y_d >= map->height)
// 	// if (drawer->barrier_x_d < 0 || drawer->barrier_x_d == map->width || drawer->barrier_y_d < 0 || drawer->barrier_y_d == map->height)
// 	{
// 		// drawer->ray_len = player->ray_depth;
// 		return (1);
// 		// return (0);
// 	}
// 	if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == '1')
// 	{
// 		drawer->wall_color = '1';
// 		return (1);
// 	}
// 	if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == '2')
// 	{
// 		drawer->wall_color = '2';
// 		return (1);
// 	}
// 	if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == '3')
// 	{
// 		drawer->wall_color = '3';
// 		return (1);
// 	}
// 	return (0);
// }

char	check_barrier(t_map *map, t_player *player, t_drawer *drawer)
{
 	if (drawer->barrier_x_d < 0 || drawer->barrier_x_d >= map->width || drawer->barrier_y_d < 0 || drawer->barrier_y_d >= map->height)
	// if (drawer->barrier_x_d < 0 || drawer->barrier_x_d == map->width || drawer->barrier_y_d < 0 || drawer->barrier_y_d == map->height)
	{
		// drawer->ray_len = player->ray_depth;
		return (1);
		// return (0);
	}
	// if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == '1')
	// {
	// 	drawer->wall_color = '1';
	// 	return (1);
	// }
	// if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == '2')
	// {
	// 	drawer->wall_color = '2';
	// 	return (1);
	// }
	// if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == '3')
	// {
	// 	drawer->wall_color = '3';
	// 	return (1);
	// }
	if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] != '.' && map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] != 'P')
		return (1);
	return (0);
}


void	def_wallparams(t_player *player, t_drawer *drawer)
{
	drawer->ray_alpha = (player->fov * (WIDTH / 2 - drawer->cursor_x)) / (double)WIDTH;
	drawer->wall_up = (HEIGHT / 2) - (HEIGHT / (drawer->ray_len * cos(drawer->ray_alpha)));
	// drawer->wall_up = (HEIGHT / 2) - (HEIGHT / (drawer->ray_len));
	drawer->wall_down = HEIGHT - drawer->wall_up;
	drawer->wall_len = drawer->wall_down - drawer->wall_up;
}

void	draw_room(t_player *player, t_drawer *drawer, int *pixel, int *img)
{
	drawer->cursor_y = 0;
	while (drawer->cursor_y < drawer->wall_up)
	{
		pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = 0x00FFFF;
		drawer->cursor_y += 1;
	}

	draw_wall(player, drawer, pixel, img);

	while (drawer->cursor_y < HEIGHT)
	{
		pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = 0xAAAAAA;
		drawer->cursor_y += 1;
	}
}

void	draw_wall(t_player *player, t_drawer *drawer, int *pixel, int *img)
{	
	if (drawer->wall_color == '1')
	{
		while (drawer->cursor_y < drawer->wall_down && drawer->cursor_y < HEIGHT)
		{
			// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = 0xFF;
			pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 0, 0, 1)];
			drawer->cursor_y += 1;
		}
	}
	if (drawer->wall_color == '2')
	{
		while (drawer->cursor_y < drawer->wall_down && drawer->cursor_y < HEIGHT)
		{
			// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = 0xFF00;
			pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 4, 6, 1)];
			drawer->cursor_y += 1;
		}
	}
	if (drawer->wall_color == '3')
	{
		while (drawer->cursor_y < drawer->wall_down && drawer->cursor_y < HEIGHT)
		{
			// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = 0xFF0000;
			pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 4, 0, 1)];
			drawer->cursor_y += 1;
		}
	}
}

void	handling_event(SDL_Event windowEvent, t_player *player)
{
	if (SDL_PollEvent(&windowEvent))
	{
		if (windowEvent.type == SDL_KEYUP)
		{
			SDL_FlushEvent(SDL_KEYDOWN);
			return ;
		}
		if (windowEvent.type == SDL_QUIT ||
		(windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_ESCAPE))
			exit(0);
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_a)
		{
			player->pos_x += 0.1 * sin(player->angle + (90 * M_PI / (double)180));
			player->pos_y += 0.1 * cos(player->angle + (90 * M_PI / (double)180));
			return ;
		}
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_d)
		{
			player->pos_x -= 0.1 * sin(player->angle + (90 * M_PI / (double)180));
			player->pos_y -= 0.1 * cos(player->angle + (90 * M_PI / (double)180));
			return ;
		}
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_w)
		{
			player->pos_x += 0.1 * sin(player->angle);
			player->pos_y += 0.1 * cos(player->angle);
			return ;
		}
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_s)
		{
			player->pos_x -= 0.1 * sin(player->angle);
			player->pos_y -= 0.1 * cos(player->angle);
			return ;
		}
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_q)
		{
			player->angle += 1 * M_PI / (double)180;
			// if (player->angle > M_PI)
			// 	player->angle -= 2 * M_PI;
			if (player->angle >= 2 * M_PI)
				player->angle -= 2 * M_PI;
			return ;
		}
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_e)
		{
			player->angle -= 1 * M_PI / (double)180;
			// if (player->angle < -M_PI)
			// 	player->angle = 2 * M_PI + player->angle;
			if (player->angle < 0)
				player->angle = 2 * M_PI + player->angle;
			return ;
		}
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_z)
		{
			player->pos_x = 1; // Координата игрока по оси X
			player->pos_y = 1; // Координата игрока по оси Y
			player->angle = 0; // Направление игрока
			return ;
		}
	}
}

int		shift_tile(t_drawer *drawer, int athlas_width, int tile_width, int u_shift, int v_shift, char inverse)
{
	int		shift_tile;

	if (inverse)
		shift_tile = (tile_width - 2) - drawer->tex_u + (tile_width * u_shift) + ((tile_width - 2) * (drawer->cursor_y - drawer->wall_up) / drawer->wall_len) * athlas_width + (athlas_width * tile_width * v_shift);
	else
		shift_tile = drawer->tex_u + (tile_width * u_shift) + ((tile_width - 2) * (drawer->cursor_y - drawer->wall_up) / drawer->wall_len) * athlas_width + (athlas_width * tile_width * v_shift);
	return (shift_tile);
}