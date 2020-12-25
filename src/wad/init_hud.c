/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 15:54:08 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/25 19:55:15 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

void		destroy_hud(t_wad_hud *hud)
{
	int	i;

	if (hud)
	{
		if (hud->big_digit)
		{
			i = -1;
			while (hud->big_digit[++i])
				free(hud->big_digit[i]);
		}
		if (hud->digit)
		{
			i = -1;
			while (hud->digit[++i])
				free(hud->digit[i]);
		}
		if (hud->stbar->name)
			free(hud->stbar->name);
		if (hud->stbar->pixel)
			free(hud->stbar->pixel);
		free(hud);
		hud = NULL;
	}
}

void		destroi_name(char **name)
{
	int	i;

	if (name)
	{
		i = 0;
		while (i < 10)
		{
			free(name[i]);
			name[i++] = NULL;
		}
		free(name);
		name = NULL;
	}
}

void		*name_digit()
{
	static const char	*name[] = {
		"STTNUM0", "STTNUM1", "STTNUM2", "STTNUM3", "STTNUM4", "STTNUM5",
		"STTNUM6", "STTNUM7", "STTNUM8", "STTNUM9", NULL
	};
	return (name);
}

void		*name_big_digit()
{
	static const char	*name[] = {
		"STYSNUM0", "STYSNUM1", "STYSNUM2", "STYSNUM3", "STYSNUM4", "STYSNUM5",
		"STYSNUM6", "STYSNUM7", "STYSNUM8", "STYSNUM9", NULL
	};
	return (name);
}

void		digit_get(t_wad *wad, char *name, t_wad_sprite *digit)
{
	uint32_t	offset;
	t_patch		patch;
	int			x;

	offset = find_offset_lump(wad->dir, name, NULL);
	patch = wad_get_patch_info(wad->map, offset);
	digit->name = (char *)name;
	digit->h = patch.height;
	digit->w = patch.width;
	digit->left_offset = patch.left_offset;
	digit->top_offset = patch.top_offset;
	digit->pixel = (uint32_t *)malloc(sizeof(uint32_t) *
		(digit->w * digit->h));
	digit->pixel = ft_memset(digit->pixel, 0xFFFFFFFF,
		sizeof(uint32_t) * digit->w * digit->h);
	x = -1;
	while (++x < patch.width)
		put_column(wad, offset + patch.columnoffset[x], x, digit);
	wad_destroy_patch(patch);
}

t_wad_hud	*init_hud(t_wad *wad)
{
	t_wad_hud	*hud;
	char		**name_b;
	char		**name;
	int			i;
	
	hud = (t_wad_hud *)ft_memalloc(sizeof(t_wad_hud));
	hud->stbar = sprite_create(wad, "STBAR");
	hud->big_digit = (t_wad_sprite **)ft_memalloc(sizeof(t_wad_sprite) * 10);
	i = -1;
	while (++i < 10)
		hud->big_digit[i] = (t_wad_sprite *)ft_memalloc(sizeof(t_wad_sprite));
	name_b = name_big_digit();
	i = -1;
	while (++i < 10)
		digit_get(wad, name_b[i], hud->big_digit[i]);
	i = -1;
	hud->digit = (t_wad_sprite **)ft_memalloc(sizeof(t_wad_sprite) * 10);
	while (++i < 10)
		hud->digit[i] = (t_wad_sprite *)ft_memalloc(sizeof(t_wad_sprite));
	name = name_digit();
	i = -1;
	while (++i < 10)
		digit_get(wad, name[i], hud->digit[i]);
	return (hud);
}
