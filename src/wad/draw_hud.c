/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 15:52:34 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/10 20:22:51 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"
#define RANG_HEALTH 0.3001
#define RANG_AMMO 0.1351
#define RANG_FACE 0.554
#define RANG_SHIELD 0.7
#define RANG_ALL_AMMO_MAX 0.9788
#define RANG_ALL_AMMO_CUR 0.8988

static void	hud_draw_number(SDL_Surface *screen, t_wad_sprite **number,
				int cur, t_rectf rect)
{
	t_rectf	rect_tmp;
	int		i;

	rect_tmp = rect;
	i = cur;
	if (cur == 0)
	{
		rect_tmp.y = rect.y - SCALING_H(number[i]->h) / 1.5;
		rect_tmp.x -= SCALING_W(number[i]->w);
		blit_sprite_scale(number[i], screen, rect_tmp);
	}
	while (cur != 0)
	{
		i = cur % 10;
		cur /= 10;
		rect_tmp.y = rect.y - SCALING_H(number[i]->h) / 1.5;
		rect_tmp.x -= SCALING_W(number[i]->w);
		blit_sprite_scale(number[i], screen, rect_tmp);
	}
}

static void	draw_max_ammo(SDL_Surface *screen, t_wad_hud *hud,
				t_wad_player status, t_rectf rect)
{
	int		hud_h;
	int		hud_w;

	hud_h = SCALING_H(hud->stbar->h);
	hud_w = SCALING_W(hud->stbar->w);
	rect.x = hud_w * RANG_ALL_AMMO_MAX;
	rect.y = HEIGHT_WIN - hud_h / 5.5 * 1;
	hud_draw_number(screen, hud->big_digit, status.ammo[3].max, rect);
	rect.y = HEIGHT_WIN - (hud_h / 5.5) * 2;
	hud_draw_number(screen, hud->big_digit, status.ammo[2].max, rect);
	rect.y = HEIGHT_WIN - (hud_h / 5.5) * 3;
	hud_draw_number(screen, hud->big_digit, status.ammo[1].max, rect);
	rect.y = HEIGHT_WIN - (hud_h / 5.5) * 4;
	hud_draw_number(screen, hud->big_digit, status.ammo[0].max, rect);
}

static void	draw_cur_ammo(SDL_Surface *screen, t_wad_hud *hud,
				t_wad_player status, t_rectf rect)
{
	int		hud_h;
	int		hud_w;

	hud_h = SCALING_H(hud->stbar->h);
	hud_w = SCALING_W(hud->stbar->w);
	rect.x = hud_w * RANG_ALL_AMMO_CUR;
	rect.y = HEIGHT_WIN - hud_h / 5.5 * 1;
	hud_draw_number(screen, hud->big_digit, status.ammo[3].cur, rect);
	rect.y = HEIGHT_WIN - (hud_h / 5.5) * 2;
	hud_draw_number(screen, hud->big_digit, status.ammo[2].cur, rect);
	rect.y = HEIGHT_WIN - (hud_h / 5.5) * 3;
	hud_draw_number(screen, hud->big_digit, status.ammo[1].cur, rect);
	rect.y = HEIGHT_WIN - (hud_h / 5.5) * 4;
	hud_draw_number(screen, hud->big_digit, status.ammo[0].cur, rect);
}

void		draw_hud(SDL_Surface *screen, t_wad_hud *hud, t_wad_player status)
{
	t_rectf	rect;
	int		hud_h;
	int		hud_w;

	blit_hud_scaled(hud->stbar, screen);
	hud_h = SCALING_H(hud->stbar->h);
	hud_w = SCALING_W(hud->stbar->w);
	rect = (t_rectf){hud_w * RANG_HEALTH, HEIGHT_WIN - hud_h / 2, 1, 1};
	hud_draw_number(screen, hud->digit, status.health.cur, rect);
	rect.x = hud_w * RANG_AMMO;
	hud_draw_number(screen, hud->digit, status.ammo[status.cur_gan].cur, rect);
	rect.x = hud_w * RANG_SHIELD;
	hud_draw_number(screen, hud->digit, status.shield.cur, rect);
	draw_max_ammo(screen, hud, status, rect);
	draw_cur_ammo(screen, hud, status, rect);
}
