/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 08:33:00 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/25 20:04:57 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

void	clear_wad_dir(t_wad_dir *dir)
{
	t_wad_dir	*temp;
	t_wad_dir	*next;

	temp = dir->next;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = NULL;
		temp = next;
	}
	if (dir != NULL)
		free(dir);
}

void	clear_wad_struct(t_wad wad)
{
	free(wad.things);
	free(wad.linedef);
	free(wad.vert);
	free(wad.sidedefs);
	free(wad.segs);
	free(wad.ssectors);
	free(wad.nodes);
	free(wad.sectors);
}

void			wad_destroy_patch(t_patch patch)
{
	if (patch.columnoffset)
		free(patch.columnoffset);
	ft_bzero(&patch, sizeof(patch));
}

int		put_error_sys(char *error)
{
	ft_putendl_fd(error, ERR_FD);
	return (1);
}

bool	put_error_sdl(char *error, const char *error_sdl)
{
	ft_putstr_fd(error, ERR_FD);
	ft_putchar_fd(' ', ERR_FD);
	ft_putendl_fd(error_sdl, ERR_FD);
	return (false);
}
