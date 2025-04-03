/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:57:26 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/01 20:13:31 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdint.h>

void	get_horizontal_bounds(t_map map, int lr[2])
{
	size_t		i;
	t_matrix	cur;

	i = 0;
	lr[0] = INT_MAX;
	lr[1] = 0;
	while (i < map.height * map.len)
	{
		cur = (map.map[i]);
		if (cur.m[X] < lr[0])
			lr[0] = (int)round(cur.m[X]);
		if (cur.m[X] > lr[1])
			lr[1] = (int)round(cur.m[X]);
		++i;
	}
}

void	get_vertical_bounds(t_map map, int tb[2])
{
	size_t		i;
	t_matrix	cur;

	i = 0;
	tb[0] = INT_MAX;
	tb[1] = 0;
	while (i < map.height * map.len)
	{
		(void)map;
		cur = (map.map[i]);
		if (cur.m[Y] < tb[0])
			tb[0] = (int)round(cur.m[Y]);
		if (cur.m[Y] > tb[1])
			tb[1] = (int)round(cur.m[Y]);
		++i;
	}
}

/* determine optimal tile size for printing the given map
 * in a 1920 x 1080 window. */
int	determine_scale(t_map *map)
{
	int	lr[2];
	int	tb[2];
	int	i;

	ft_printf("map is %d x %d\n", map->len, map->height);
	get_vertical_bounds(*map, lr);
	get_horizontal_bounds(*map, tb);
	ft_printf("left : %dpx\nright : %dpx\ntop: %dpx\nbot: %dpx\n", lr[0], lr[1], tb[0], tb[1]);
	i = 2;
	while (i * lr[1] < 0.8 * WIDTH && i * tb[1] < 0.8 * HEIGHT)
	{
		ft_printf("\n\n === SCALE = %d === \n\n", i);
		ft_printf("left : %dpx\nright : %dpx\ntop: %dpx\nbot: %dpx\n", i * lr[0], i * lr[1], i * tb[0], i * tb[1]);
		++i;
	}
	return (i - 1);
}

t_matrix	get_center(t_map map)
{
	int			tb[2];
	int			lr[2];
	t_matrix	center;

	get_vertical_bounds(map, tb);
	get_horizontal_bounds(map, lr);
	center.m[X] = (lr[1] - lr[0]) / 2;
	center.m[Y] = (tb[1] - tb[0]) / 2;
	return (center);
}

t_matrix	center_point(t_map map, t_matrix point)
{
	t_matrix	center;
	t_matrix	point2;

	center = get_center(map);
	/*ft_printf("center of map is %d, %d\n", center.x, center.y);*/
	point2.m[X] = point.m[X] + (WIDTH / 2 - center.m[X]);
	point2.m[Y] = point.m[Y] + (HEIGHT / 2 - center.m[Y]);
	point2.m[Z] = point.m[Z];
	return (point2);
}

void	scale_map(t_map *map)
{
	size_t	scale;
	size_t	i;

	i = 0;
	scale = determine_scale(map);
	while (i < map->len * map->height)
	{
		map->map[i].m[X] *= scale;
		map->map[i].m[Y] *= scale;
		map->map[i].m[Z] *= scale;
		++i;
	}
}
