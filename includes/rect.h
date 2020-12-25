/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:22:43 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/12 13:18:41 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECT_H
# define RECT_H

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_pointf
{
	double			x;
	double			y;
}					t_pointf;

typedef struct		s_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
}					t_rect;

typedef struct		s_rectf
{
	double			x;
	double			y;
	double			w;
	double			h;
}					t_rectf;

typedef struct		s_limit
{
	int				cur;
	int				max;
	int				min;
}					t_limit;

typedef struct		s_limit_f
{
	double			cur;
	double			max;
	double			min;
}					t_limit_f;

typedef struct			s_crd
{
	int					x;
	int					*y;
}						t_crd;

void					fill_limit(t_limit *data, int min, int cur, int max);
void					fill_limit_f(t_limit_f *data, float min,
							float cur, float max);

#endif