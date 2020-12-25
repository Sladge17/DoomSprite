/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ppower.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:22:36 by jthuy             #+#    #+#             */
/*   Updated: 2019/09/21 16:22:40 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_ppower(int number, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (number == 0)
		return (0);
	if (power == 1)
		return (number);
	return (ft_ppower(number, power - 1) * number);
}
