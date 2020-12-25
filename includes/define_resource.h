/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_resource.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:07:49 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/12 20:03:48 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_RESOURCE_H
# define DEFINE_RESOURCE_H

# define IMG_TEST "resource/textures/test.bmp"
# define IMG_CURS0 "resource/textures/cursors/cur_hand.bmp"
# define IMG_IRON "resource/textures/ract_iron.bmp"
# define IMG_ICON "resource/textures/icon.bmp"
# define IMG_EDITHOR_BACK "resource/textures/editor_back.bmp"
# define IMG_TEST2 "resource/textures/sw2cmt.bmp"

# define FONT_BUTTON "resource/font/button.otf"
# define FONT_TEXT "resource/font/robotron.otf"

# define NAME_WIN "Doom-Nukem (by Bdrinkin & Jthuy & Vneelix && Nsena)"

# define WIDTH_WIN 1024
# define HEIGHT_WIN 768
# define HALF_WIDTH WIDTH_WIN / 2
# define HALF_HEIGHT HEIGHT_WIN / 2
# define HALF_R_WIDTH HALF_WIDTH
# define HALF_R_HEIGHT (HEIGHT_WIN - HEIGHT_WIN * 0.155) / 2
# define SCALING_W(a) a * WIDTH_WIN / 320
# define SCALING_H(a) a * HEIGHT_WIN / 200

# include "sprite_kit.h"

typedef enum		e_texture
{
	texture_icon,
	texture_cursor0,
	texture_test,
	texture_iron,
	texture_test2,
	texture_editor_back,
	texture_total
}					t_texture;

typedef enum		e_font
{
	font_button,
	font_text,
	font_total
}					t_font;

#endif
