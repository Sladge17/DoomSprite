/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:29:58 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/25 18:43:08 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

void	wad_init_level(t_wad *wad, char *name_map)
{
	wad_get_things(wad, name_map);
	wad_get_linedefs(wad, name_map);
	wad_get_sidedefs(wad, name_map);
	wad_get_vertex(wad, name_map);
	wad_get_segs(wad, name_map);
	wad_get_ssectors(wad, name_map);
	wad_get_nodes(wad, name_map);
	wad_get_sectors(wad, name_map);
}

void	*def_name(void)
{
	static const char *names[] = {
		"POSSA1", "POSSA2A8", "POSSA3A7", "POSSA4A6", "POSSA5", "POSSB1",
		"POSSB2B8", "POSSB3B7", "POSSB4B6", "POSSB5", "POSSC1", "POSSC2C8",
		"POSSC3C7", "POSSC4C6", "POSSC5", "POSSD1",	"POSSD2D8", "POSSD3D7",
		"POSSD4D6", "POSSD5", "POSSE1", "POSSE2E8", "POSSE3E7", "POSSE4E6",
		"POSSE5", "POSSF1", "POSSF2F8", "POSSF3F7", "POSSF4F6", "POSSF5",
		"POSSG1", "POSSG2G8", "POSSG3G7", "POSSG4G6", "POSSG5", "POSSH0",
		"POSSI0", "POSSJ0", "POSSK0", "POSSL0", "TROOE1", "TROOE2E8",
		"TROOE3E7", "TROOE4E6", "TROOE5", "TROOA1", "TROOA2A8", "TROOA3A7",
		"TROOA4A6", "TROOA5", "TROOB1", "TROOB2B8", "TROOB3B7", "TROOB4B6",
		"TROOB5", "TROOC1", "TROOC2C8", "TROOC3C7", "TROOC4C6", "TROOC5",
		"TROOC1", "TROOC2C8", "TROOC3C7", "TROOC4C6","TROOC5", "TROOG1",
		"TROOG2G8", "TROOG3G7", "TROOG4G6", "TROOG5", "TROOH1", "TROOH2H8",
		"TROOH3H7", "TROOH4H6", "TROOH5", "TROOI0", "TROOJ0", "TROOK0",
		"TROOL0", "TROOM0", "PISGA0", "PISGB0", "PISGC0", "PISGD0", "PISGE0",
		"PISFA0", "SHTGA0", "SHTGB0", "SHTGC0", "SHTGD0", "SHTFA0", "SHTFB0",
		NULL
	};
	return (names);
}

t_wad_sprite	**fill_sprites(int def_sprt, char **name, t_wad *wad)
{
	int				i;
	t_wad_sprite	**sprites;

	i = -1;
	sprites = ft_memalloc(sizeof(t_wad_sprite *) * (def_sprt));
	while (++i <= def_sprt)
		sprites[i] = (t_wad_sprite *)ft_memalloc(sizeof(t_wad_sprite));
	i = -1;
	while (++i < def_sprt)
		sprites[i] = sprite_create(wad, name[i]);
	sprites[i] = NULL;
	return (sprites);
}

t_wad	*init_wad(char *av)
{
	t_wad	*wad;

	wad = (t_wad *)ft_memalloc(sizeof(t_wad));
	wad_loader(wad, av);
	wad_reader(wad);
	wad_init_level(wad, "E1M1");
	wad_init_menu(wad);
	wad->name = def_name();
	wad->hud = init_hud(wad);
	wad->sprites = fill_sprites(sprt_total, wad->name, wad);
	return (wad);
}
