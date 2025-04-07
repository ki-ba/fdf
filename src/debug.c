/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:20:55 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/03 16:28:36 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_full_map(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ft_printf("\n\n===== FULL MAP =====\n\n");
	while (i < map->h_capacity)
	{
		j = 0;
		while (j < map->len)
		{
			if (i < map->height)
				ft_printf("[%d, %d, %d]", (int)round(map->map[i][j].px), (int)round(map->map[i][j].py), (int)round(map->map[i][j].pz));
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
	ft_printf("\n\n====================\n\n");
}

void	print_actions(t_scene scene)
{
	printf("rot : {%.2f, %.2f, %.2f}\n", scene.rot[0], scene.rot[1], scene.rot[2]);
	printf("tr  : {%.2f, %.2f, %.2f}\n", scene.tr[0], scene.tr[1], scene.tr[2]);
	printf("scale: %zu\n", scene.scale);
}
