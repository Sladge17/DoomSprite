/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 08:33:00 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/30 19:11:55 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

void	clear_wad_dir(t_dir *dir)
{
	t_dir	*temp;
	t_dir	*next;

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

// void	doom_exit(t_doom *doom)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < texture_total)
// 		if (doom->sdl.textures[i] != NULL)
// 			SDL_FreeSurface(doom->sdl.textures[i]);
// 	if (doom->sdl.surface != NULL)
// 		SDL_FreeSurface(doom->sdl.surface);
// 	if (doom->sdl.window != NULL)
// 		SDL_DestroyWindow(doom->sdl.window);
// 	i = -1;
// 	while (++i < font_total)
// 		if (doom->sdl.fonts[i] != NULL)
// 			TTF_CloseFont(doom->sdl.fonts[i]);
// 	// clear_wad_dir(doom->wad.dir);
// 	// clear_wad_struct(doom->wad);
// 	if (doom->wad.map != NULL)
// 		free(doom->wad.map);
// 	free_editor(doom->screen);
// 	IMG_Quit();
// 	TTF_Quit();
// 	SDLNet_Quit();
// 	Mix_Quit();
// 	SDL_Quit();
// 	if (doom != NULL)
// 		free(doom);
// }

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
