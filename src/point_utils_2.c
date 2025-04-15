/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:49:45 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/15 16:49:51 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	get_minimum(t_map *map)
{
	size_t		i;
	size_t		j;
	double		min;

	min = INT_MAX;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->len)
		{
			if (map->map[i][j].z < min)
				min = map->map[i][j].z;
			++j;
		}
		++i;
	}
	return (min);
}

double	get_maximum(t_map *map)
{
	size_t		i;
	size_t		j;
	double		max;

	max = INT_MIN;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->len)
		{
			if (map->map[i][j].z > max)
				max = map->map[i][j].z;
			++j;
		}
		++i;
	}
	return (max);
}
