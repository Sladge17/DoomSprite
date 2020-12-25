/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_sprite_scale.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:03:55 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/25 18:22:36 by jthuy            ###   ########.fr       */
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

static void			while_scale_pic(t_wad_sprite *src, t_rect *rsrc,
					SDL_Surface *dst, t_rect *rdst)
{
	t_pointf		screen;
	t_pointf		pixel;
	t_rectf			delta;
	Uint32			color;

	delta = check_scale_delta(rdst, rsrc);
	screen.y = rdst->y;
	pixel.y = rsrc->y;
	while (pixel.y < rsrc->h || screen.y < rdst->y + rdst->h)
	{
		screen.x = rdst->x;
		pixel.x = rsrc->x;
		while (pixel.x < rsrc->w || screen.x < rdst->x + rdst->w)
		{
			color = get_pixel_sprite(src, pixel.x, pixel.y);
			if (color == 0xFFFFFFFF)
			{
				(pixel.x += delta.w) && screen.x++;
				continue ;
			}
			putpixel(dst, screen.x, screen.y, color);
			(pixel.x += delta.w) && screen.x++;
		}
		(pixel.y += delta.h) && screen.y++;
	}
}

void				blit_sprite_scale(t_wad_sprite *src, SDL_Surface *dst,
						t_rectf rdst)
{
	t_rect			rsrc;
	t_rect			rdst_temp;

	rdst_temp.w = SCALING_W(src->w) * rdst.w;
	rdst_temp.h = SCALING_H(src->h) * rdst.h;
	rdst_temp.x = rdst.x - SCALING_W(src->left_offset);
	rdst_temp.y = rdst.y - SCALING_H(src->top_offset);
	rsrc = (t_rect){0, 0, src->w, src->h};
	while_scale_pic(src, &rsrc, dst, &rdst_temp);
}

void				blit_sprite_scaled(t_wad_sprite *src, SDL_Surface *dst, t_sub_sprite sub)
{
	t_rect			rsrc;
	t_rect			rdst_temp;

	rdst_temp.w = SCALING_W(src->w) * sub.dist;
	rdst_temp.h = SCALING_H(src->h) * sub.dist;
	rdst_temp.x = sub.origin.x - SCALING_W(src->left_offset) * sub.dist;
	rdst_temp.y = sub.origin.y - SCALING_H(src->top_offset) * sub.dist;
	rsrc = (t_rect){0, 0, src->w, src->h};
	while_scale_pic(src, &rsrc, dst, &rdst_temp);
}

void				blit_gan_scaled(t_wad_sprite *src, SDL_Surface *dst)
{
	t_rect			rsrc;
	t_rect			rdst;

	rsrc = (t_rect){0, 0, src->w, src->h};
	rdst.w = SCALING_W(src->w);
	rdst.h = SCALING_H(src->h);
	rdst.x = -(SCALING_W(src->left_offset));
	rdst.y = -(SCALING_H(src->top_offset));
	while_scale_pic(src, &rsrc, dst, &rdst);
}

void				blit_hud_scaled(t_wad_sprite *src, SDL_Surface *dst)
{
	t_rect			rsrc;
	t_rect			rdst;

	rsrc = (t_rect){0, 0, src->w, src->h};
	rdst.w = SCALING_W(src->w);
	rdst.h = SCALING_H(src->h);
	rdst.x = 0;
	rdst.y = HEIGHT_WIN - rdst.h;
	while_scale_pic(src, &rsrc, dst, &rdst);
}
