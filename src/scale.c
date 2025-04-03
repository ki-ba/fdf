/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:57:26 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/03 16:43:03 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stddef.h>
#include <stdint.h>

void	get_horizontal_bounds(t_map map, int lr[2])
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

void	get_vertical_bounds(t_map map, int tb[2])
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

/* determine optimal tile size for printing the given map
 * in a 1920 x 1080 window. */
size_t	determine_scale(t_map *map)
{
	int		lr[2];
	int		tb[2];
	size_t	scale;

	ft_printf("map is %d x %d\n", map->len, map->height);
	get_vertical_bounds(*map, lr);
	get_horizontal_bounds(*map, tb);
	ft_printf("right : %dpx\nbot: %dpx\n", lr[1], tb[1]);
	scale = 1;
	while (scale * lr[1] < 0.7 * WIDTH && scale * tb[1] < 0.7 * HEIGHT)
	{
		ft_printf("\n\n === SCALE = %d === \n\n", scale);
		ft_printf("right : %dpx\nbot: %dpx\n", scale * lr[1], scale * tb[1]);
		++scale;
	}
	ft_printf("\n\n\nFINAL SCALE = %d\nright : %dpx\bot: %dpx\n", scale, scale * lr[1], scale * tb[1]);
	return (scale);
}

void	center_map(t_map *map)
{
	size_t	i;
	size_t	j;
	t_point	center;

	center = map->map[map->len / 2][map->height / 2];
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->len)
		{
			map->map[i][j].x += WIDTH / 2 - center.x;
			map->map[i][j].y += HEIGHT / 2 - center.y;
			++j;
		}
		++i;
	}
}

void	scale_map(t_map *map)
{
	size_t	scale;
	size_t	i;
	size_t	j;

	i = 0;
	scale = determine_scale(map);
	while (i < map->height)
	{
		j = 0;
		while (j < map->len)
		{
			map->map[i][j].x *= scale;
			map->map[i][j].y *= scale;
			map->map[i][j].z *= scale;
			++j;
		}
		++i;
	}
}
