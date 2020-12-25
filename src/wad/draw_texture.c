/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:06:35 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/25 19:54:06 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

// void			wad_compose_texture(t_doom *doom, t_map_texture pth,
// 					t_point start, SDL_Surface *surface)
// {
// 	int32_t		x, y;
// 	uint32_t	offset;
// 	uint32_t	temp_offset;
// 	uint32_t	i;
// 	t_patch		patch;
// 	uint16_t	x_temp, y_temp;

// 	i = 0;
// 	while (i < pth.patchcount)
// 	{
// 		offset = find_offset_lump(doom->wad.dir,
// 			doom->wad.pname.name[pth.patches[i].patch], NULL);
// 		patch = wad_get_patch_info(doom->wad.map, offset);
// 		doom->wad.temp_step = pth.height;
// 		x = (pth.patches[i].origin_x <= 0) ? start.x
// 			: start.x + pth.patches[i].origin_x;
// 		x_temp = x;
// 		while (x < patch.width + x_temp && x < pth.width + start.x)
// 		{
// 			temp_offset = offset + patch.columnoffset[x - x_temp];
// 			y = (pth.patches[i].origin_y <= 0) ? start.y
// 				: start.y + pth.patches[i].origin_y;
// 			y_temp = y;
// 			while (y < patch.height + y_temp && y < pth.height + start.y)
// 				temp_offset = rec_column(doom, temp_offset, (t_crd){x, &y}, surface);
// 			x++;
// 		}
// 		i++;
// 	}
// }


// SDL_Surface		*wad_draw_texture(t_doom *doom, t_point start, char *texture)
// {
// 	uint32_t	i;
// 	SDL_Surface	*ret;

// 	i = 0;
// 	if (texture == NULL)
// 		exit(put_error_sys("Enter texture name") - 1);
// 	while (i < doom->wad.textures1.num_texture &&
// 		ft_strcmp(doom->wad.textures1.mtexture[i].name, texture) != 0)
// 		i++;
// 	if (i >= doom->wad.textures1.num_texture)
// 	{
// 		i = 0;
// 		while (i < doom->wad.textures2.num_texture &&
// 			ft_strcmp(doom->wad.textures2.mtexture[i].name, texture) != 0)
// 			i++;
// 		if (i >= doom->wad.textures2.num_texture)
// 			exit(put_error_sys("Error WAD - could not find texture") * -1);
// 		ret = SDL_CreateRGBSurfaceWithFormat(0,
// 			doom->wad.textures2.mtexture[i].width,
// 			doom->wad.textures2.mtexture[i].height, 32, SDL_PIXELFORMAT_RGBA32);
// 		wad_compose_texture(doom, doom->wad.textures2.mtexture[i], start, ret);
// 	}
// 	else
// 	{
// 		ret = SDL_CreateRGBSurfaceWithFormat(0,
// 			doom->wad.textures1.mtexture[i].width,
// 			doom->wad.textures1.mtexture[i].height, 32, SDL_PIXELFORMAT_RGBA32);
// 		wad_compose_texture(doom, doom->wad.textures1.mtexture[i], start, ret);
// 	}
// 	return (ret);	
// }
