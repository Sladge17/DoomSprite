/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 13:55:30 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/12 19:45:28 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

# define COLOR_1 0xFF
# define COLOR_2 0xFF00
# define COLOR_3 0xFF0000

double		*z_buff;

void	def_icon(SDL_Window	*window, int *img, int shift_x, int shift_y)
{
	SDL_Surface		*icon[2];
	int				*icon_img;
	int				i;
	int				pixel;

	if (!(icon[1] = SDL_CreateRGBSurface(0, 64, 64, 32, 0, 0, 0, 0)))
		exit(1);
	if (!(icon[0] = SDL_ConvertSurface
		(icon[1], SDL_AllocFormat(SDL_PIXELFORMAT_BGRA32), 0)))
		exit(1);
	SDL_FreeSurface(icon[1]);
	icon_img = (int *)icon[0]->pixels;
	i = -1;
	while(++i < 64 * 64)
	{
		pixel = i % 64 + (shift_x * 65) + 1039 * (i / 64 + (shift_y * 65));
		if (img[pixel] == 0xFF980088)
		{
			icon_img[i] = 0;
			continue ;
		}
		icon_img[i] = img[pixel];
	}
	SDL_SetWindowIcon(window, icon[0]);
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

	
	def_icon(window, img, 3, 42);
	
	// //Create icon!!!!
	// SDL_Surface		*icon[2];

	// if (!(icon[1] = SDL_CreateRGBSurface(0, 64, 64, 32, 0, 0, 0, 0)))
	// 	exit(1);
	// if (!(icon[0] = SDL_ConvertSurface(icon[1], surface->format, 0)))
	// 	exit(1);
	// SDL_FreeSurface(icon[1]);
	// int		*icon_img = (int *)icon[0]->pixels;
	
	// int		shift_x = 3;
	// int		shift_y = 42;
	
	
	// int		i = -1;
	// while(++i < 64 * 64)
	// {
	// 	if (img[i % 64 + (shift_x * 65) + 1039 * (i / 64 + (shift_y * 65))] == 0xFF980088)
	// 	{
	// 		icon_img[i] = 0;
	// 		continue ;
	// 	}
	// 	icon_img[i] = img[i % 64 + (shift_x * 65) + 1039 * (i / 64 + (shift_y * 65))];
	// }
	// SDL_SetWindowIcon(window, icon[0]);
	// // End create icon


	SDL_Rect		canvas;

	canvas.x = 0;
	canvas.y = 0;
	canvas.h = 64;
	canvas.w = 64;

	z_buff = (double *)malloc(sizeof(double) * (WIDTH * HEIGHT));

	// img[0] = 0xFF0000;
	// img[63] = 0xFF0000;
	// img[64 * 63] = 0xFF0000;
	// img[64 * 63 + 63] = 0xFF0000;
	// img[64/2 + 64 * (64 / 2)] = 0xFF0000;

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
		int		i = 0;
		while (i < WIDTH * HEIGHT)
		{
			z_buff[i] = 2147483647;
			i += 1;
		}
		handling_event(windowEvent, player);
		drawing(map, player, drawer, pixel, img);
		SDL_UpdateWindowSurface(window);
	}
	return (0);
}

t_map		*def_map()
{
	t_map	*map;
	
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	// map->field =	"1311111311111131"\
	// 				"1..............3"\
	// 				"1..CC.C.C..C...1"\
	// 				"1..............1"\
	// 				"1..............1"\
	// 				"1..............1"\
	// 				"1..............1"\
	// 				"1..............1"\
	// 				"2..C...P....C..2"\
	// 				"1..............1"\
	// 				"1..............1"\
	// 				"1..............1"\
	// 				"1..............1"\
	// 				"1..C...C...C...1"\
	// 				"1..............3"\
	// 				"1111112121111131";
	
	map->field =	"1111111121111111"\
					"1..............3"\
					"1..............1"\
					"1....B2.2B.....1"\
					"1..............1"\
					"1..............1"\
					"1..............1"\
					"1..............1"\
					"1......P.......1"\
					"1..............1"\
					"1..............1"\
					"1..............1"\
					"1.....2E2B.....1"\
					"1..............1"\
					"1..............1"\
					"1111111111111111";
	map->width = 16;
	map->height = 16;
	return (map);
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
	player->angle = PLAYER_ANGLE * M_PI / 180;
	player->ray_depth = 30;
	player->fov = 90 * M_PI / 180;
	return (player);
}

t_drawer	*def_drawer()
{
	t_drawer	*drawer;

	if (!(drawer = (t_drawer *)malloc(sizeof(t_drawer))))
		return (NULL);
	return (drawer);
}

void	drawing(t_map *map, t_player *player, t_drawer *drawer, int *pixel, int *img)
{
	drawer->cursor_x = 0;
	while (drawer->cursor_x < WIDTH)
	{
		def_raylen(map, player, drawer);
		def_walltile(map, drawer);
		
		def_walltile_u(drawer);
		def_wallparams(player, drawer);
		draw_room(player, drawer, pixel, img);
		drawer->cursor_x += 1;
	}

	// int		tex_shift_x = 4;
	// int		tex_shift_y = 7;
	// int		i = 0;
	// // // for athlas.png
	// while (i < 64 * 64)
	// {
	// 	if (img[i % 64 + 1039 * (i / 64) + (64 * tex_shift_x) + (1039 * 64 * tex_shift_y)] != 0xFF980088)
	// 		pixel[i % 64 + WIDTH * (i / 64)] = img[i % 64 + 1039 * (i / 64) + (64 * tex_shift_x) + (1039 * 64 * tex_shift_y)];
	// 	i += 1;
	// }
	// // // fir test_map.png
	// while (i < 64 * 64)
	// {
	// 	pixel[i % 64 + WIDTH * (i / 64)] = img[i % 64 + 64 * (i / 64)];
	// 	i += 1;
	// }

	int	door_pos = map->width + 1;
	while (map->field[door_pos] != 'E')
		door_pos += 1;
	 draw_door(map, player, pixel, img, door_pos, 98, z_buff, drawer);
	
	
	// draw_door2(map, player, pixel, img, 98, z_buff, drawer);
	
	// int	door_pos = map->width + 1;
	// while (door_pos < map->width * map->height)
	// {
	// 	if (map->field[door_pos] == 'E')
	// 	{
	// 		// printf("%c %c\n", map->field[door_pos - 1], map->field[door_pos + 1]);
	// 		// exit(0);
	// 		draw_door(map, player, pixel, img, door_pos, 98, z_buff, drawer);
	// 	}
	// 	door_pos += 1;
	// }

	
	int	sprite_pos = map->width + 1;
	while (sprite_pos < map->width * map->height)
	{
		if (map->field[sprite_pos] == 'B')
			draw_sprite(map, player, pixel, img, sprite_pos, 156, z_buff);
		sprite_pos += 1;
	}
	draw_ui(pixel, img, 0, 33);
}


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


// char	check_barrier(t_map *map, t_player *player, t_drawer *drawer)
// {
// 	if (drawer->barrier_x_d < 0 || drawer->barrier_x_d >= map->width || drawer->barrier_y_d < 0 || drawer->barrier_y_d >= map->height)
// 	{ // Если мы вышли за карту, то дальше смотреть нет смысла - фиксируем соударение на расстоянии видимости
// 		drawer->ray_len = player->ray_depth;
// 		return (1);
// 	}
// 	if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == '1')
// 	{ // Если встретили стену, то заканчиваем цикл
// 		drawer->wall_color = '1';
// 		return (1);
// 	}
// 	if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == '2')
// 	{ // Если встретили стену, то заканчиваем цикл
// 		drawer->wall_color = '2';
// 		return (1);
// 	}
// 	if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == '3')
// 	{ // Если встретили стену, то заканчиваем цикл
// 		drawer->wall_color = '3';
// 		return (1);
// 	}
// 	if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == 'C')
// 	{ // Если встретили стену, то заканчиваем цикл
// 		drawer->wall_color = 'C';
// 		return (1);
// 	}
// 	return (0);
// }

void	def_wallparams(t_player *player, t_drawer *drawer)
{
	drawer->ray_alpha = (player->fov * (WIDTH / 2 - drawer->cursor_x)) / (double)WIDTH;
	drawer->wall_up = (HEIGHT / 2) - (HEIGHT / (drawer->raylen[0] * cos(drawer->ray_alpha)));
	// drawer->wall_up = (HEIGHT / 2) - (HEIGHT / (drawer->ray_len));
	drawer->wall_down = HEIGHT - drawer->wall_up;
	drawer->wall_len = drawer->wall_down - drawer->wall_up;
}

void	draw_room(t_player *player, t_drawer *drawer, int *pixel, int *img)
{
	// При заданном X проходим по всем Y В этом цикле рисуется вертикальная полоска
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
	while (drawer->cursor_y < drawer->wall_down && drawer->cursor_y < HEIGHT)
	{
		if (drawer->wall_tile == '1')
		{
			// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = COLOR_1;
			if (drawer->wall_part)
			{
				if (player->pos_y < drawer->barrier_d[1])
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 0, 0, 1)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 0, 0, 1)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
				else
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 0, 0, 0)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 0, 0, 0)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
			}
			else
			{
				if (player->pos_x < drawer->barrier_d[0])
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 0, 0, 0)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 0, 0, 0)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
				else
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 0, 0, 1)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 0, 0, 1)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
			}
			drawer->cursor_y += 1;
			continue ;
		}
		
		if (drawer->wall_tile == '2')
		{
			// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = COLOR_2;
			if (drawer->wall_part)
			{
				if (player->pos_y < drawer->barrier_d[1])
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 4, 6, 1)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 4, 6, 1)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
				else
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 4, 6, 0)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 4, 6, 0)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
			}
			else
			{
				if (player->pos_x < drawer->barrier_d[0])
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 4, 6, 0)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 4, 6, 0)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
				else
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 4, 6, 1)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 4, 6, 1)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
			}
			drawer->cursor_y += 1;
			continue ;
		}
		if (drawer->wall_tile == '3')
		{
			// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = COLOR_3;
			if (drawer->wall_part)
			{
				if (player->pos_y < drawer->barrier_d[1])
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 4, 0, 1)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 4, 0, 1)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
				else
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 4, 0, 0)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 4, 0, 0)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
			}
			else
			{
				if (player->pos_x < drawer->barrier_d[0])
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 4, 0, 0)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 4, 0, 0)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
				else
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 4, 0, 1)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 4, 0, 1)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
			}
			drawer->cursor_y += 1;
			continue ;
		}

		// Column drawing
		if (drawer->wall_tile == 'C')
		{
			// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = COLOR_3;
			if (drawer->wall_part)
			{
				if (player->pos_y < drawer->barrier_d[1])
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 10, 4, 1)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 10, 4, 1)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
				else
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 8, 1, 0)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 8, 1, 0)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
			}
			else
			{
				if (player->pos_x < drawer->barrier_d[0])
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 0, 4, 0)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 0, 4, 0)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
				else
				{
					// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 10, 1, 1)];
					pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[def_pixel(drawer, 10, 1, 1)];
					z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = drawer->raylen[0];
				}
			}
			drawer->cursor_y += 1;
			continue ;
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

int		def_pixel(t_drawer *drawer, int tile_u, int tile_v, char inverse)
{
	drawer->athlas_pix = 65 * tile_u +
		(63 * (drawer->cursor_y - drawer->wall_up) /
		drawer->wall_len) * 1039 + (67535 * tile_v);
	drawer->athlas_pix = inverse ?
		63 - drawer->tex_u + drawer->athlas_pix :
		drawer->tex_u + drawer->athlas_pix;
	return (drawer->athlas_pix);
}

// void	handling_event(SDL_Event windowEvent, t_player *player)
// {
// 	if (SDL_PollEvent(&windowEvent))
// 	{
// 		if (windowEvent.type == SDL_KEYUP)
// 		{
// 			SDL_FlushEvent(SDL_KEYDOWN);
// 			return ;
// 		}
// 		if (windowEvent.type == SDL_QUIT ||
// 		(windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_ESCAPE))
// 			exit(0);
// 		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_a)
// 		{
// 			player->pos_x += 0.1 * sin(player->angle + (90 * M_PI / (double)180));
// 			player->pos_y += 0.1 * cos(player->angle + (90 * M_PI / (double)180));
// 			return ;
// 		}
// 		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_d)
// 		{
// 			player->pos_x -= 0.1 * sin(player->angle + (90 * M_PI / (double)180));
// 			player->pos_y -= 0.1 * cos(player->angle + (90 * M_PI / (double)180));
// 			return ;
// 		}
// 		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_w)
// 		{
// 			player->pos_x += 0.1 * sin(player->angle);
// 			player->pos_y += 0.1 * cos(player->angle);
// 			return ;
// 		}
// 		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_s)
// 		{
// 			player->pos_x -= 0.1 * sin(player->angle);
// 			player->pos_y -= 0.1 * cos(player->angle);
// 			return ;
// 		}
// 		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_q)
// 		{
// 			player->angle += 1 * M_PI / (double)180;
// 			return ;
// 		}
// 		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_e)
// 		{
// 			player->angle -= 1 * M_PI / (double)180;
// 			return ;
// 		}
// 		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_z)
// 		{
// 			player->pos_x = 1; // Координата игрока по оси X
// 			player->pos_y = 1; // Координата игрока по оси Y
// 			player->angle = 0; // Направление игрока
// 			return ;
// 		}
// 	}
// }

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

