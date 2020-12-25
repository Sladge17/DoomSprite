/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:48:05 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/25 18:26:59 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

void		if_rect(SDL_Surface *src, t_rect *rsrc,
			SDL_Surface *dst, t_rect *rdst)
{
	if (rsrc == NULL)
		rsrc = &(t_rect){.w = src->w, .h = src->h};
	if (rdst == NULL)
		rdst = &(t_rect){.w = dst->w, .h = dst->h};
}

void		fill_limit_f(t_limit_f *data, float min, float cur, float max)
{
	data->min = min;
	data->cur = (cur <= min) ? min : (cur >= max) ? max : cur;
	data->max = max;
}

void		fill_limit(t_limit *data, int min, int cur, int max)
{
	data->min = min;
	data->cur = (cur <= min) ? min : (cur >= max) ? max : cur;
	data->max = max;
}
