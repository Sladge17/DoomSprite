/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_kit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:37:12 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/25 20:13:50 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_KIT_H
# define SPRITE_KIT_H

/*
**Бензопила - анимация покоя
*/
# define S_SAW_S "SAWGC0"; name[1] = "SAWGD0"

/*
**Бензопила - анимация атаки
*/
# define S_SAW_G "SAWGA0"; name[1] = "SAWGB0"

# ifdef __APPLE__
#  include "SDL.h"
# elif __linux__
#  include "SDL2/SDL.h"
# endif

# include <stdint.h>
# include "rect.h"

typedef struct s_wad_player	t_wad_player;
typedef struct s_wad_hud	t_wad_hud;
typedef struct s_wad_sprite	t_wad_sprite;
typedef struct s_sub_sprite	t_sub_sprite;
typedef struct s_sub_gun	t_sub_gun;

enum		e_name_peh {
	peh_a1,		// straight 1
	peh_a2a8,	// straight left/right 45 degree 1
	peh_a3a7,	// left/right 1
	peh_a4a6,	// back left/right 45 degree 1
	peh_a8,		// back 1
	peh_b1,		// straight 2
	peh_b2b8,	// straight left/right 45 degree 2
	peh_b3b7,	// left/right 2
	peh_b4b6,	// back left/right 45 degree 2
	peh_b8,		// back 2
	peh_c1,		// straight 3
	peh_c2c8,	// straight left/right 45 degree 3
	peh_a3c7,	// left/right 3
	peh_c4c6,	// back left/right 45 degree 3
	peh_c8,		// back 3
	peh_d1,		// straight 4
	peh_d2d8,	// straight left/right 45 degree 4
	peh_d3d7,	// left/right 4
	peh_d4d6,	// back left/right 45 degree 4
	peh_d8,		// back 4
	peh_e1,		// fire straight 1
	peh_e2e8,	// fire straight 45 degree left/right 1
	peh_e3e7,	// fire left/right 1
	peh_e4e6,	// fire back 45 degree left/righr 1
	peh_e8,		// fire back 1
	peh_f1,		// fire straight 2
	peh_f2f8,	// fire straight 45 degree left/right 2
	peh_f3f7,	// fire left/right 2
	peh_f4f6,	// fire back 45 degree left/righr 2
	peh_f8,		// fire back 2
	peh_g1,		// death straight 1
	peh_g2g8,	// death straight left/right 45 degree 1
	peh_g3g7,	// death left/right 1
	peh_g4g6,	// death back left/right 45 degree 1
	peh_g8,		// death back 1
	peh_h0,		// death 2
	peh_h1,		// death 3
	peh_h2,		// death 4
	peh_h3,		// death 5
	peh_h4,		// death 6
	pig_a1,		// straight 1
	pig_a2a8,	// straight left/right 45 degree 1
	pig_a3a7,	// left/right 1
	pig_a4a6,	// back left/right 45 degree 1
	pig_a8,		// back 1
	pig_b1,		// straight 2
	pig_b2b8,	// straight left/right 45 degree 2
	pig_b3b7,	// left/right 2
	pig_b4b6,	// back left/right 45 degree 2
	pig_b8,		// back 2
	pig_c1,		// straight 3
	pig_c2c8,	// straight left/right 45 degree 3
	pig_a3c7,	// left/right 3
	pig_c4c6,	// back left/right 45 degree 3
	pig_c8,		// back 3
	pig_d1,		// straight 4
	pig_d2d8,	// straight left/right 45 degree 4
	pig_d3d7,	// left/right 4
	pig_d4d6,	// back left/right 45 degree 4
	pig_d8,		// back 4
	pig_e1,		// fire straight 1
	pig_e2e8,	// fire straight 45 degree left/right 1
	pig_e3e7,	// fire left/right 1
	pig_e4e6,	// fire back 45 degree left/righr 1
	pig_e8,		// fire back 1
	pig_f1,		// fire straight 2
	pig_f2f8,	// fire straight 45 degree left/right 2
	pig_f3f7,	// fire left/right 2
	pig_f4f6,	// fire back 45 degree left/righr 2
	pig_f8,		// fire back 2
	pig_g1,		// death straight 1
	pig_g2g8,	// death straight left/right 45 degree 1
	pig_g3g7,	// death left/right 1
	pig_g4g6,	// death back left/right 45 degree 1
	pig_g8,		// death back 1
	pig_h0,		// death 2
	pig_h1,		// death 3
	pig_h2,		// death 4
	pig_h3,		// death 5
	pig_h4,		// death 6
	gun_a0,		// gun 1
	gun_b0,		// gun 2
	gun_c0,		// gun 3
	gun_d0,		// gun 4
	gun_e0,		// gun 5
	gun_f0,		// gun fire
	shg_a0,		// shotgun 1
	shg_b0,		// shotgun 2
	shg_c0,		// shotgun 3
	shg_d0,		// shotgun 4
	shg_f0,		// shotgun fire 1
	shg_f1,		// shotgun fire 2
	sprt_total
};

struct		s_sub_sprite {
	t_pointf	origin;
	double		dist;
	double		*z_buff;
	int			name_sprite;
};

struct		s_sub_gun {
	bool	status;
	t_limit	*ammo;
};

struct		s_wad_sprite {
	char		*name;
	uint32_t	*pixel;
	int32_t		w;
	int32_t		h;
	int32_t		left_offset;
	int32_t		top_offset;
};

struct		s_wad_hud {
	t_wad_sprite	*stbar;
	t_wad_sprite	**digit;
	t_wad_sprite	**big_digit;
};

struct		s_wad_player {
	t_limit			health;
	t_limit			shield;
	t_limit			ammo[4];
	uint8_t			cur_gan;
	t_wad_sprite	**gun;
	void			(*shot)(SDL_Surface *, t_wad_sprite **, Uint32, t_sub_gun);
	bool			status;
};

uint32_t	get_pixel_sprite(t_wad_sprite *surface, int x, int y);

void		wad_draw_pistol(SDL_Surface *screen, t_wad_sprite **sprite,
				Uint32 delay, t_sub_gun sub);
void		wad_draw_shotgun(SDL_Surface *screen, t_wad_sprite **sprite,
				Uint32 delay, t_sub_gun sub);

void		draw_sprite_anim(SDL_Surface *screen, t_wad_sprite **sprite,
				Uint32 delay, t_sub_sprite sub);

void		blit_sprite_scaled(t_wad_sprite *src, SDL_Surface *dst,
				t_sub_sprite sub);
void		blit_gan_scaled(t_wad_sprite *src, SDL_Surface *dst);
void		blit_hud_scaled(t_wad_sprite *src, SDL_Surface *dst);
void		blit_sprite_scale(t_wad_sprite *src, SDL_Surface *dst,
				t_rectf rdst);

#endif
