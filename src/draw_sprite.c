/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:24:05 by jthuy             #+#    #+#             */
/*   Updated: 2020/08/17 21:44:05 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_sprite(t_map *map, t_player *player, int *pixel, int *img, int sprite_poz, int tile_numb, double *z_buff)
{
	t_sprite sprite;

	sprite.x = sprite_poz % map->width + 0.5;
	sprite.y = sprite_poz / map->width + 0.5;

	double	sprite_dir = atan2(sprite.x - player->pos_x, sprite.y - player->pos_y);
	while (sprite_dir - player->angle > M_PI)
	 	sprite_dir -= 2 * M_PI; 
	while (sprite_dir - player->angle < -M_PI)
	 	sprite_dir += 2 * M_PI;
	
	double	sprite_dist = sqrt(pow(sprite.x - player->pos_x, 2) + pow(sprite.y - player->pos_y, 2));
	int		sprite_screen_size = (int)(HEIGHT / sprite_dist) < 2000 ? (int)(HEIGHT * 2 / sprite_dist) : 2000;
	
	double sp_dir_pl = sprite_dir - player->angle;
	int shift_x = WIDTH / 2 - (sp_dir_pl * (WIDTH) / (player->fov));
	int h_offset = shift_x - sprite_screen_size / 2;

	int v_offset = HEIGHT / 2 - sprite_screen_size / 2;

	int		cursor_x;
	int		cursor_y;
	cursor_x = 0;
	while (cursor_x < sprite_screen_size)
	{
		if (h_offset + cursor_x < 0 || h_offset + cursor_x >= WIDTH)
		{
			cursor_x += 1;
			continue;
		}
		cursor_y = 0;
		while (cursor_y < sprite_screen_size)
		{
			if (v_offset + cursor_y < 0 || v_offset + cursor_y >= HEIGHT)
			{
				cursor_y += 1;
				continue;
			}
			if (img[(int)(65 * (cursor_x / (double)sprite_screen_size)) + 1039 * (int)(65 * (cursor_y / (double)sprite_screen_size)) + tile_numb % 16 * 65 + tile_numb / 16 * 1039 * 65] != 0xFF980088 &&
				(int)(65 * (cursor_x / (double)sprite_screen_size)) != 64 && (int)(65 * (cursor_y / (double)sprite_screen_size)) != 64 &&
				sprite_dist < z_buff[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)])
			{
				pixel[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = img[(int)(65 * (cursor_x / (double)sprite_screen_size)) + 1039 * (int)(65 * (cursor_y / (double)sprite_screen_size)) + tile_numb % 16 * 65 + tile_numb / 16 * 1039 * 65];
				z_buff[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = sprite_dist;
			}
			// pixel[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = 0xFF;
			cursor_y += 1;
		}
		cursor_x += 1;
	}
}

void	draw_door11(t_map *map, t_player *player, int *pixel, int *img, int sprite_poz, int tile_numb, double *z_buff, t_drawer *drawer)
{
	t_sprite sprite;

	sprite.x = sprite_poz % map->width + 0.5;
	sprite.y = sprite_poz / map->width + 0.5;

	double	sprite_dir = atan2(sprite.x - player->pos_x, sprite.y - player->pos_y);
	while (sprite_dir - player->angle > M_PI)
	 	sprite_dir -= 2 * M_PI; 
	while (sprite_dir - player->angle < -M_PI)
	 	sprite_dir += 2 * M_PI;
	
	// sprite.x = sprite_poz % map->width + 0.5;
	// sprite.y = sprite_poz / map->width + 0.5;

	
	double	sprite_dist = sqrt(pow(sprite.x - player->pos_x, 2) + pow(sprite.y - player->pos_y, 2));
	int		sprite_screen_size = (int)(HEIGHT / sprite_dist) < 2000 ? (int)(HEIGHT * 2 / sprite_dist) : 2000;
	
	double sp_dir_pl = sprite_dir - player->angle;
	int shift_x = WIDTH / 2 - (sp_dir_pl * (WIDTH) / (player->fov));
	int h_offset = shift_x - sprite_screen_size / 2;

	// int v_offset = HEIGHT / 2 - sprite_screen_size / 2;

	int		cursor_x;
	int		cursor_y;
	cursor_x = 0;
	while (cursor_x < sprite_screen_size)
	{
		if (h_offset + cursor_x < 0 || h_offset + cursor_x >= WIDTH)
		{
			cursor_x += 1;
			continue;
		}

		drawer->ray_alpha = (player->fov * (WIDTH / 2 - cursor_x)) / (double)WIDTH;
		drawer->wall_up = (HEIGHT / 2) - (HEIGHT / ((sprite_dist * cos(drawer->ray_alpha))));
		drawer->wall_down = HEIGHT - drawer->wall_up;
		drawer->wall_len = drawer->wall_down - drawer->wall_up;

		// drawer->ray_alpha = (player->fov * (WIDTH / 2 - drawer->cursor_x)) / (double)WIDTH;
		// drawer->wall_up = (HEIGHT / 2) - (HEIGHT / (drawer->ray_len * cos(drawer->ray_alpha)));
		// drawer->wall_down = HEIGHT - drawer->wall_up;
		// drawer->wall_len = drawer->wall_down - drawer->wall_up;

		

		int v_offset = HEIGHT / 2 - drawer->wall_len / 2;

		
		cursor_y = 0;
		// while (cursor_y < sprite_screen_size)
		while (cursor_y < drawer->wall_len)
		{
			if (v_offset + cursor_y < 0 || v_offset + cursor_y >= HEIGHT)
			{
				cursor_y += 1;
				continue;
			}
			// if (img[(int)(65 * (cursor_x / (double)sprite_screen_size)) + 1039 * (int)(65 * (cursor_y / (double)sprite_screen_size)) + tile_numb % 16 * 65 + tile_numb / 16 * 1039 * 65] != 0xFF980088 &&
			// 	(int)(65 * (cursor_x / (double)sprite_screen_size)) != 64 && (int)(65 * (cursor_y / (double)sprite_screen_size)) != 64 &&
			// 	sprite_dist < z_buff[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)])
			// {
			// 	pixel[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = img[(int)(65 * (cursor_x / (double)sprite_screen_size)) + 1039 * (int)(65 * (cursor_y / (double)sprite_screen_size)) + tile_numb % 16 * 65 + tile_numb / 16 * 1039 * 65];
			// 	z_buff[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = sprite_dist;
			// }
			// pixel[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = 0xFF;
			if (img[(int)(65 * (cursor_x / (double)sprite_screen_size)) + 1039 * (int)(65 * (cursor_y / (double)drawer->wall_len)) + tile_numb % 16 * 65 + tile_numb / 16 * 1039 * 65] != 0xFF980088 &&
				(int)(65 * (cursor_x / (double)sprite_screen_size)) != 64 && (int)(65 * (cursor_y / (double)drawer->wall_len)) != 64 &&
				sprite_dist < z_buff[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)])
			{
				pixel[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = img[(int)(65 * (cursor_x / (double)sprite_screen_size)) + 1039 * (int)(65 * (cursor_y / (double)drawer->wall_len)) + tile_numb % 16 * 65 + tile_numb / 16 * 1039 * 65];
				z_buff[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = sprite_dist;
			}
			cursor_y += 1;
		}
		cursor_x += 1;
	}
}

void	draw_door2(t_map *map, t_player *player, int *pixel, int *img, int tile_numb, double *z_buff, t_drawer *drawer)
{
	//---- START DRAW DOOR --------
	drawer->cursor_x = 0;
	while (drawer->cursor_x < WIDTH)
	{
		drawer->wall_color = '0';
		drawer->ray_angle = ((drawer->cursor_x / (double)WIDTH) * player->fov) + (player->angle - player->fov / (double)2);
		drawer->ray_sin = sin(drawer->ray_angle);
		drawer->ray_cos = cos(drawer->ray_angle);

		drawer->ray_len = 0; // Расстояние до препятствия в направлении fRayAngle
		while (drawer->ray_len < player->ray_depth) // Пока не столкнулись со стеной, Или не вышли за радиус видимости
		{
			drawer->barrier_x_f = player->pos_x + drawer->ray_len * drawer->ray_sin;
			drawer->barrier_y_f = player->pos_y + drawer->ray_len * drawer->ray_cos;
			drawer->barrier_x_d = (int)(drawer->barrier_x_f);
			drawer->barrier_y_d = (int)(drawer->barrier_y_f);

			if (drawer->barrier_x_d < 0 || drawer->barrier_x_d >= map->width || drawer->barrier_y_d < 0 || drawer->barrier_y_d >= map->height)
			{ // Если мы вышли за карту, то дальше смотреть нет смысла - фиксируем соударение на расстоянии видимости
				drawer->ray_len = player->ray_depth;
				break ;
			}
			if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == 'E')
			{ // Если встретили стену, то заканчиваем цикл
				drawer->wall_color = 'E';
				break ;
			}
			drawer->ray_len += 0.01;
		}
		if (drawer->wall_color != 'E')
		{
			drawer->cursor_x += 1;
			continue ;
		}

		drawer->ray_len += 0.5;


		drawer->texel_x = drawer->barrier_x_f - (int)(drawer->barrier_x_f + 0.5); // floor -> int
		drawer->texel_y = drawer->barrier_y_f - (int)(drawer->barrier_y_f + 0.5); //

		if (fabs(drawer->texel_y) > fabs(drawer->texel_x))
		{
			// drawer->tex_u = (int)(drawer->texel_y * 64);
			// drawer->wall_part = 0;
			drawer->cursor_x += 1;
			continue ;
		}
		else
		{
			drawer->tex_u = (int)(drawer->texel_x * 64);
			drawer->wall_part = 1;
		}
		if (drawer->tex_u < 0)
			drawer->tex_u += 64;

		
		drawer->ray_alpha = (player->fov * (WIDTH / 2 - drawer->cursor_x)) / (double)WIDTH;
		drawer->wall_up = (HEIGHT / 2) - (HEIGHT / ((drawer->ray_len) * cos(drawer->ray_alpha)));
		drawer->wall_down = HEIGHT - drawer->wall_up;
		drawer->wall_len = drawer->wall_down - drawer->wall_up;


		double	sprite_dir = atan2(drawer->barrier_x_f - player->pos_x, (drawer->barrier_y_f + 0.5) - player->pos_y);
		while (sprite_dir - player->angle > M_PI)
			sprite_dir -= 2 * M_PI; 
		while (sprite_dir - player->angle < -M_PI)
			sprite_dir += 2 * M_PI;
		
		// sprite.x = sprite_poz % map->width + 0.5;
		// sprite.y = sprite_poz / map->width + 0.5;

		
		// double	sprite_dist = sqrt(pow(drawer->barrier_x_f - player->pos_x, 2) + pow(drawer->barrier_y_f - player->pos_y, 2));
		// int		sprite_screen_size = (int)(HEIGHT / sprite_dist) < 2000 ? (int)(HEIGHT * 2 / sprite_dist) : 2000;
		
		double sp_dir_pl = sprite_dir - player->angle;

		
		// int shift_x = WIDTH / 2 - (sp_dir_pl * (WIDTH) / (player->fov));
		// int shift_x = WIDTH / 2 - (sprite_dir * (WIDTH) / (player->fov));
		// int shift_x = sprite_dist * sin(sprite_dir);
		int shift_x = drawer->ray_len * sin(sprite_dir);
		// int shift_x = 0;
		// int h_offset = shift_x - sprite_screen_size / 2;


		
		drawer->cursor_y = drawer->wall_up;
		while (drawer->cursor_y < drawer->wall_down && drawer->cursor_y < HEIGHT)  //drawer->cursor_y < drawer->wall_down && drawer->cursor_y < HEIGHT
		{
			// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = COLOR_1;
			// if (drawer->wall_part)
			// {
			// 	if (player->pos_y < drawer->barrier_y_d)
			// 		pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 64, 0, 0, 1)];
			// 	else
			// 		pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 64, 0, 0, 0)];
			// }
			// else
			// {
			// 	if (player->pos_x < drawer->barrier_x_d)
			// 		pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 64, 0, 0, 0)];
			// 	else
			// 		pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 64, 0, 0, 1)];
			// }
			if (drawer->wall_part)
			{
				if (WIDTH - 1 - drawer->cursor_x + shift_x < WIDTH && drawer->ray_len < z_buff[WIDTH - 1 - drawer->cursor_x + shift_x + WIDTH * drawer->cursor_y])
					pixel[WIDTH - 1 - drawer->cursor_x + shift_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 2, 6, 1)];
			}
			drawer->cursor_y += 1;
			continue ;
		}
		drawer->cursor_x += 1;
	}
	// ------ END DRAW DOOR -------
}

void	draw_door3(t_map *map, t_player *player, int *pixel, int *img, int sprite_poz, int tile_numb, double *z_buff, t_drawer *drawer)
{
	t_sprite sprite;

	sprite.x = sprite_poz % map->width + 0.5;
	sprite.y = sprite_poz / map->width + 0.5;

	double	sprite_dir = atan2(sprite.x - player->pos_x, sprite.y - player->pos_y);
	while (sprite_dir - player->angle > M_PI)
	 	sprite_dir -= 2 * M_PI; 
	while (sprite_dir - player->angle < -M_PI)
	 	sprite_dir += 2 * M_PI;
	
	double	sprite_dist = sqrt(pow(sprite.x - player->pos_x, 2) + pow(sprite.y - player->pos_y, 2));
	int		sprite_screen_size = (int)(HEIGHT / sprite_dist) < 2000 ? (int)(HEIGHT * 2 / sprite_dist) : 2000;
	
	double sp_dir_pl = sprite_dir - player->angle;
	int shift_x = WIDTH / 2 - (sp_dir_pl * (WIDTH) / (player->fov));
	int h_offset = shift_x - sprite_screen_size / 2;

	// int v_offset = HEIGHT / 2 - sprite_screen_size / 2;

	drawer->cursor_x = h_offset;
	while (drawer->cursor_x < drawer->cursor_x + sprite_screen_size)
	{
		if (drawer->cursor_x < 0 || drawer->cursor_x >= WIDTH)
		{
			drawer->cursor_x += 1;
			continue;
		}

		drawer->ray_angle = ((((drawer->cursor_x / (double)WIDTH) * player->fov) + (player->angle - player->fov / (double)2)) * drawer->cursor_x) / WIDTH;
		drawer->ray_sin = sin(drawer->ray_angle);
		drawer->ray_cos = cos(drawer->ray_angle);

		drawer->ray_len = 0; // Расстояние до препятствия в направлении fRayAngle
		while (drawer->ray_len < player->ray_depth) // Пока не столкнулись со стеной, Или не вышли за радиус видимости
		{
			drawer->barrier_x_f = player->pos_x + drawer->ray_len * drawer->ray_sin;
			drawer->barrier_y_f = player->pos_y + drawer->ray_len * drawer->ray_cos;
			drawer->barrier_x_d = (int)drawer->barrier_x_f;
			drawer->barrier_y_d = (int)drawer->barrier_y_f;

			if (((h_offset - drawer->cursor_x) / sprite_screen_size) * (h_offset + sprite_screen_size))
				break ;
			drawer->ray_len += 0.01;
		}

		drawer->texel_x = drawer->barrier_x_f - (int)(drawer->barrier_x_f + 0.5); // floor -> int
		drawer->texel_y = drawer->barrier_y_f - (int)(drawer->barrier_y_f + 0.5); //

		if (fabs(drawer->texel_y) > fabs(drawer->texel_x))
		{
			// drawer->tex_u = (int)(drawer->texel_y * 64);
			// drawer->wall_part = 0;
			drawer->cursor_x += 1;
			continue ;
		}
		else
		{
			drawer->tex_u = (int)(drawer->texel_x * 64);
			drawer->wall_part = 1;
		}
		if (drawer->tex_u < 0)
			drawer->tex_u += 64;

		drawer->ray_alpha = (player->fov * (WIDTH / 2 - drawer->cursor_x)) / (double)WIDTH;
		drawer->wall_up = (HEIGHT / 2) - (HEIGHT / (drawer->ray_len * cos(drawer->ray_alpha)));
		drawer->wall_down = HEIGHT - drawer->wall_up;
		drawer->wall_len = drawer->wall_down - drawer->wall_up;


		// int v_offset = HEIGHT / 2 - drawer->wall_len / 2;
		// drawer->cursor_y = v_offset;
		// while (drawer->cursor_y < drawer->cursor_y + sprite_screen_size)
		// {
		// 	if (drawer->cursor_y < 0 || drawer->cursor_y >= HEIGHT)
		// 	{
		// 		drawer->cursor_y += 1;
		// 		continue;
		// 	}
		// 	pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = 0xFF;
		// 	drawer->cursor_y += 1;
		// }
		pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * (HEIGHT / 2)] = 0xFF;
		drawer->cursor_x += 1;
	}
}


void	draw_door1(t_map *map, t_player *player, int *pixel, int *img, int sprite_poz, int tile_numb, double *z_buff, t_drawer *drawer)
{
	t_sprite sprite;

	sprite.x = sprite_poz % map->width + 0.5;
	sprite.y = sprite_poz / map->width + 0.5;

	double	sprite_dir = atan2(sprite.x - player->pos_x, sprite.y - player->pos_y);
	while (sprite_dir - player->angle > M_PI)
	 	sprite_dir -= 2 * M_PI; 
	while (sprite_dir - player->angle < -M_PI)
	 	sprite_dir += 2 * M_PI;
	
	// sprite.x = sprite_poz % map->width + 0.5;
	// sprite.y = sprite_poz / map->width + 0.5;

	
	double	sprite_dist = sqrt(pow(sprite.x - player->pos_x, 2) + pow(sprite.y - player->pos_y, 2));
	int		sprite_screen_size = (int)(HEIGHT / sprite_dist) < 2000 ? (int)(HEIGHT * 2 / sprite_dist) : 2000;
	
	double sp_dir_pl = sprite_dir - player->angle;
	int shift_x = WIDTH / 2 - (sp_dir_pl * (WIDTH) / (player->fov));
	int h_offset = sprite_screen_size / 2;//shift_x - 

	// int v_offset = HEIGHT / 2 - sprite_screen_size / 2;

	int		cursor_x;
	int		cursor_y;
	cursor_x =  h_offset;
	while (cursor_x < sprite_screen_size +  h_offset)
	{
		if (cursor_x < 0 || cursor_x >= WIDTH)
		{
			cursor_x += 1;
			continue;
		}

		drawer->ray_angle = ((cursor_x / (double)WIDTH) * player->fov) + (player->angle - player->fov / (double)2);
		//drawer->ray_alpha = (player->fov * (WIDTH / 2 - cursor_x)) / (double)WIDTH;
		//drawer->wall_up = (HEIGHT / 2) - (HEIGHT / ((sprite_dist * cos(drawer->ray_alpha))));
		//drawer->wall_down = HEIGHT - drawer->wall_up;
		//drawer->wall_len = drawer->wall_down - drawer->wall_up;

		// drawer->ray_alpha = (player->fov * (WIDTH / 2 - drawer->cursor_x)) / (double)WIDTH;
		// drawer->wall_up = (HEIGHT / 2) - (HEIGHT / (drawer->ray_len * cos(drawer->ray_alpha)));
		// drawer->wall_down = HEIGHT - drawer->wall_up;
		// drawer->wall_len = drawer->wall_down - drawer->wall_up;

		

		int v_offset = HEIGHT / 2 ;//- drawer->wall_len / 2;

		
		cursor_y = 0;
		// while (cursor_y < sprite_screen_size)
		//while (cursor_y < drawer->wall_len)

		int len = (sprite.y - player->pos_y) / cos(drawer->ray_angle);

		drawer->ray_alpha = (player->fov * (WIDTH / 2 - cursor_x)) / (double)WIDTH;
		drawer->wall_up = (HEIGHT / 2) - (HEIGHT / (len * cos(drawer->ray_alpha)));
		drawer->wall_down = HEIGHT - drawer->wall_up;
		
		//cursor_y = drawer->wall_up;
		//while (++cursor_y < drawer->wall_down)
		//{
			//if (cursor_y < 0 || cursor_y >= HEIGHT)
			//{
			//	cursor_y += 1;
			//	continue;
			//}
			// if (img[(int)(65 * (cursor_x / (double)sprite_screen_size)) + 1039 * (int)(65 * (cursor_y / (double)sprite_screen_size)) + tile_numb % 16 * 65 + tile_numb / 16 * 1039 * 65] != 0xFF980088 &&
			// 	(int)(65 * (cursor_x / (double)sprite_screen_size)) != 64 && (int)(65 * (cursor_y / (double)sprite_screen_size)) != 64 &&
			// 	sprite_dist < z_buff[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)])
			// {
			// 	pixel[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = img[(int)(65 * (cursor_x / (double)sprite_screen_size)) + 1039 * (int)(65 * (cursor_y / (double)sprite_screen_size)) + tile_numb % 16 * 65 + tile_numb / 16 * 1039 * 65];
			// 	z_buff[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = sprite_dist;
			// }
			// pixel[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = 0xFF;
			//if (img[(int)(65 * (cursor_x / (double)sprite_screen_size)) + 1039 * (int)(65 * (cursor_y / (double)drawer->wall_len)) + tile_numb % 16 * 65 + tile_numb / 16 * 1039 * 65] != 0xFF980088 &&
			//	(int)(65 * (cursor_x / (double)sprite_screen_size)) != 64 && (int)(65 * (cursor_y / (double)drawer->wall_len)) != 64 )//
				//&& sprite_dist < z_buff[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)])
			//{
			//	pixel[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = 0xff0000;//img[(int)(65 * (cursor_x / (double)sprite_screen_size)) + 1039 * (int)(65 * (cursor_y / (double)drawer->wall_len)) + tile_numb % 16 * 65 + tile_numb / 16 * 1039 * 65];
				//z_buff[h_offset + cursor_x + WIDTH * (v_offset + cursor_y)] = sprite_dist;
			//}
			//cursor_y += 1;
		//}
		cursor_y = drawer->wall_up;
		if (cursor_y >= 0 && cursor_y < HEIGHT)
			pixel[cursor_x + WIDTH * (cursor_y)] = 0xff0000;
		
		cursor_y = drawer->wall_down;
		if (cursor_y >= 0 && cursor_y < HEIGHT)
			pixel[cursor_x + WIDTH * (cursor_y)] = 0xff00ff;
		
		cursor_x += 1;
	}
}