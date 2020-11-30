/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:39:05 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/30 18:26:13 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

void			read_head_data(const uint8_t *data,
					int offset, t_wad_head *head)
{
	head->wad_type[0] = data[offset];
	head->wad_type[1] = data[offset + 1];
	head->wad_type[2] = data[offset + 2];
	head->wad_type[3] = data[offset + 3];
	head->wad_type[4] = '\0';
	head->dir_count = bytes_to_int(data, offset + 4);
	head->dir_offset = bytes_to_int(data, offset + 8);
}

void			read_dir_data(const uint8_t *data, int offset, t_dir *dir)
{
	dir->lump_offset = bytes_to_int(data, offset);
	dir->lump_size = bytes_to_int(data, offset + 4);
	dir->lump_name[0] = data[offset + 8];
	dir->lump_name[1] = data[offset + 9];
	dir->lump_name[2] = data[offset + 10];
	dir->lump_name[3] = data[offset + 11];
	dir->lump_name[4] = data[offset + 12];
	dir->lump_name[5] = data[offset + 13];
	dir->lump_name[6] = data[offset + 14];
	dir->lump_name[7] = data[offset + 15];
	dir->lump_name[8] = '\0';
}

void			wad_pars_name(const uint8_t *data,
					uint32_t offset, char name[9])
{
	int			i;
	uint32_t	temp_offset;

	i = 0;
	temp_offset = offset;
	while (i < 8)
	{
		name[i] = data[temp_offset];
		temp_offset++;
		i++;
	}
}

void			wad_pars_box(const uint8_t *data,
					uint32_t offset, int16_t box[4])
{
	int			i;
	uint32_t	temp_offset;

	i = 0;
	temp_offset = offset;
	while (i < 4)
	{
		box[i] = bytes_to_short(data, temp_offset);
		temp_offset += 2;
		i++;
	}
}

uint32_t		find_offset_lump(t_dir *dir, char *lable, char *name_map)
{
	t_dir	*temp;

	temp = dir;
	if (name_map != NULL)
		while (temp != NULL && ft_strcmp(name_map, temp->lump_name) != 0)
			temp = temp->next;
	while (temp != NULL && ft_strcmp(lable, temp->lump_name) != 0)
		temp = temp->next;
	if (temp == NULL)
	{
		put_error_sys("Error wadfile - could not find lumpname");
		exit (-1);
	}
	return (temp->lump_offset);
}

uint32_t		find_size_lump(t_dir *dir, char *lable, char *name_map)
{
	t_dir	*temp;

	temp = dir;
	if (name_map != NULL)
		while (temp != NULL && ft_strcmp(name_map, temp->lump_name) != 0)
			temp = temp->next;
	while (temp != NULL && ft_strcmp(lable, temp->lump_name) != 0)
		temp = temp->next;
	if (temp == NULL)
	{
		put_error_sys("Error wadfile - could not find lumpname");
		exit (-1);
	}
	return (temp->lump_size);
}

uint32_t		wad_find_texture(t_dir *dir, char *name)
{
	t_dir		*temp;

	temp = dir;
	while (temp != NULL && ft_strcmp(name, temp->lump_name) != 0)
		temp = temp->next;
	if (temp == NULL)
	{
		put_error_sys("Error wadfile - could not find texture");
		exit (-1);
	}
	return (temp->lump_offset);
}

bool			wad_reader(t_wad *wad)
{
	t_dir		*temp;
	size_t		i;

	i = -1;
	read_head_data(wad->map, 0, &wad->head);
	wad->dir = (t_dir *)ft_memalloc(sizeof(t_dir));
	temp = wad->dir;
	while (++i < wad->head.dir_count)
	{
		read_dir_data(wad->map, wad->head.dir_offset + i * 16, temp);
		if (i + 1 != wad->head.dir_count)
		{
			temp->next = (t_dir *)ft_memalloc(sizeof(t_dir));
			temp = temp->next;
		}
	}
	wad_get_playpal(wad);
	wad_get_colormap(wad);
	wad_get_textures(wad->map, find_offset_lump(wad->dir,
		"TEXTURE1", NULL), &wad->textures1);
	wad_get_textures(wad->map, find_offset_lump(wad->dir,
		"TEXTURE2", NULL), &wad->textures2);
	wad_get_pnames(wad->map, wad->dir, &wad->pname);
	return (true);
}
