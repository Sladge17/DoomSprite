/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:15:36 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/11 18:01:49 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

Uint32		get_ticks(t_timer *time)
{
	Uint32	time_temp;

	time_temp = 0;
	if (time->started)
	{
		if (time->paused)
			time_temp = time->paused_ticks;
		else
			time_temp = SDL_GetTicks() - time->start_ticks;
	}
	return (time_temp);
}

bool		time_is_started(t_timer *time)
{
	return (time->started);
}

bool		time_is_paused(t_timer *time)
{
	return (time->paused);
}

void		fps_counter(t_timer *time)
{
	if (get_ticks(time) >= 1000)
	{
		timer_stop(time);
		ft_putstr("FPS: ");
		ft_putnbr(time->counted_frames);
		ft_putchar('\n');
		timer_start(time);
		time->counted_frames = 0;
	}
	else
		time->counted_frames++;
}
