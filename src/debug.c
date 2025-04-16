/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:20:55 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/15 17:49:29 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_full_map(t_map *map)
{
	size_t	i;
	size_t	j;
	t_point	p;

	i = 0;
	j = 0;
	while (i < map->h_capacity)
	{
		j = 0;
		while (j < map->len)
		{
			p = map->map[i][j];
			if (i < map->height)
				ft_printf("[%d, %d, %d, %d]", (int)p.px, (int)p.py, (int)p.pz, p.color);
			else
				ft_printf("[x, x, x]");
			if (j < map->len - 1)
				ft_printf(" ");
			++j;
		}
		++i;
		ft_printf("\n");
	}
	ft_printf("\nmap capacity :	%d	rows\noccupied :	%d	rows\n", map->h_capacity, map->height);
	ft_printf("\nmap is :		%d * %d\n", map->height, map->len);
}

void	print_actions(t_scene scene)
{
	printf("rot : {%.2f, %.2f, %.2f}\n", scene.rot[0], scene.rot[1], scene.rot[2]);
	printf("tr  : {%.2f, %.2f, %.2f}\n", scene.tr[0], scene.tr[1], scene.tr[2]);
	printf("ext : %d\n", scene.ext);
	printf("scale: %zu\n", scene.scale);
}
