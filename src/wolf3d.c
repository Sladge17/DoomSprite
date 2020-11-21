/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 13:55:30 by jthuy             #+#    #+#             */
/*   Updated: 2020/11/21 14:23:20 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

# define COLOR_1 0xFF
# define COLOR_2 0xFF00
# define COLOR_3 0xFF0000

double		*z_buff;

int		main()
{
	t_map		*map;
	t_player	*player;
	t_enemy		*enemies;
	t_drawer	*drawer;


	if (SDL_Init(SDL_INIT_VIDEO))
		exit(0);

	SDL_Window	*window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface	*surface = SDL_GetWindowSurface(window);
	int			*pixel = (int *)surface->pixels;
	SDL_Surface	*athlas = IMG_Load("resurses/athlas.png");
	int			*img = (int *)athlas->pixels;

	z_buff = (double *)malloc(sizeof(double) * (WIDTH * HEIGHT));

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

	if (!(enemies = def_enemies(map)))
	{
		SDL_FreeSurface(athlas);
		SDL_FreeSurface(surface);
		SDL_DestroyWindow(window);
		exit(0);
	}
	// print_epath(enemies);
	// exit(0);

	
	set_enemies(enemies, player); // not need with patrol animation
	

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
		if (handling_event(windowEvent, player))
			set_enemies(enemies, player);

		set_patrol(enemies, player); //NEED TO ANIMATION
		
		drawing(map, player, enemies, drawer, pixel, img);
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
					"1.....2.2......1"\
					"1..............1"\
					"1..............1"\
					"1..............1"\
					"1..............1"\
					"1......P.......1"\
					"1..............1"\
					"1..............1"\
					"1......E.......1"\
					"1..............1"\
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

void	drawing(t_map *map, t_player *player, t_enemy *enemies, t_drawer *drawer, int *pixel, int *img)
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

	// int	door_pos = map->width + 1;
	// while (map->field[door_pos] != 'E')
	// 	door_pos += 1;
	// draw_door(map, player, pixel, img, door_pos, 98, z_buff, drawer);

	
	// int	sprite_pos = map->width + 1;
	// while (sprite_pos < map->width * map->height)
	// {
	// 	if (map->field[sprite_pos] == 'B')
	// 		draw_sprite(map, player, pixel, img, sprite_pos, 156, z_buff);
	// 		// draw_sprite(map, player, pixel, img, sprite_pos, 164, z_buff);
	// 	sprite_pos += 1;
	// }

	draw_enemies(player, enemies, pixel, img, z_buff);
	draw_cross(pixel, enemies);
	
	// draw_ui(pixel, img, 0, 33);
}

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

// int		shift_tile(t_drawer *drawer, int athlas_width, int tile_width, int u_shift, int v_shift, char inverse)
// {
// 	int		shift_tile;

// 	if (inverse)
// 		shift_tile = (tile_width - 2) - drawer->tex_u + (tile_width * u_shift) + ((tile_width - 2) * (drawer->cursor_y - drawer->wall_up) / drawer->wall_len) * athlas_width + (athlas_width * tile_width * v_shift);
// 	else
// 		shift_tile = drawer->tex_u + (tile_width * u_shift) + ((tile_width - 2) * (drawer->cursor_y - drawer->wall_up) / drawer->wall_len) * athlas_width + (athlas_width * tile_width * v_shift);
// 	return (shift_tile);
// }

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

char	handling_event(SDL_Event windowEvent, t_player *player)
{
	if (SDL_PollEvent(&windowEvent))
	{
		if (windowEvent.type == SDL_KEYUP)
		{
			SDL_FlushEvent(SDL_KEYDOWN);
			return (1);  //MAYBE NEED RETURT 0
		}
		if (windowEvent.type == SDL_QUIT ||
		(windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_ESCAPE))
			exit(0);
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_a)
		{
			player->pos_x += 0.1 * sin(player->angle + (90 * M_PI / (double)180));
			player->pos_y += 0.1 * cos(player->angle + (90 * M_PI / (double)180));
			return (1);
		}
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_d)
		{
			player->pos_x -= 0.1 * sin(player->angle + (90 * M_PI / (double)180));
			player->pos_y -= 0.1 * cos(player->angle + (90 * M_PI / (double)180));
			return (1);
		}
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_w)
		{
			player->pos_x += 0.1 * sin(player->angle);
			player->pos_y += 0.1 * cos(player->angle);
			return (1);
		}
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_s)
		{
			player->pos_x -= 0.1 * sin(player->angle);
			player->pos_y -= 0.1 * cos(player->angle);
			return (1);
		}
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_q)
		{
			player->angle += 1 * M_PI / (double)180;
			// if (player->angle > M_PI)
			// 	player->angle -= 2 * M_PI;
			if (player->angle >= 2 * M_PI)
				player->angle -= 2 * M_PI;
			return (1);
		}
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_e)
		{
			player->angle -= 1 * M_PI / (double)180;
			// if (player->angle < -M_PI)
			// 	player->angle = 2 * M_PI + player->angle;
			if (player->angle < 0)
				player->angle = 2 * M_PI + player->angle;
			return (1);
		}
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_z)
		{
			player->pos_x = 1; // Координата игрока по оси X
			player->pos_y = 1; // Координата игрока по оси Y
			player->angle = 0; // Направление игрока
			return (1);
		}
	}
	return (0);
}

