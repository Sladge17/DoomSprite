/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_main_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:25:32 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/25 18:43:08 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

void			wad_init_menu(t_wad *wad)
{
	int			i;
	
	wad->menu = (t_wad_menu *)ft_memalloc(sizeof(t_wad_menu));
	wad->menu->background = sprite_create(wad, "TITLEPIC");
	i = -1;
	wad->menu->buttons = (t_wad_sprite **)ft_memalloc(sizeof(t_wad_sprite *));
	wad->menu->buttons[++i] = sprite_create(wad, "M_NGAME");
	wad->menu->buttons[++i] = sprite_create(wad, "M_PAUSE");
	wad->menu->buttons[++i] = sprite_create(wad, "M_ENDGAM");
	wad->menu->buttons[++i] = sprite_create(wad, "M_QUITG");
}

void			wad_draw_menu(SDL_Surface *screen, t_wad *wad)
{
	t_rectf		rect;

	rect = (t_rectf){0, 0, 1, 1};
	blit_sprite_scale(wad->menu->background, screen, rect);
	blit_sprite_scale(wad->menu->buttons[3], screen, rect);
	(void)wad;
}