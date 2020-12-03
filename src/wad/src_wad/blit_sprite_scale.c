/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_sprite_scale.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:03:55 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/03 13:18:10 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"


static t_rectf		check_scale_delta(t_rect *rdst, t_rect *rsrc)
{
	t_rectf			delta;

	if (rdst->h == rsrc->h)
		delta.h = 1.0;
	else
		delta.h = ((rsrc->h * 1.0) / (rdst->h * 1.0));
	if (rdst->w == rsrc->w)
		delta.w = 1.0;
	else
		delta.w = ((rsrc->w * 1.0) / (rdst->w * 1.0));
	return (delta);
}

static void			while_scale_pic(t_watsprite *src, t_rect *rsrc,
					SDL_Surface *dst, t_rect *rdst)
{
	t_pointf		crd[2];
	t_rectf			delta;
	Uint32			color;

	delta = check_scale_delta(rdst, rsrc);
	crd[0].y = rdst->y;
	crd[1].y = rsrc->y;
	while (crd[1].y < rsrc->h || crd[0].y < rdst->y + rdst->h)
	{
		crd[0].x = rdst->x;
		crd[1].x = rsrc->x;
		while (crd[1].x < rsrc->w || crd[0].x < rdst->x + rdst->w)
		{
			color = get_pixel_sprite(src, crd[1].x, crd[1].y);
			if (color == 0xFFFFFFFF)
			{
				(crd[1].x += delta.w) && crd[0].x++;
				continue ;
			}
			putpixel(dst, crd[0].x, crd[0].y, color);
			(crd[1].x += delta.w) && crd[0].x++;
		}
		(crd[1].y += delta.h) && crd[0].y++;
	}
}

void				blit_gan_scaled(t_watsprite *src, SDL_Surface *dst)
{
	t_rect			rsrc;
	t_rect			rdst;

	rsrc = (t_rect){0, 0, src->w, src->h, false};
	rdst.w = src->w * WIDTH / 320;
	rdst.h = src->h * HEIGHT / 200;
	rdst.x = -(WIDTH * src->left_offset / 320);
	rdst.y = -(HEIGHT * src->top_offset / 200);
	while_scale_pic(src, &rsrc, dst, &rdst);
}

void				blit_hud_scaled(t_watsprite *src, SDL_Surface *dst, t_hud *status)
{
	t_rect			rsrc;
	t_rect			rdst;

	rsrc = (t_rect){0, 0, src->w, src->h, false};
	rdst.w = src->w * WIDTH / 320;
	rdst.h = src->h * HEIGHT / 200;
	rdst.x = 0;
	rdst.y = HEIGHT - rdst.h;
	while_scale_pic(src, &rsrc, dst, &rdst);
	(void)status;
}

void				blit_sprite_scale(t_enemy *enemies, t_watsprite *src, SDL_Surface *dst, t_rect *rdst)
{
	t_rect			rsrc;
	uint16_t		size;
	
	
	rsrc = (t_rect){0, 0, src->w, src->h, false};
	size = (int)(HEIGHT / enemies->dist);

	// (int)(HEIGHT * 2 / enemies->dist)


	rdst->w = src->w * size / 32;
	rdst->h = src->h * size / 32;

	// enemies->size = (int)(HEIGHT * 2 / enemies->dist);
	// rdst->x = enemies->shift_x - (src->left_offset * enemies->size / 64);
	rdst->x = enemies->shift_x - src->left_offset * size / 32;
	// rdst->y += src->h * rdst->h / 64 / 4;
	// rdst->y += src->top_offset * (int)(HEIGHT / enemies->dist) / 128;
	
	// HEIGHT / 2 - enemies->size / 2

	rdst->y = HEIGHT / 2 - src->top_offset * size / 32 + size;
	// rdst->y = HEIGHT / 2 - (int)(HEIGHT / enemies->dist) + src->top_offset * (int)(HEIGHT / enemies->dist) / 128;
	// rdst->y = HEIGHT / 2 - enemies->size / 2;
	// rdst->x += 80;
	// rdst->y += 46;	
	while_scale_pic(src, &rsrc, dst, rdst);
}