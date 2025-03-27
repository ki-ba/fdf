/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:12:18 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/27 14:29:54 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_ppoint	ij_to_xy(t_ppoint a)
{
	t_ppoint	b;

	b.x = (a.x - a.y) * 0.5 * (TILE_WIDTH - 1) + WIDTH / 2;
	b.y = (a.x + a.y) * 0.25 * (TILE_HEIGHT - 1) + HEIGHT / 2;
	return (b);
}

void	init_map(t_map *map, char filename[])
{
	int	map_fd;

	map->len = 0;
	map->height = 0;
	map->capacity = 1;
	map_fd = open_map(filename);
	map->map = ft_calloc(1, sizeof(t_point));
	if (map_fd < 0)
		free_exit(map, EXIT_FAILURE);
	read_map(map, map_fd);
}

int	get_z(t_map *map, int x, int y)
{
	return (map->map[(y * map->len + x)].z);
}

int	main(int argc, char *argv[])
{
	t_map		map;
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_point		cur_point;
	t_ppoint	cur_ppoint;
	int			i;

	if (argc != 2)
		return (usage());
	i = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	init_map(&map, argv[1]);
	while (i < map.len * map.height)
	{
		cur_point = map.map[i];
		cur_ppoint = project_point(cur_point);
		if (i >= map.len)
			bresenham(cur_ppoint, project_point(map.map[i - map.len]), img);
		if (i % map.len < map.len - 1)
			bresenham(cur_ppoint, project_point(map.map[i + 1]), img);
		ft_printf("printing (%d, %d) -> (%d, %d)\n",cur_point.x, cur_point.y, cur_ppoint.x, cur_ppoint.y);
		//my_mlx_pixel_put(&img, cur_ppoint.x, cur_ppoint.y, 0x00FFFF00);
		++i;
	}
	print_full_map(&map);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	free_exit(&map, EXIT_SUCCESS);
	return (0);
}
