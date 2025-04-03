/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:12:18 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/03 16:57:19 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>

void	init_map(t_map *map, int map_fd, size_t len)
{
	map->len = len;
	map->height = 0;
	map->h_capacity = 1;
	map->map = ft_calloc(1, sizeof(t_point *));
	if (!map->map)
		free_exit(map, EXIT_FAILURE);
	map->map[0] = ft_calloc(len, sizeof(t_point));
	if (!map->map[0] || map_fd < 0)
		free_exit(map, EXIT_FAILURE);
}

void	draw_map(t_map *map, t_data img)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->len)
		{
			/*ft_printf("point %d, %d\n", i, j);*/
			if (j < map->len - 1)
			{
				bresenham(map->map[i][j], map->map[i][j + 1], img);
			}
			if (i < map->height - 1)
			{
				bresenham(map->map[i][j], map->map[i + 1][j], img);
			}
			++j;
		}
		++i;
	}
}

int	main(int argc, char *argv[])
{
	t_map		map;
	void		*mlx;
	void		*mlx_win;
	t_data		img;

	if (argc != 2)
		return (usage());
	read_map(&map, open_map(argv[1]));
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "FdF");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	rotate_map(&map, 0.785, rotate_x);
	rotate_map(&map, 0.785, rotate_y);
	scale_map(&map);
	center_map(&map);
	/*print_full_map(&map);*/
	/*rotate_map(&map, ANGLE, rotate_z);*/
	draw_map(&map, img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	free_exit(&map, EXIT_SUCCESS);
	return (0);
}
