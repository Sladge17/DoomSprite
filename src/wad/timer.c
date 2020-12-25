/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:15:36 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/25 18:46:54 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

bool		time_started(t_timer *time)
{
	if (!time_is_started(time))
	{
		timer_start(time);
		return (true);
	}
	return (false);
}

void		time_update(t_timer *time)
{
	timer_stop(time);
	timer_start(time);
}

void		fps_counter(t_timer *time)
{
	if (get_ticks(time) >= 1000)
	{
		ft_putstr("FPS: ");
		ft_putnbr(time->counted_frames);
		ft_putchar('\n');
		time_update(time);
		time->counted_frames = 0;
	}
	else
		time->counted_frames++;
}
