/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/03 13:20:28 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

// void				user_cursor(t_doom *doom)
// {
// 	SDL_Cursor		*curs;

// 	curs = SDL_CreateColorCursor(sdl->textures[texture_cursor0], 5, 1);
// 	SDL_SetCursor(curs);
// }

void				wad_init_level(t_wad *wad, char *name_map)
{
	wad_get_things(wad, name_map);
	wad_get_linedefs(wad, name_map);
	wad_get_sidedefs(wad, name_map);
	wad_get_vertex(wad, name_map);
	wad_get_segs(wad, name_map);
	wad_get_ssectors(wad, name_map);
	wad_get_nodes(wad, name_map);
	wad_get_sectors(wad, name_map);
}

// void				skin(t_doom *doom)
// {
// 	SDL_GetWindowSize(sdl->window, &sdl->width, &sdl->height);
// 	user_cursor(doom);
// 	SDL_SetWindowIcon(sdl->window, sdl->textures[texture_icon]);
// 	fill_limit(&pla->er.heals, 0, 190, 200);
// }

void				wad_destroy_patch(t_patch patch)
{
	if (patch.columnoffset)
		free(patch.columnoffset);
	ft_bzero(&patch, sizeof(patch));
}

static void				put_column(t_wad *wad, uint32_t offset,
							int x, t_watsprite *sprite)
{
	uint16_t			iter;
	uint16_t			col;
	int					y_step;
	int					y_miss;

	y_step = wad->map[offset];
	y_miss = 0;
	col = wad->map[offset + 1];
	iter = 0;
	offset += 3;
	while (y_miss - 1 < sprite->h && wad->map[offset + 1] != 255)
	{
		sprite->pixel[y_step * sprite->w + x] = wad->color[wad->baff]
			[wad->colormap[wad->bright]
			[wad->map[offset]]];
		++iter;
		++offset;
		++y_miss;
		if (iter == col && wad->map[offset + 1] != 255)
		{
			col = wad->map[offset + 2];
			y_step = wad->map[offset + 1];
			offset += 4;
			iter = 0;
		}
		else
			y_step++;
	}
}

void				draw_sprite(t_watsprite *sprite, SDL_Surface *screen,
						t_rect rect)
{
	int				x;
	int				y;
	uint32_t		color;

	x = 0;
	rect.x -= sprite->left_offset;
	rect.y -= sprite->top_offset;
	while (x < sprite->w)
	{
		y = 0;
		while (y < sprite->h)
		{
			color = get_pixel_sprite(sprite, x, y);
			if (color == 0xFFFFFFFF)
			{
				++y;
				continue ;
			}
			putpixel(screen, rect.x + x, rect.y + y, color);
			++y;
		}
		++x;
	}
}

t_watsprite			*sprite_create(t_wad *wad, char *name)
{
	t_watsprite		*sprite;
	t_patch			patch;
	uint32_t		offset;
	int				x;

	if (!(sprite = (t_watsprite *)ft_memalloc(sizeof(t_watsprite))))
		return (NULL);
	offset = find_offset_lump(wad->dir, name, NULL);
	patch = wad_get_patch_info(wad->map, offset);
	sprite->name = ft_strdup(name);
	sprite->h = patch.height;
	sprite->w = patch.width;
	sprite->left_offset = patch.left_offset;
	sprite->top_offset = patch.top_offset;
	sprite->pixel = (uint32_t *)malloc(sizeof(uint32_t) *
		(sprite->w * sprite->h));
	sprite->pixel = (uint32_t *)ft_memset(sprite->pixel, 0xFFFFFFFF,
		sizeof(uint32_t) * sprite->w * sprite->h);
	x = -1;
	while (++x < patch.width)
		put_column(wad, offset + patch.columnoffset[x], x, sprite);
	wad_destroy_patch(patch);
	return (sprite);
}


// int					main(int ac, char **av)
// {
// 	t_doom	*doom;

// 	char			*name_map = {"E1M1"};

// 	if (ac == 2 || ac == 3)
// 	{
// 		doom = ft_memalloc(sizeof(t_doom));
// 		init_lib_sdl(doom);
// 		if (load_res(doom) == false | wad_loader(&wad av[1]) == false)
// 		{
// 			doom_exit(doom);
// 			return (0);
// 		}
// 		wad_reader(&wad->;
// 		wad_init_level(&wad-> name_map);
// 		skin(doom);
// 		scr->en = init_editor(doom);
// 		wad->baff = 0;
// 		wad->bright = 0;
// 		// texture = wad_draw_texture(doom, fill_point(0, 0), av[2]);

// 		t_watsprite	**sprites;
// 		char		**name;
// 		int			i = 0;

// 		name = (char **)ft_memalloc(sizeof(char *));
// 		while (i < SAW)
// 		{
// 			name[i] = ft_memalloc(sizeof(char) * 9);
// 			++i;
// 		}
// 		name[0] = "SAWGC0";
// 		name[1] = "SAWGD0";
// 		i = 0;
// 		sprites = (t_watsprite **)ft_memalloc(sizeof(t_watsprite *));
// 		while (i <= SAW)
// 		{
// 			sprites[i] = (t_watsprite *)ft_memalloc(sizeof(t_watsprite));
// 			++i;
// 		}

// 		i = 0;
// 		while (i < SAW)
// 			(sprites[i] = sprite_create(doom, name[i])) && ++i;
// 		sprites[i] = NULL;

// 		// t_watsprite *hud = sprite_create(doom, "STBAR");

// 		timer_start(&tim->);
// 		while (qui-> == false)
// 		{
// 			// fps_counter(&tim->);
// 			// frame_tamer(doom, scr->en);
// 			// wad_draw_linedefs(wad-> wad->vert, sdl->surface, name_map);
// 			// draw_line(sdl->surface, (t_point){HALF_WIDTH, 0}, (t_point){HALF_WIDTH, HEIGHT_WIN}, 0xffffff);
// 			// draw_line(sdl->surface, (t_point){0, HALF_HEIGHT}, (t_point){WIDTH_WIN, HALF_HEIGHT}, 0xffffff);

// 			draw_sprite_anim(doom, sprites, 200);
// 			// blit_gan_scaled(sprites[i], sdl->surface);
// 			// blit_hud_scaled(hud, sdl->surface, NULL);

// 			event_list(doom);
// 			SDL_UpdateWindowSurface(sdl->window);
// 			clear_surface(sdl->surface, 0);
// 		}
// 		doom_exit(doom);
// 	}
// 	else if (!av[1])
// 		ft_putendl(USAGE_DOOM);
// 	return (0);
// }
