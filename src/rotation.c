/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:01:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/03 14:43:01 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_map(t_map *map, double a, t_point (*r_f)(t_point pt, double a))
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->len)
		{
			map->map[i][j] = r_f(map->map[i][j], a);
			++j;
		}
		++i;
	}
}

t_point	rotate_x(t_point p0, double a)
{
	t_point	p1;

	p1.x = p0.x;
	p1.y = p0.y * cos(a) - p0.z * sin(a);
	p1.z = p0.y * sin(a) + p0.z * cos(a);
	return (p1);
}

t_point	rotate_y(t_point p0, double a)
{
	t_point	p1;

	p1.x = p0.x * cos(a) - p0.z * sin(a);
	p1.y = p0.y;
	p1.z = p0.x * sin(a) + p0.z * cos(a);
	return (p1);
}

t_point	rotate_z(t_point p0, double a)
{
	t_point	p1;

	p1.x = p0.x * cos(a) - p0.y * sin(a);
	p1.y = p0.x * sin(a) + p0.y * cos(a);
	p1.z = p0.z;
	return (p1);
}
