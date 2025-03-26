/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:12:18 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/26 13:38:13 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	print_square(t_data img, t_point origin, int size, int fill)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			if (fill || (i == 0 || i == size || j == 0 || j == size))
				my_mlx_pixel_put(&img, origin.x + i, origin.y + j, 0x00FFFF00);
			++j;
		}
		++i;
	}
}

void	print_rectangle(t_data img, t_point a, t_point b)
{
	t_point	cur;

	cur.x = a.x;
	cur.y = a.y;
	while (cur.x <= b.x)
	{
		cur.y = a.y;
		while (cur.y <= b.y)
		{
			if (cur.x == a.x || cur.x == b.x || cur.y == a.y || cur.y == b.y)
				my_mlx_pixel_put(&img, cur.x, cur.y, 0x00FFFF00);
			++(cur.y);
		}
		++(cur.x);
	}
}

void	ij_to_xy(t_point a)
{
	int	x;
	int	y;

	x = (a.x * 0.5 * WIDTH) - (a.y * 0.5 * WIDTH);
	y = (a.x * 0.25 * HEIGHT) + (a.y * 0.25 * HEIGHT);
	a.x = x;
	a.y = y;
}

void	init_map(t_map *map, char filename[])
{
	map->len = 0;
	map->height = 0;
	map->capacity = 1;
	map->map = ft_calloc(1, sizeof(t_point));
	read_map(map, open_map(filename));
}

int	get_z(t_map *map, int x, int y)
{
	return (map->map[(y * map->len + x)].z);
}

void	print_full_map(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->capacity)
	{
		ft_printf("%d", map->map[i].z);
		if (++i % (map->len) == 0)
			ft_printf("\n");
	}
	ft_printf("\n");
}

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
		return (usage());
	init_map(&map, argv[1]);
	print_full_map(&map);
	free_exit(&map, EXIT_SUCCESS);
	return (0);
}
