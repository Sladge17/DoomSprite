/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 13:57:39 by jthuy             #+#    #+#             */
/*   Updated: 2020/11/30 13:07:03 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# include <stdio.h>

# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"


# define WIDTH	1600
# define HEIGHT	800

# define PLAYER_ANGLE 0

typedef struct	s_map
{
	char		*field;
	int			width;
	int			height;
}				t_map;

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		angle;
	double		ray_depth;
	int			fov;
	int			health;
	
	char		condition;

	char		shoot; //including to condition
	
	char		bitweapons;
	char		weapon;
	int			main_tile; //maybe char
	int			phase; //maybe char
	int			tile; //maybe char
}				t_player;

typedef struct	s_drawer
{
	int			cursor_x;
	int			cursor_y;
	double		ray_angle;
	double		ray_sin;
	double		ray_cos;
	
	double		raylen_tmp;
	double		ray_len;
	
	double		barrier_x_f;
	double		barrier_y_f;
	double		barrier_x_f_tmp;
	double		barrier_y_f_tmp;
	int			barrier_x_d;
	int			barrier_y_d;
	
	// for export to project
	double		ray_tan[2];
	double		raylen[2];
	double		barrier_f[2][2];
	int			barrier_d[2];
	double		texel[2];
	int			mapid;
	char		wall_tile;
	int			tex_u;
	int			athlas_pix;
	

	double		texel_x;
	double		texel_y;

	
	char		wall_part; //need rename
	char		wall_color;
	double		ray_alpha;
	int			wall_up;
	int			wall_down;
	int			wall_len;
	
}				t_drawer;

typedef struct	s_sprite
{
	double		pos_x;
	double		pos_y;
	double		direction;
	
	double		rotator;
	double		dev_coax;
	double		normal;
	
	double		dist;
	int			size;
	int			h_offset;
	int			v_offset;
	int			cursor_x;
	int			cursor_y;
}				t_sprite;

typedef struct		s_epath
{
	int				index;
	double			crd_x;
	double			crd_y;
	double			normal;
	struct s_epath	*next;
}					t_epath;

typedef struct		s_enemy
{
	t_epath			*path;
	t_epath			*start;
	t_epath			*end;
	double			pos_x;
	double			pos_y;
	double			normal;
	int				main_tile;
	char			health;
	char			condition;
	char			phase;
	
	int				shift_tile;
	double			p_div;
	int				tile;
	double			p_dir;

	double			hfov;	
	
	double			dist;
	int				size;
	int				shift_x;
	int				h_offset;
	int				v_offset;

	// char			punch; // <--- need dell

	
	struct s_enemy	*next;
}					t_enemy;

/*
** player.c
*/
t_player	*def_player(t_map *map);
void		set_pcondition(t_player *player, t_enemy *enemies);
void		set_stay(t_player *player);
void		set_pshoot(t_player *player, t_enemy *enemies);
void		shoot_player(t_player *player, t_enemy *enemies);


/*
** enemies.c
*/
t_enemy	*def_enemies(t_map *map);
t_epath	*def_epath(int ecounter);

void	set_econdition(t_enemy *enemies, t_player *player);
void	set_shoot(t_enemy *enemies, t_player *player);
void	set_detect(t_enemy *enemies, t_player *player);
void	set_dead(t_enemy *enemies, t_player *player);
void	set_punch(t_enemy *enemies, t_player *player);
void	set_walk(t_enemy *enemies, t_player *player);
void	set_position(t_enemy *enemies);
void	set_rotation(t_enemy *enemies, t_player *player);
void	set_walkphase(t_enemy *enemies);
void	set_spritesparam(t_enemy *enemies, t_player *player);
void	set_spriteparam(t_enemy *enemies, t_player *player);



void	draw_enemies(t_player *player, t_enemy *enemies, int *pixel, int *img, double *z_buff);
void	draw_vertlenemy(t_enemy *sprite, int *pixel, int *img, double *z_buff, int cursor_x, t_player *player);
void	print_enemies(t_enemy *enemies);
void	print_epath(t_enemy *enemies);

/*
** wolf3d.c
*/
void		set_timer(t_enemy *enemies, t_player *player);
t_map		*def_map();
t_drawer	*def_drawer();
void		drawing(t_map *map, t_player *player, t_enemy *enemies, t_drawer *drawer, int *pixel, int *img);
void		def_wallparams(t_player *player, t_drawer *drawer);
void		draw_room(t_player *player, t_drawer *drawer, int *pixel, int *img);
void		draw_wall(t_player *player, t_drawer *drawer, int *pixel, int *img);
int			shift_tile(t_drawer *drawer, int athlas_width, int tile_width, int u_shift, int v_shift, char inverse);
int			def_pixel(t_drawer *drawer, int tile_u, int tile_v, char inverse);
char		handling_event(SDL_Event windowEvent, t_player *player, t_enemy *enemies);

/*
** draw_sprite.c
*/
void	draw_sprite(t_map *map, t_player *player, int *pixel, int *img, int sprite_poz, int tile_numb, double *z_buff);
void	def_spriteparam(t_sprite *sprite, int sprite_poz, t_map *map, t_player *player);
void	draw_vertline(t_sprite *sprite, int *pixel, int *img, int tile_numb, double *z_buff);
/*
** door_sprite.c
*/
void	draw_door(t_map *map, t_player *player, int *pixel, int *img, int sprite_poz, int tile_numb, double *z_buff, t_drawer *drawer);
void	draw_door21(t_map *map, t_player *player, int *pixel, int *img, int sprite_poz, int tile_numb, double *z_buff, t_drawer *drawer);

/*
** door_sprite.c
*/
void	def_raylen(t_map *map, t_player *player, t_drawer *drawer);
char	check_barrier(t_map *map, t_player *player, t_drawer *drawer);
double	calc_raylen(t_player *player, t_drawer *drawer, char index);
void	def_barrierparam(t_player *player, t_drawer *drawer, char n_quad);
void	def_walltile(t_map *map, t_drawer *drawer);
void	def_walltile_u(t_drawer *drawer);

/*
** calc_quads.c
*/
void	calc_firstquad(t_map *map, t_player *player, t_drawer *drawer);
void	calc_secondquad(t_map *map, t_player *player, t_drawer *drawer);
void	calc_thirdquad(t_map *map, t_player *player, t_drawer *drawer);
void	calc_fourthquad(t_map *map, t_player *player, t_drawer *drawer);

/*
** draw_ui.c
*/
// void	draw_ui(int *pixel, int *img, int tile_u, int tile_v);
void	draw_ui(int *pixel, int *img, int tile);
void	draw_cross(int *pixel, t_enemy *enemies);


#endif