/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 19:56:54 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/25 18:43:08 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

void				put_column(t_wad *wad, uint32_t offset,
							int x, t_wad_sprite *sprite)
{
	uint16_t		iter;
	uint16_t		col;
	int				y_step;
	int				y_miss;

	y_step = wad->map[offset];
	y_miss = 0;
	col = wad->map[offset + 1];
	iter = 0;
	offset += 3;
	while (y_miss - 1 < sprite->h && wad->map[offset + 1] != 255)
	{
		sprite->pixel[y_step * sprite->w + x] = wad->color[wad->baff]
			[wad->colormap[wad->bright][wad->map[offset]]];
		++iter && ++offset && ++y_miss;
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

t_wad_sprite		*sprite_create(t_wad *wad, char *name)
{
	t_wad_sprite	*sprite;
	t_patch			patch;
	uint32_t		offset;
	int				x;

	if (!(sprite = (t_wad_sprite *)ft_memalloc(sizeof(t_wad_sprite))))
		return (NULL);
	offset = find_offset_lump(wad->dir, name, NULL);
	patch = wad_get_patch_info(wad->map, offset);
	sprite->name = name;
	sprite->h = patch.height;
	sprite->w = patch.width;
	sprite->left_offset = patch.left_offset;
	sprite->top_offset = patch.top_offset;
	sprite->pixel = (uint32_t *)malloc(sizeof(uint32_t) *
		(sprite->w * sprite->h));
	sprite->pixel = ft_memset(sprite->pixel, 0xFFFFFFFF,
		sizeof(uint32_t) * sprite->w * sprite->h);
	x = -1;
	while (++x < patch.width)
		put_column(wad, offset + patch.columnoffset[x], x, sprite);
	wad_destroy_patch(patch);
	return (sprite);
}
