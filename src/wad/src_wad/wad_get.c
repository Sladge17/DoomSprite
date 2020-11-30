/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 19:49:40 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/30 18:25:33 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

void			wad_get_things(t_wad *wad, char *name_map)
{
	uint32_t 	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	uint16_t	i;

	offset = find_offset_lump(wad->dir, "THINGS", name_map);
	size = find_size_lump(wad->dir, "THINGS", name_map);
	wad->things = (t_things *)ft_memalloc(size / 10 * sizeof(t_things));
	temp_offset = offset + size;
	i = 0;
	while (offset < temp_offset)
	{
		wad->things[i].x = bytes_to_short(wad->map, offset);
		wad->things[i].y = bytes_to_short(wad->map, offset + 2);
		wad->things[i].angle = bytes_to_short(wad->map, offset + 4);
		wad->things[i].type = bytes_to_short(wad->map, offset + 6);
		wad->things[i].flags = bytes_to_short(wad->map, offset + 8);
		offset += 10;
		i++;
	}
	// i = 0;
	// while (i < size / 10)
	// {
	// 	printf("x = %d,\ty = %d,\tyangle = %d,\ttype = %d,\tflags = %d\n",
	// 	wad->things[i].x,
	// 	wad->things[i].y,
	// 	wad->things[i].angle,
	// 	wad->things[i].type,
	// 	wad->things[i].flags);
	// 	i++;
	// }
}

void			wad_get_linedefs(t_wad *wad, char *name_map)
{
	uint32_t 	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	uint16_t	i;

	offset = find_offset_lump(wad->dir, "LINEDEFS", name_map);
	size = find_size_lump(wad->dir, "LINEDEFS", name_map);
	wad->linedef = (t_linedef *)ft_memalloc(size / 14 * sizeof(t_linedef));
	temp_offset = offset + size;
	i = 0;
	while (offset < temp_offset)
	{
		wad->linedef[i].start = bytes_to_short(wad->map, offset);
		wad->linedef[i].finish = bytes_to_short(wad->map, offset + 2);
		wad->linedef[i].flags = bytes_to_short(wad->map, offset + 4);
		wad->linedef[i].type = bytes_to_short(wad->map, offset + 6);
		wad->linedef[i].mark_sector = bytes_to_short(wad->map, offset + 8);
		wad->linedef[i].front = bytes_to_short(wad->map, offset + 10);
		wad->linedef[i].rear = bytes_to_short(wad->map, offset + 12);
		offset += 14;
		i++;
	}
}

void			wad_get_sidedefs(t_wad *wad, char *name_map)
{
	uint32_t	offset;
	uint32_t	temp_offset;
	uint32_t	size;
	uint32_t	i;

	offset = find_offset_lump(wad->dir, "SIDEDEFS", name_map);
	size = find_size_lump(wad->dir, "SIDEDEFS", name_map);
	temp_offset = offset + size;
	wad->sidedefs = (t_sidedef *)ft_memalloc(sizeof(t_sidedef) * size / 30);
	i = 0;
	while (offset < temp_offset)
	{
		wad->sidedefs[i].x = bytes_to_short(wad->map, offset);
		wad->sidedefs[i].y = bytes_to_short(wad->map, offset + 2);
		wad_pars_name(wad->map, offset + 4, wad->sidedefs[i].name_of_up);
		wad_pars_name(wad->map, offset + 12, wad->sidedefs[i].name_of_low);	
		wad_pars_name(wad->map, offset + 20, wad->sidedefs[i].name_of_mid);
		wad->sidedefs[i++].sector = bytes_to_short(wad->map, offset + 28);
		offset += 30;
	}
	// i = 0;
	// while (i < size / 30)
	// {
	// 	printf("x = %d, y = %d, up = %s, low = %s, mid = %s, sector = %d\n",
	// 	wad->sidedefs[i].x, wad->sidedefs[i].y, wad->sidedefs[i].name_of_up,
	// 	wad->sidedefs[i].name_of_low, wad->sidedefs[i].name_of_mid,
	// 	wad->sidedefs[i].sector);
	// 	i++;
	// }
}

void			wad_get_vertex(t_wad *wad, char *name_map)
{
	uint32_t 	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	uint32_t	i;

	i = 0;
	offset = find_offset_lump(wad->dir, "VERTEXES", name_map);
	size = find_size_lump(wad->dir, "VERTEXES", name_map);
	wad->vert = (t_vertex *)ft_memalloc(size / 4 * sizeof(t_vertex));
	temp_offset = offset + size;
	while (offset < temp_offset)
	{
		wad->vert[i].x = bytes_to_short(wad->map, offset);
		wad->vert[i].y = bytes_to_short(wad->map, offset + 2);
		offset += 4;
		i++;
	}
	i = 0;
	while (i < size / 4)
	{
		wad->buf1 = wad->vert[i].x > wad->buf1 ? wad->buf1 : wad->vert[i].x;
		wad->buf2 = wad->vert[i].y < wad->buf2 ? wad->buf2 : wad->vert[i].y;
		i++;
	}
}

void			wad_get_segs(t_wad *wad, char *name_map)
{
	uint32_t	offset;
	uint32_t	temp_offset;
	uint32_t	size;
	uint32_t	i;

	offset = find_offset_lump(wad->dir, "SEGS", name_map);
	size = find_size_lump(wad->dir, "SEGS", name_map);
	temp_offset = size + offset;
	wad->segs = (t_seg *)ft_memalloc(sizeof(t_seg) * size / 12);
	i = 0;
	while (offset < temp_offset)
	{
		wad->segs[i].start_vert = bytes_to_short(wad->map, offset);
		wad->segs[i].finish_vert = bytes_to_short(wad->map, offset + 2);
		wad->segs[i].angle = bytes_to_short(wad->map, offset + 4);
		wad->segs[i].linedef = bytes_to_short(wad->map, offset + 6);
		wad->segs[i].direction = bytes_to_short(wad->map, offset + 8);
		wad->segs[i].offset = bytes_to_short(wad->map, offset + 10);
		offset += 12;
		i++;
	}
	// i = 0;
	// while (i < size / 12)
	// {
	// 	printf("start = %d,\tfinish = %d,\tangle = %d,\tlinedef = %d,\tdir = %d,\toffset = %d\n",
	// 	wad->segs[i].start_vert,
	// 	wad->segs[i].finish_vert,
	// 	wad->segs[i].angle,
	// 	wad->segs[i].linedef,
	// 	wad->segs[i].direction,
	// 	wad->segs[i].offset);
	// 	i++;
	// }
}

void			wad_get_ssectors(t_wad *wad, char *name_map)
{
	uint32_t	offset;
	uint32_t	temp_offset;
	uint32_t	size;
	uint32_t	i;

	offset = find_offset_lump(wad->dir, "SSECTORS", name_map);
	size = find_size_lump(wad->dir, "SSECTORS", name_map);
	temp_offset = offset + size;
	wad->ssectors = (t_ssectors *)ft_memalloc(sizeof(t_ssectors) * size / 4);
	i = 0;
	while (offset < temp_offset)
	{
		wad->ssectors[i].count_seg = bytes_to_short(wad->map, offset);
		wad->ssectors[i].first_seg = bytes_to_short(wad->map, offset + 2);
		offset += 4;
		i++;
	}
	// i = 0;
	// while (i < size / 4)
	// {
	// 	printf("count_seg = %d,\tfirst_seg = %d\n",
	// 	wad->ssectors[i].count_seg,
	// 	wad->ssectors[i].first_seg);
	// 	i++;
	// }
}

void			wad_get_nodes(t_wad *wad, char *map_name)
{
	uint32_t	offset;
	uint32_t	temp_offset;
	uint32_t	size;
	uint32_t	i;

	offset = find_offset_lump(wad->dir, "NODES", map_name);
	size = find_size_lump(wad->dir, "NODES", map_name);
	temp_offset = offset + size;
	wad->nodes = (t_node *)ft_memalloc(size / 28 * sizeof(t_node));
	i = 0;
	while (offset < temp_offset)
	{
		wad->nodes[i].x_sliser = bytes_to_short(wad->map, offset);
		wad->nodes[i].y_sliser = bytes_to_short(wad->map, offset + 2);
		wad->nodes[i].x_sliser2 = bytes_to_short(wad->map, offset + 4);
		wad->nodes[i].y_sliser2 = bytes_to_short(wad->map, offset + 6);
		wad_pars_box(wad->map, offset + 8, wad->nodes[i].right_box);
		wad_pars_box(wad->map, offset + 16, wad->nodes[i].left_box);
		// print_bit(&wad->map[offset + 24]);
		wad->nodes[i].right_baby = bytes_to_short(wad->map, offset + 24);
		wad->nodes[i].left_baby = bytes_to_short(wad->map, offset + 26);
		offset += 28;
		i++;
	}
	// i = 0;
	// while (i < size / 28)
	// {
	// 	printf("x_line %d,\ty_line %d,\t", wad->nodes[i].x_sliser, wad->nodes[i].y_sliser);
	// 	printf("x_line2 %d,\ty_line2 %d,\t", wad->nodes[i].x_sliser2, wad->nodes[i].y_sliser2);
	// 	printf("rigth_box_y_up %d,\trigth_box_y_dwn %d,\t", wad->nodes[i].right_box[0], wad->nodes[i].right_box[1]);
	// 	printf("rigth_box_x_left %d,\trigth_box_x_right %d,\t", wad->nodes[i].right_box[2], wad->nodes[i].right_box[3]);
	// 	printf("left_box_y_up %d,\tleft_box_y_dwn %d,\t", wad->nodes[i].left_box[0], wad->nodes[i].left_box[1]);
	// 	printf("left_box_x_left %d,\tleft_box_x_right %d,\t", wad->nodes[i].left_box[2], wad->nodes[i].left_box[3]);
	// 	printf("right_ch %d, left_ch %d\n", wad->nodes[i].right_baby, wad->nodes[i].left_baby);
	// 	i++;
	// }
}

void			wad_get_sectors(t_wad *wad, char *name_map)
{
	uint32_t	offset;
	uint32_t	temp_offset;
	uint32_t	size;
	uint32_t	i;

	offset = find_offset_lump(wad->dir, "SECTORS", name_map);
	size = find_size_lump(wad->dir, "SECTORS", name_map);
	temp_offset = offset + size;
	wad->sectors = (t_sector *)ft_memalloc(sizeof(t_sector) * size / 26);
	i = 0;
	while (offset < temp_offset)
	{
		wad->sectors[i].hight_flor = bytes_to_short(wad->map, offset);
		wad->sectors[i].hight_cell = bytes_to_short(wad->map, offset + 2);
		wad_pars_name(wad->map, offset + 4, wad->sectors[i].name_of_flor);
		wad_pars_name(wad->map, offset + 12, wad->sectors[i].name_of_cell);
		wad->sectors[i].light = bytes_to_short(wad->map, offset + 20);
		wad->sectors[i].type = bytes_to_short(wad->map, offset + 22);
		wad->sectors[i].tag = bytes_to_short(wad->map, offset + 24);
		offset += 26;
		i++;
	}
	// i = 0;
	// while (i < size / 26)
	// {
	// 	printf("Floor_h = %d,\tcell_h = %d,\tname_floor = %s,\tname_cell = %s,\tlight = %d,\ttupe = %d,\ttag = %d\n",
	// 	wad->sectors[i].hight_flor,
	// 	wad->sectors[i].hight_cell,
	// 	wad->sectors[i].name_of_flor,
	// 	wad->sectors[i].name_of_cell,
	// 	wad->sectors[i].light,
	// 	wad->sectors[i].type,
	// 	wad->sectors[i].tag);
	// 	i++;
	// }
}

t_patch			wad_get_patch_info(const uint8_t *data,	uint32_t offset)
{
	t_patch		patch;
	uint32_t	temp_offset;
	int			i;

	patch.width = bytes_to_short(data, offset);
	patch.height = bytes_to_short(data, offset + 2);
	patch.left_offset = bytes_to_short(data, offset + 4);
	patch.top_offset = bytes_to_short(data, offset + 6);
	patch.columnoffset = (uint32_t *)ft_memalloc(sizeof(uint32_t) *
		patch.width);
	i = 0;
	temp_offset = offset + 8;
	while (i < patch.width)
	{
		patch.columnoffset[i] = bytes_to_int(data, temp_offset);
		temp_offset += 4;
		i++;
	}
	return (patch);
}

void			wad_get_playpal(t_wad *wad)
{
	uint32_t	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	t_point		step;

	offset = find_offset_lump(wad->dir, "PLAYPAL", NULL);
	size = find_size_lump(wad->dir, "PLAYPAL", NULL);
	temp_offset = offset + size;
	step.y = 0;
	while (offset < temp_offset)
	{
		step.x = 0;
		while (step.x < 256)
		{
			wad->color[step.y][step.x] = (wad->map[offset] << 16)
									| (wad->map[offset + 1] << 8)
									| wad->map[offset + 2];
			offset += 3;
			step.x++;
		}
		step.y++;
	}
}

void			wad_get_colormap(t_wad *wad)
{
	uint32_t	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	t_point		step;

	offset = find_offset_lump(wad->dir, "COLORMAP", NULL);
	size = find_size_lump(wad->dir, "COLORMAP", NULL);
	temp_offset = offset + size;
	step.y = 0;
	while (offset < temp_offset)
	{
		step.x = 0;
		while (step.x < 256)
		{
			wad->colormap[step.y][step.x] = wad->map[offset];
			offset += 1;
			step.x++;
		}
		step.y++;
	}
}

void			wad_get_textures(const uint8_t *data, uint32_t offset, t_texture_head *texture)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	temp_offset;

	temp_offset = offset;
	texture->num_texture = bytes_to_int(data, temp_offset);
	temp_offset += 4;
	texture->offsets = (uint32_t *)ft_memalloc(texture->num_texture * (sizeof(uint32_t)));
	i = 0;
	while (i < texture->num_texture)
	{
		texture->offsets[i] = bytes_to_int(data, temp_offset);
		temp_offset += 4;
		i++;
	}
	texture->mtexture = (t_map_texture *)ft_memalloc(sizeof(t_map_texture) * i);
	i = 0;
	while (i < texture->num_texture)
	{
		temp_offset = offset + texture->offsets[i];
		j = 0;
		while(j < 8)
			texture->mtexture[i].name[j++] = data[temp_offset++];
		texture->mtexture[i].name[j] = '\0';
		texture->mtexture[i].masked = bytes_to_short(data, temp_offset + 2);
		texture->mtexture[i].width = bytes_to_short(data, temp_offset + 4);
		texture->mtexture[i].height = bytes_to_short(data, temp_offset + 6);
		texture->mtexture[i].patchcount = bytes_to_short(data, temp_offset + 12);
		texture->mtexture[i].patches = (t_patches *)ft_memalloc(sizeof(t_patches) * texture->mtexture[i].patchcount);
		j = 0;
		temp_offset = temp_offset + 12;
		while (j < texture->mtexture[i].patchcount)
		{
			texture->mtexture[i].patches[j].origin_x = bytes_to_short(data, temp_offset + 2);
			texture->mtexture[i].patches[j].origin_y = bytes_to_short(data, temp_offset + 4);
			texture->mtexture[i].patches[j].patch = bytes_to_short(data, temp_offset + 6);
			texture->mtexture[i].patches[j].stepdir = bytes_to_short(data, temp_offset + 8);
			texture->mtexture[i].patches[j].colormap = bytes_to_short(data, temp_offset + 10);
			temp_offset = temp_offset + 10;
			j++;
		}
		i++;
	}
}

void			wad_get_pnames(const uint8_t *data, t_dir *dir, t_pnames *pname)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	offset;
	uint32_t	temp_offset;
	
	offset = find_offset_lump(dir, "PNAMES", NULL);
	temp_offset = offset;
	i = 0;
	pname->num_map_patches = bytes_to_int(data, temp_offset);
	pname->name = (char **)ft_memalloc(sizeof(char *) * pname->num_map_patches);
	while (i < pname->num_map_patches)
		pname->name[i++] = (char *)ft_memalloc(sizeof(char) * 9);
	i = 0; 
	temp_offset += 4;
	while (i < pname->num_map_patches)
	{
		j = 0;
		while (j < 8)
			pname->name[i][j++] = data[temp_offset++];
		i++;
	}
}
