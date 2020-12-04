/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 13:55:30 by jthuy             #+#    #+#             */
/*   Updated: 2020/12/04 13:03:58 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

# define COLOR_1 0xFF
# define COLOR_2 0xFF00
# define COLOR_3 0xFF0000

double		*z_buff;

void			name_big_digit(char **name)
{
	int			i;
	i = -1;
	while (++i < 6)
		name[i] = (char *)ft_memalloc(sizeof(char) * 9);
	// name[0] = "SARGA1";
	// name[1] = "SARGB1";
	// name[2] = "SARGC1";
	// name[3] = "SARGD1";
	// name[4] = "SARGE1";
	
	// name[0] = "BOSSA1";
	// name[1] = "BOSSB1";
	// name[2] = "BOSSC1";
	// name[3] = "BOSSD1";
	// name[4] = "BOSSE1";
	
	name[0] = "POSSA1";
	name[1] = "POSSB1";
	name[2] = "POSSC1";
	name[3] = "POSSD1";
	name[4] = "POSSE1";

	name[5] = NULL;
}

int		main()
{
	t_map		*map;
	t_player	*player;
	t_enemy		*enemies;
	t_props		*props;
	t_drawer	*drawer;
	// t_wad		*wad;
	
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
	
	if (!(props = def_props(map)))
	{
		SDL_FreeSurface(athlas);
		SDL_FreeSurface(surface);
		SDL_DestroyWindow(window);
		exit(0);
	}
	// print_props(props);
	// exit(0);

	
	// set_enemies(enemies, player); // not need with patrol animation
	

	if (!(drawer = def_drawer()))
	{
		SDL_FreeSurface(athlas);
		SDL_FreeSurface(surface);
		SDL_DestroyWindow(window);
		exit(0);
	}

	set_propsparam(props, player);
	
	// wad = (t_wad *)ft_memalloc(sizeof(t_wad));
	// wad_loader(wad, "map.wad");
	// wad_reader(wad);

	// LOAD WADSPRITES
	// t_sprite **sprite;
	// int m = -1;
	// char **name;

	// name = (char **)ft_memalloc(sizeof(char *) * 6);
	// name_big_digit(name);
	// sprite = (t_sprite **)ft_memalloc(sizeof(t_sprite *) * 6);
	// while (++m < 5)
	// 	sprite[m] = sprite_create(wad, name[m]);
		
	SDL_Event	windowEvent;
	while (1)
	{
		int		i = 0;
		while (i < WIDTH * HEIGHT)
		{
			z_buff[i] = 2147483647;
			i += 1;
		}
		// // handling_event(windowEvent, player, enemies);
		if (handling_event(windowEvent, player, enemies))
		{
			set_enemiesparam(enemies, player);
			set_propsparam(props, player);
			drawing(map, player, enemies, props, drawer, pixel, img);
			// drawing(map, player, enemies, props, drawer, pixel, img, sprite, surface);
			// blit_sprite_scale(sprite, surface, &((t_rect){enemies->h_offset, enemies->v_offset, enemies->size / 2, enemies->size / 2, false}));
			SDL_UpdateWindowSurface(window);
			continue ;
		}
		// // printf("out\n");
		set_timer(enemies, player);
		
		drawing(map, player, enemies, props, drawer, pixel, img);
		// drawing(map, player, enemies, props, drawer, pixel, img, sprite, surface);
		// blit_sprite_scale(sprite, surface, &((t_rect){enemies->h_offset, enemies->v_offset, enemies->size / 2, enemies->size / 2, false}));

		SDL_UpdateWindowSurface(window);
	}
	return (0);
}

void	set_timer(t_enemy *enemies, t_player *player)
{
	static long	time = 0;

	if (time % 50 == 0)
	{
		// player->tile = player->tile_weapon + player->phase;
		// player->phase += 1;
		// if (player->phase > 4)
		// 	player->phase = 0;
		set_pcondition(player, enemies);
		set_econdition(enemies, player);
	}
	time += 1;
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
					"1...H......H...1"\
					"1......A.......1"\
					"1..............1"\
					"1..............1"\
					"1..............1"\
					"1111111111111111";
	map->width = 16;
	map->height = 16;
	return (map);
}

t_drawer	*def_drawer()
{
	t_drawer	*drawer;

	if (!(drawer = (t_drawer *)malloc(sizeof(t_drawer))))
		return (NULL);
	return (drawer);
}

void	drawing(t_map *map, t_player *player, t_enemy *enemies, t_props *props, t_drawer *drawer, int *pixel, int *img)
// void	drawing(t_map *map, t_player *player, t_enemy *enemies, t_props *props, t_drawer *drawer, int *pixel, int *img, t_sprite **wad_sprite, SDL_Surface *screen)
{
	static int sprt = 0;
	
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

	// // CLEAR SCREEN
	// int		i = 0;
	// while (i < WIDTH * HEIGHT)
	// {
	// 	pixel[i] = 0;
	// 	i += 1;
	// }

	draw_enemies(enemies, pixel, img, z_buff);

	draw_props(player, props, pixel, img, z_buff);
	draw_cross(pixel, enemies);
	
	// draw_ui(pixel, img, 0, 33);
	// draw_ui(pixel, img, 527);
	draw_ui(pixel, img, player->tile);
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

char	handling_event(SDL_Event windowEvent, t_player *player, t_enemy *enemies)
{
	static char		condition = 1;
	
	if (SDL_PollEvent(&windowEvent))
	{
		// // WHAT IS IT ???
		// if (windowEvent.type == SDL_KEYUP)
		// {
		// 	SDL_FlushEvent(SDL_KEYDOWN);
		// 	return (1);  //MAYBE NEED RETURT 0
		// }
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
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_SPACE)
		{
			// if (!condition)
			// 	return (0);
			// condition = 0;
			// player->shoot = 1;
			player->condition |= 0b1;
			shoot_player(player, enemies);
			return (1);
		}
		if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_SPACE)
		{
			// player->shoot = 0;
			player->condition ^= 0b1;
			shoot_player(player, enemies);
			// condition = 1;
			return (1);
		}
	}
	return (0);
}

