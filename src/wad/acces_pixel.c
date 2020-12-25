/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acces_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:10:36 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/25 20:04:13 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

Uint32				get_pixel(SDL_Surface *surface, int x, int y)
{
	register int	bpp;
	register Uint8	*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	if (bpp == 2)
		return (*(Uint16 *)p);
	if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	if (bpp == 4)
		return (*(Uint32 *)p);
	return (0);
}

uint32_t			get_pixel_sprite(t_wad_sprite *sprite, int x, int y)
{
	if (x > sprite->w || x < 0 || y > sprite->h || y < 0)
		exit(put_error_sys("Error pixel access"));
	return (sprite->pixel[y * sprite->w + x]);
}

void				putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int				bpp;
	Uint8			*p;

	if (x > 0 && x < WIDTH_WIN && y > 0 && y < HEIGHT_WIN)
	{
		bpp = surface->format->BytesPerPixel;
		p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		if (bpp == 1)
			*p = pixel;
		if (bpp == 2)
			*(Uint16 *)p = pixel;
		else if (bpp == 3)
		{
			p[0] = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ?
				(pixel >> 16) & 0xff : pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ?
				pixel & 0xff : (pixel >> 16) & 0xff;
		}
		else if (bpp == 4)
			*(Uint32 *)p = pixel;
	}
}

// t_color				color32_to_8(Uint32 color)
// {
// 	t_color			color8;

// 	color8.red = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ?
// 		(color >> 16) & 0xff : color & 0xff;
// 	color8.green = (color >> 8) & 0xff;
// 	color8.blue = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ?
// 		color & 0xff : (color >> 16) & 0xff;
// 	return (color8);
// }

// Uint32				color8_to_32(t_color color)
// {
// 	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
// 		return (color.red << 16 | color.green << 8 | color.blue);
// 	else
// 		return (color.red | color.green << 8 | color.blue << 16);
// }

void				clear_surface(SDL_Surface *surface, Uint32 color)
{
	SDL_LockSurface(surface);
	SDL_memset(surface->pixels, color, surface->h * surface->pitch);//ВАЖНО
	SDL_UnlockSurface(surface);
}
