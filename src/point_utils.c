/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:19:22 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/18 10:05:29 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	@brief returns a t_point with given properties.
	@param x the position on x axis
	@param y the position on y axis
	@param z the position on z axis
	@param color of the point
*/

t_point	create_point(double x, double y, double z, int color)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.px = x;
	point.py = y;
	point.pz = z;
	point.color = color;
	return (point);
}

/*
	@brief applies scene translation to given point.
	@param point pointer to the t_point to update.
*/
void	apply_translation(t_scene scene, t_point *point)
{
	point->px += scene.tr[0];
	point->py += scene.tr[1];
	point->pz += scene.tr[2];
}

/*
	@brief applies scene extrusion to given point.
	@param point pointer to the t_point to update.
	@param min zvalue of the lowest point in origin map (extrusion
	@param min applies to the high points)
*/
void	apply_extrusion(t_scene scene, t_point *point, double min)
{
	if (point->z > min)
		point->pz += fabs(point->pz - min) * scene.ext;
}

/*
	@brief returns the z-value of the lowest point on the map.
	@param map pointer to the map to parse
	@returns the lowest altitude present on the map.
*/
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

/*
	@brief returns the z-value of the highest point on the map.
	@param map pointer to the map to parse
	@returns the highest altitude present on the map.
*/
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
