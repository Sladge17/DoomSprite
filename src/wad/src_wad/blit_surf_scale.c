/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_surf_scale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:03:55 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/30 19:11:23 by jthuy            ###   ########.fr       */
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

static void			while_scale_pic(SDL_Surface *src, t_rect *rsrc,
					SDL_Surface *dst, t_rect *rdst)
{
	t_pointf		crd[2];
	t_rectf			delta;
	Uint32			color;

	delta = check_scale_delta(rdst, rsrc);
	crd[0].y = rdst->y;
	crd[1].y = rsrc->y;
	while (crd[0].y < rdst->h || crd[0].y < rdst->y + rdst->h)
	{
		crd[0].x = rdst->x;
		crd[1].x = rsrc->x;
		while (crd[0].x < rdst->w || crd[0].x < rdst->x + rdst->w)
		{
			color = get_pixel(src, crd[1].x, crd[1].y);
			putpixel(dst, crd[0].x, crd[0].y, color);
			crd[1].x += delta.w;
			crd[0].x++;
		}
		crd[1].y += delta.h;
		crd[0].y++;
	}
}

void				blit_surf_scaled(SDL_Surface *src, t_rect *rsrc,
					SDL_Surface *dst, t_rect *rdst)
{
	t_rect			tmp_rsrc;
	t_rect			tmp_rdst;

	if (rsrc == NULL)
		tmp_rsrc = (t_rect){0, 0, src->w, src->h, false};
	if (rdst == NULL)
		tmp_rdst = (t_rect){0, 0, dst->w, dst->h, false};
	while_scale_pic(src, rsrc != NULL ? rsrc : &tmp_rsrc,
		dst, rdst != NULL ? rdst : &tmp_rdst);
}
