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
	ft_printf("left : %d\nright : %dpx\ntop : %d\nbot: %dpx\n", lr[0], lr[1], tb[0], tb[1]);
	scale = 1;
	while (scale *(lr[1] - lr[0]) < 0.7 * WIDTH && scale * (tb[1] - tb[0]) < 0.7 * HEIGHT)
	{
		ft_printf("\n\n === SCALE = %d === \n\n", scale);
		ft_printf("horizontal delta : %d\nvertical delta :%d\n\n\n", scale * (lr[1] - lr[0]), scale * (tb[1] - tb[0]));
		ft_printf("right : %dpx\nbot: %dpx\n", scale * lr[1], scale * tb[1]);
		++scale;
	}
	ft_printf("FINAL SCALE\nleft : %d\nright : %dpx\ntop : %d\nbot: %dpx\n", lr[0], lr[1], tb[0], tb[1]);
	return (scale);
}

void	center_map(t_scene *scene)
{
	scene->tr[0] = (WIDTH >> 1);
	scene->tr[1] = (HEIGHT >> 1);
}
