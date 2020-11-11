/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 12:26:05 by jthuy             #+#    #+#             */
/*   Updated: 2020/11/11 18:01:58 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_doorhorizont(int start_door, int end_door, int *pixel, double *z_buff)
{
	while (start_door < end_door && start_door < WIDTH)
	{
		if (start_door >= 0)
		{
			pixel[start_door + WIDTH * (HEIGHT / 2)] = 0xFF0000;
			z_buff[start_door + WIDTH * (HEIGHT / 2)] = 1;
		}
		start_door += 1;
	}	
}




// void	draw_door(t_map *map, t_player *player, int *pixel, int *img, int sprite_poz, int tile_numb, double *z_buff, t_drawer *drawer)
// {
// 	t_sprite sprite;

// 	// sprite.x = sprite_poz % map->width;
// 	// sprite.y = sprite_poz / map->width;
// 	sprite.x = sprite_poz % map->width + 0.5;
// 	sprite.y = sprite_poz / map->width + 0.5;

// 	// printf("%f\n", player->angle);

// 	double	sprite_dir = atan2(sprite.x - player->pos_x, sprite.y - player->pos_y);
// 	while (sprite_dir - player->angle > M_PI)
// 	 	sprite_dir -= 2 * M_PI; 
// 	while (sprite_dir - player->angle < -M_PI)
// 	 	sprite_dir += 2 * M_PI;
	
// 	double	sprite_dist = sqrt(pow(sprite.x - player->pos_x, 2) + pow(sprite.y - player->pos_y, 2));
// 	int		len_door = (int)(HEIGHT / sprite_dist) < 2000 ? (int)(HEIGHT * 2 / sprite_dist) : 2000;
	
// 	double sp_dir_pl = sprite_dir - player->angle;
// 	int axis_x = WIDTH / 2 - (sp_dir_pl * (WIDTH) / (player->fov));
// 	int offset_door = 0;
// 	// int offset_door = sprite_dist * sin(sprite_dir) * WIDTH / map->width;
// 	int start_door = axis_x - len_door / 2 + offset_door;
// 	int end_door = start_door + len_door + offset_door;
// 	int end_door2 = end_door;

// 	// int door_height = len_door;
// 	int door_height = len_door * (1 / cos(sp_dir_pl));
// 	// int door_height = len_door * (1 / cos(sprite_dir));
// 	int door_up = HEIGHT / 2 - door_height / 2;
// 	int door_down = HEIGHT - door_up;
	
// 	double sprite_w = len_door * map->width / (double)WIDTH;
// 	double sprite_wh = sprite_w / cos(sprite_dir);
// 	double sprite_h = sprite_wh * sin(sprite_dir);
// 	double sprite_x1 = sprite.x - sprite_w / 2;
// 	double sprite_y1 = sprite.y - sprite_h / 2;
// 	double sprite_x2 = sprite.x + sprite_w / 2;
// 	double sprite_y2 = sprite.y + sprite_h / 2;
// 	// double sprite_x;
// 	// double sprite_y;
// 	double	sprite_dir1 = atan2(sprite_x1 - player->pos_x, sprite_y1 - player->pos_y);
// 	double sp_dir_pl1 = sprite_dir1 - player->angle;
	
// 	int door_height1 = len_door * (1 / cos(sp_dir_pl1));
// 	// int door_height1 = len_door;
// 	int door_up1 = HEIGHT / 2 - door_height1 / 2;
// 	int door_down1 = HEIGHT - door_up1;

// 	drawer->wall_up = (HEIGHT / 2) - (HEIGHT / (drawer->ray_len * cos(drawer->ray_alpha)));
	

// 	while (door_up < door_down)
// 	{
// 		pixel[axis_x + WIDTH * door_up] = 0xFF0000;
// 		z_buff[axis_x + WIDTH * door_up] = 1;
// 		door_up += 1;
// 	}
	
// 	while (door_up1 < door_down1)
// 	{
// 		pixel[axis_x - len_door / 2 + WIDTH * door_up1] = 0xFF;
// 		z_buff[axis_x - len_door / 2 + WIDTH * door_up1] = 1;
// 		door_up1 += 1;
// 	}

// 	// printf("%d\n", start_door);
	
// 	while (start_door < -1)
// 	{
// 		start_door += 1;
// 		continue ;
// 	}
	
// 	// while (drawer->cursor_x < end_door)
// 	draw_doorhorizont(start_door, end_door, pixel, z_buff);
		
// 	drawer->cursor_x = 0;
// 	// while (drawer->cursor_x < WIDTH)
// 	while (drawer->cursor_x < WIDTH && end_door > start_door)
// 	{
// 		// if (start_door < -1)
// 		// {
// 		// 	start_door += 1;
// 		// 	// drawer->cursor_x += 1;
// 		// 	continue ;
// 		// }
		
// 		drawer->ray_angle = ((drawer->cursor_x / (double)WIDTH) * player->fov) + (player->angle - player->fov / (double)2);
// 		drawer->ray_sin = sin(drawer->ray_angle);
// 		drawer->ray_cos = cos(drawer->ray_angle);

// 		// drawer->ray_len = sqrt(pow(sprite_x1 - player->pos_x, 2) + pow(sprite_y1 - player->pos_y, 2));

// 		drawer->ray_len = 0;
// 		while (drawer->ray_len < player->ray_depth)
// 		{
// 			drawer->barrier_x_f = player->pos_x + drawer->ray_len * drawer->ray_sin;
// 			drawer->barrier_y_f = player->pos_y + drawer->ray_len * drawer->ray_cos;
// 			drawer->barrier_x_d = (int)drawer->barrier_x_f;
// 			drawer->barrier_y_d = (int)drawer->barrier_y_f;

// 			if (drawer->barrier_x_d < 0 || drawer->barrier_x_d >= map->width || drawer->barrier_y_d < 0 || drawer->barrier_y_d >= map->height)
// 			{
// 				drawer->ray_len = 0;
// 				break ;
// 			}
// 			// if (map->field[drawer->barrier_x_d + map->width * drawer->barrier_y_d] == 'E')
// 			// 	break;
// 			// if (drawer->barrier_x_d + map->width * drawer->barrier_y_d == sprite_poz)
// 			// 	break ;
// 			if (drawer->barrier_x_d + map->width * drawer->barrier_y_d == (int)(sprite.x + map->width * (int)sprite.y))
// 				break ;
// 			// if ((int)(drawer->barrier_x_f + map->width * drawer->barrier_y_f) == (int)(sprite.x + map->width * sprite.y))
// 			// 	break ;
// 			drawer->ray_len += 0.01;
// 		}

// 		if (!drawer->ray_len)
// 		{
// 			drawer->cursor_x += 1;
// 			continue ;
// 		}

// 		drawer->ray_len += 0.5;

// 		// drawer->texel_x = drawer->barrier_x_f - (int)(drawer->barrier_x_f + 0.5);
// 		// drawer->texel_y = drawer->barrier_y_f - (int)(drawer->barrier_y_f + 0.5);

// 		// if (fabs(drawer->barrier_x_f) > fabs(drawer->barrier_y_f))
// 		// if (drawer->barrier_x_d > drawer->barrier_y_d)
		
// 		// if (fabs(drawer->texel_x) > fabs(drawer->texel_y))
// 		// {
// 		// 	drawer->tex_u = (int)(drawer->texel_x * 64);
// 		// 	// drawer->wall_part = 1;
// 		// }
// 		// else
// 		// {
// 		// 	// drawer->tex_u = (int)(drawer->texel_y * 64);
// 		// 	// drawer->wall_part = 0;
// 		// 	drawer->cursor_x += 1;
// 		// 	continue ;
// 		// }
// 		// if (drawer->tex_u < 0)
// 		// 	drawer->tex_u += 64;

// 		// if (map->field[sprite_poz - 1] == '2' && map->field[sprite_poz + 1] == '2')
// 		// 	drawer->tex_u = (int)(drawer->texel_x * 64);
// 		// else if (map->field[sprite_poz - map->width] == '2' && map->field[sprite_poz + map->width] == '2')
// 		// 	drawer->tex_u = (int)(drawer->texel_y * 64);
// 		// else
// 		// {
// 		// 	drawer->cursor_x += 1;
// 		// 	continue ;
// 		// }
// 		// if (drawer->tex_u < 0)
// 		// 	drawer->tex_u += 64;
		
// 		if (!(map->field[sprite_poz - 1] == '2' && map->field[sprite_poz + 1] == '2') &&
// 			!(map->field[sprite_poz - map->width] == '2' && map->field[sprite_poz + map->width] == '2'))
// 		{
// 			drawer->cursor_x += 1;
// 			continue ;
// 		}
// 		drawer->tex_u = (65 * len_door * ((end_door2 - end_door) / (double)len_door)) / len_door;

// 		drawer->ray_alpha = (player->fov * (WIDTH / 2 - drawer->cursor_x)) / (double)WIDTH;
// 		drawer->wall_up = (HEIGHT / 2) - (HEIGHT / (drawer->ray_len * cos(drawer->ray_alpha)));
// 		drawer->wall_down = HEIGHT - drawer->wall_up;
// 		drawer->wall_len = drawer->wall_down - drawer->wall_up;

// 		drawer->cursor_y = drawer->wall_up;
// 		while (drawer->cursor_y < drawer->wall_down && drawer->cursor_y < HEIGHT)
// 		{
// 			// if (end_door < WIDTH && sprite_dist < z_buff[end_door + WIDTH * drawer->cursor_y])
// 			if (end_door < WIDTH && sprite_dist < z_buff[end_door + WIDTH * drawer->cursor_y])
// 			{
// 				// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = 0xFF;
// 			// pixel[drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 9, 2, 1)];
// 			// pixel[-drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 9, 2, 1)];
// 				// pixel[start_door + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 9, 2, 0)];
// 				// pixel[end_door + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, 2, 6, 1)];
				
// 				// if (drawer->ray_angle > -2.356 && drawer->ray_angle < 0.785) // <-- something wrong
// 				// 	pixel[end_door + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, tile_numb % 16, tile_numb / 16, 1)];
// 				// else
// 				// 	pixel[end_door + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, tile_numb % 16, tile_numb / 16, 0)];
					
// 				// pixel[drawer->cursor_x + WIDTH * drawer->cursor_y] = 0xFF;
// 				// pixel[end_door + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, tile_numb % 16, tile_numb / 16, 1)];
// 				// pixel[end_door + WIDTH * drawer->cursor_y] = 0xFF;
				
// 				pixel[end_door + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, tile_numb % 16, tile_numb / 16, 1)];

// 				// int	u_shift = (65 * len_door * ((end_door2 - end_door) / (double)len_door)) / len_door;
// 				// int	v_shift = (65 * drawer->wall_len * ((drawer->cursor_y - drawer->wall_up) / (double)drawer->wall_len)) / drawer->wall_len;
// 				// pixel[end_door + WIDTH * drawer->cursor_y] = img[u_shift + 1039 * v_shift];
				
// 				z_buff[end_door + WIDTH * drawer->cursor_y] = sprite_dist;
// 			}


// 			// if (sprite_dist < z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y])
// 			// {
// 			// 	pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, tile_numb % 16, tile_numb / 16, 1)];
// 			// 	z_buff[WIDTH - 1 - drawer->cursor_x + WIDTH * drawer->cursor_y] = sprite_dist;
// 			// }

			
// 			drawer->cursor_y += 1;
// 		}
// 		// start_door += 1;
// 		end_door -= 1;
// 		// pixel[WIDTH - 1 - drawer->cursor_x + WIDTH * (HEIGHT / 2)] = 0xFF0000;
// 		// pixel[drawer->cursor_x + WIDTH * (HEIGHT / 2)] = 0xFF0000;

// 		drawer->cursor_x += 1;
		
// 	}
// }



// void	draw_door(t_map *map, t_player *player, int *pixel, int *img, int sprite_poz, int tile_numb, double *z_buff, t_drawer *drawer)
// {
// 	t_sprite sprite;

// 	sprite.x = sprite_poz % map->width + 0.5;
// 	sprite.y = sprite_poz / map->width + 0.5;

// 	double	sprite_dir = atan2(sprite.x - player->pos_x, sprite.y - player->pos_y);
// 	while (sprite_dir - player->angle > M_PI)
// 	 	sprite_dir -= 2 * M_PI; 
// 	while (sprite_dir - player->angle < -M_PI)
// 	 	sprite_dir += 2 * M_PI;
	
// 	double	sprite_dist = sqrt(pow(sprite.x - player->pos_x, 2) + pow(sprite.y - player->pos_y, 2));
// 	int		len_door = (int)(HEIGHT / sprite_dist) < 2000 ? (int)(HEIGHT * 2 / sprite_dist) : 2000;
	
// 	double sp_dir_pl = sprite_dir - player->angle;
// 	int axis_x = WIDTH / 2 - (sp_dir_pl * (WIDTH) / (player->fov));
// 	// int offset_door = sprite_dist * sin(sprite_dir) * WIDTH / map->width;
// 	int start_door = axis_x - len_door / 2;
// 	int end_door = start_door + len_door;
// 	int end_door2 = end_door;
	
// 	while (start_door < -1)
// 	{
// 		start_door += 1;
// 		continue ;
// 	}

		
// 	drawer->cursor_x = 0;
// 	// while (drawer->cursor_x < WIDTH)
// 	while (drawer->cursor_x < WIDTH && end_door > start_door)
// 	{
		
// 		// def_raylen2(map, player, drawer);
// 		drawer->ray_angle = ((drawer->cursor_x / (double)WIDTH) * player->fov) + (player->angle - player->fov / (double)2);
// 		drawer->ray_sin = sin(drawer->ray_angle);
// 		drawer->ray_cos = cos(drawer->ray_angle);

// 		drawer->ray_len = 0;
// 		while (drawer->ray_len < player->ray_depth)
// 		{
// 			drawer->barrier_x_f = player->pos_x + drawer->ray_len * drawer->ray_sin;
// 			drawer->barrier_y_f = player->pos_y + drawer->ray_len * drawer->ray_cos;
// 			drawer->barrier_x_d = (int)drawer->barrier_x_f;
// 			drawer->barrier_y_d = (int)drawer->barrier_y_f;

// 			if (drawer->barrier_x_d < 0 || drawer->barrier_x_d >= map->width || drawer->barrier_y_d < 0 || drawer->barrier_y_d >= map->height)
// 			{
// 				drawer->ray_len = 0;
// 				break ;
// 			}
// 			if (drawer->barrier_x_d + map->width * drawer->barrier_y_d == (int)(sprite.x + map->width * (int)sprite.y))
// 				break ;
// 			drawer->ray_len += 0.01;
// 		}

// 		if (!drawer->ray_len)
// 		{
// 			drawer->cursor_x += 1;
// 			continue ;
// 		}



		
// 		drawer->ray_len += 0.5;
		
// 		// if (!(map->field[sprite_poz - 1] == '2' && map->field[sprite_poz + 1] == '2') &&
// 		// 	!(map->field[sprite_poz - map->width] == '2' && map->field[sprite_poz + map->width] == '2'))
// 		// {
// 		// 	drawer->cursor_x += 1;
// 		// 	continue ;
// 		// }
// 		drawer->tex_u = (65 * len_door * ((end_door2 - end_door) / (double)len_door)) / len_door;

// 		drawer->ray_alpha = (player->fov * (WIDTH / 2 - drawer->cursor_x)) / (double)WIDTH;
// 		drawer->wall_up = (HEIGHT / 2) - (HEIGHT / (drawer->ray_len * cos(drawer->ray_alpha)));
// 		drawer->wall_down = HEIGHT - drawer->wall_up;
// 		drawer->wall_len = drawer->wall_down - drawer->wall_up;

// 		drawer->cursor_y = drawer->wall_up;
// 		while (drawer->cursor_y < drawer->wall_down && drawer->cursor_y < HEIGHT)
// 		{
// 			if (end_door < WIDTH && sprite_dist < z_buff[end_door + WIDTH * drawer->cursor_y])
// 			{
// 				pixel[end_door + WIDTH * drawer->cursor_y] = img[shift_tile(drawer, 1039, 65, tile_numb % 16, tile_numb / 16, 1)];
// 				z_buff[end_door + WIDTH * drawer->cursor_y] = sprite_dist;
// 			}
// 			drawer->cursor_y += 1;
// 		}
// 		end_door -= 1;
// 		drawer->cursor_x += 1;
		
// 	}
// }
