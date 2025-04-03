/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:20:55 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/27 13:13:13 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	print_full_map(t_map *map)
{
	size_t	i;

	i = 0;
	ft_printf("\n\n===== FULL MAP =====\n\n");
	while (i < map->capacity)
	{
		ft_printf("%d", map->map[i].z);
		if (++i % (map->len) == 0)
			ft_printf("\n");
		else
			ft_printf("	");
	}
	ft_printf("\nmap capacity :	%d	t_points\noccupied :	%d	t_points\n", map->capacity, map->len * map->height);
	ft_printf("\n\n====================\n\n");
}
