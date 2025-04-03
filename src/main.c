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
#include "libft.h"

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

void	draw_map(t_map *map, t_data img)
{
	t_point		cur_point;
	t_point		projected;
	int			i;

	i = 0;
	while (i < map->len * map->height)
	{
		cur_point = (map->map[i]);
		projected = project_point(cur_point);
		if (i >= map->len)
			bresenham(projected, project_point(map->map[i - map->len]), img);
		if (i % map->len < map->len - 1)
			bresenham(projected, project_point(map->map[i + 1]), img);
		/*ft_printf("printing (%d, %d) -> (%d, %d)	(value : %d)\n",cur_point.x, cur_point.y, projected.x, projected.y, projected.z);*/
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
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "FdF");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	init_map(&map, argv[1]);
	/*print_full_map(&map);*/
	scale_map(&map);
	draw_map(&map, img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	free_exit(&map, EXIT_SUCCESS);
	return (0);
}
