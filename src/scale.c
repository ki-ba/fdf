/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:57:26 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/27 17:58:21 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdint.h>

void	get_horizontal_bounds(t_map map, int lr[2])
{
	int		i;
	t_point	cur;

	i = 0;
	lr[0] = INT_MAX;
	lr[1] = 0;
	while (i < map.height * map.len)
	{
		(void)map;
		cur = (map.map[i]);
		if (cur.x < lr[0])
			lr[0] = cur.x;
		if (cur.x > lr[1])
			lr[1] = cur.x;
		++i;
	}
}

void	get_vertical_bounds(t_map map, int tb[2])
{
	int		i;
	t_point	cur;

	i = 0;
	tb[0] = INT_MAX;
	tb[1] = 0;
	while (i < map.height * map.len)
	{
		(void)map;
		cur = (map.map[i]);
		if (cur.y < tb[0])
			tb[0] = cur.y;
		if (cur.y > tb[1])
			tb[1] = cur.y;
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
	int	scale;

	ft_printf("map is %d x %d\n", map->len, map->height);
	get_vertical_bounds(*map, lr);
	get_horizontal_bounds(*map, tb);
	ft_printf("left : %dpx\nright : %dpx\ntop: %dpx\nbot: %dpx\n", lr[0], lr[1], tb[0], tb[1]);
	i = 10;
	scale = (int)pow(2, i);
	while (i > 0 && (scale * lr[0] < 0 || scale * lr[1] > WIDTH || scale * tb[0] < 0 || scale * tb[1] > HEIGHT))
	{
		scale = (int)pow(2, i);
		ft_printf("\n\n === SCALE %d ^ %d =  %d === \n\n", 2, i, scale);
		ft_printf("left : %dpx\nright : %dpx\ntop: %dpx\nbot: %dpx\n", scale * lr[0], scale * lr[1], scale * tb[0], scale * tb[1]);
		--i;
	}
	ft_printf("\n\n\nFINAL SCALE (%d ^ %d = %d)\nleft : %dpx\nright : %dpx\ntop: %dpx\nbot: %dpx\n", 2 , i , (int)pow(2, i), scale * lr[0], scale * lr[1], scale * tb[0], scale * tb[1]);
	return (pow(2, i));
}

int	fits_in_map(t_map map, t_point point)
{
	(void)map;
	(void)point;
	return (0);
}
void	scale_map(t_map *map)
{
	int		scale;
	int		i;

	i = 0;
	scale = determine_scale(map);
	while (i < map->len * map->height)
	{
		map->map[i].x *= scale;
		map->map[i].y *= scale;
		map->map[i].z *= scale;
		++i;
	}
}
