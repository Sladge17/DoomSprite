/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 12:14:39 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/03 13:17:07 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAD_H
# define WAD_H

# include <stdint.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include "tree_struct.h"
# include "rect.h"
# include "sprite_kit.h"
# include "errorout.h"
# include "libft.h"

# ifdef __APPLE__
#  include "SDL.h"
# elif __linux__
#  include "SDL2/SDL.h"
# endif

# ifndef HEIGHT
#  define HEIGHT 800
# endif
# ifndef WIDTH
#  define WIDTH 1600
# endif

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
	
	struct s_enemy	*next;
}					t_enemy;

typedef struct			s_wad_head
{
	char				wad_type[5];
	uint32_t			dir_count;
	uint32_t			dir_offset;
}						t_wad_head;

typedef struct			s_dir
{
	uint32_t			lump_offset;
	uint32_t			lump_size;
	char				lump_name[9];
	struct s_dir		*next;
}						t_dir;

typedef struct			s_wad
{
	uint8_t				*map;
	struct s_wad_head	head;
	struct s_dir		*dir;
	uint32_t			color[14][256];
	uint32_t			colormap[34][256];
	t_things			*things;
	t_linedef			*linedef;
	t_sidedef			*sidedefs;
	t_vertex			*vert;
	t_seg				*segs;
	t_ssectors			*ssectors;
	t_node				*nodes;
	t_sector			*sectors;
	t_pnames			pname;
	t_texture_head		textures1;
	t_texture_head		textures2;
	int					buf1;
	int					buf2;
	uint16_t			bright;
	uint16_t			baff;
	uint16_t			temp_step;
}						t_wad;


/*Битовые операции с числами*/
uint16_t				bytes_to_short(const uint8_t *data, int offset);
uint32_t				bytes_to_int(const uint8_t *data, int offset);
Uint32					get_pixel(SDL_Surface *surface, int x, int y);
uint32_t				get_pixel_sprite(t_watsprite *sprite, int x, int y);
void					putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void					clear_surface(SDL_Surface *surface, Uint32 color);

bool					wad_loader(t_wad *wad, char *path);
bool					wad_reader(t_wad *wad);

void					wad_get_linedefs(t_wad *wad, char *name_map);
void					wad_get_vertex(t_wad *wad, char *name_map);
t_patch					wad_get_patch_info(const uint8_t *data,  uint32_t offset);
void					wad_get_playpal(t_wad *wad);
void					wad_get_colormap(t_wad *wad);
void					wad_get_textures(const uint8_t *data, uint32_t offset, t_texture_head *texture);
void					wad_get_pnames(const uint8_t *data, t_dir *dir ,t_pnames *pname);
void					wad_get_nodes(t_wad *wad, char *map_name);
void					wad_get_sidedefs(t_wad *wad, char *name_map);
void					wad_get_segs(t_wad *wad, char *name_map);
void					wad_get_ssectors(t_wad *wad, char *name_map);
void					wad_get_sectors(t_wad *wad, char *name_map);
void					wad_get_things(t_wad *wad, char *name_map);

void					read_head_data(const uint8_t *data, int offset, t_wad_head *head);
void					read_dir_data(const uint8_t *data, int offset, t_dir *dir);
void					wad_pars_name(const uint8_t *data, uint32_t offset, char name[9]);
void					wad_pars_box(const uint8_t *data, uint32_t offset, int16_t box[4]);

uint32_t				find_offset_lump(t_dir *dir, char *lable, char *name_map);
uint32_t				find_size_lump(t_dir *dir, char *lable, char *name_map);
uint32_t				wad_find_texture(t_dir *dir, char *name);

t_watsprite				*sprite_create(t_wad *wad, char *name);
void					draw_sprite(t_watsprite *sprite, SDL_Surface *screen,
							t_rect rect);
// void					blit_sprite_scale(t_watsprite *src, SDL_Surface *dst, t_rect *rdst);
void					blit_sprite_scale(t_enemy *enemies, t_watsprite *src, SDL_Surface *dst, t_rect *rdst);


#endif