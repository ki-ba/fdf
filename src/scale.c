/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:57:26 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/18 10:11:30 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	@brief populates given int[2] with left and right bounds of the map.
	@brief useful after projection to determine optimal scale.
*/
static void	get_horizontal_bounds(t_map map, int lr[2])
{
	size_t	i;
	size_t	j;
	t_point	cur;

	i = 0;
	lr[0] = INT_MAX;
	lr[1] = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.len)
		{
			cur = (map.map[i][j]);
			if (cur.x < lr[0])
				lr[0] = cur.x;
			if (cur.x > lr[1])
				lr[1] = cur.x;
			++j;
		}
		++i;
	}
}

/*
	@brief populates given int[2] with top and bottom bounds of the map.
	@brief useful after projection to determine optimal scale.
*/
static void	get_vertical_bounds(t_map map, int tb[2])
{
	size_t	i;
	size_t	j;
	t_point	cur;

	i = 0;
	tb[0] = INT_MAX;
	tb[1] = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.len)
		{
			cur = (map.map[i][j]);
			if (cur.y < tb[0])
				tb[0] = cur.y;
			if (cur.y > tb[1])
				tb[1] = cur.y;
			++j;
		}
		++i;
	}
}

/*	@brief determine optimal tile size for printing the given map
	@brief in a 1920 x 1080 window.
*/
size_t	determine_scale(t_map *map)
{
	int		lr[2];
	int		tb[2];
	int		vd;
	int		hd;
	size_t	scale;

	get_vertical_bounds(*map, lr);
	get_horizontal_bounds(*map, tb);
	vd = tb[1] - tb[0];
	hd = lr[1] - lr[0];
	scale = 1;
	while (vd + hd > 0 && scale * hd < 0.7 * WIDTH && scale * hd < 0.7 * HEIGHT)
		++scale;
	if (scale > 50)
		return (50);
	return (scale);
}

/*
	@brief adds half of the window width to the scene x-translation,
	@brief and half of the window height to the scene y-translation.
	@param scene a pointer to the scene to update.
*/
void	center_map(t_scene *scene)
{
	scene->tr[0] += (WIDTH >> 1);
	scene->tr[1] += (HEIGHT >> 1);
}
