/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:12:18 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/01 20:13:59 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>
void	init_map(t_map *map, char filename[])
{
	int	map_fd;

	map->len = 0;
	map->height = 0;
	map->capacity = 1;
	map_fd = open_map(filename);
	map->map = ft_calloc(1, sizeof(t_matrix));
	if (map_fd < 0)
		free_exit(map, EXIT_FAILURE);
	read_map(map, map_fd);
}

int	get_z(t_map *map, int x, int y)
{
	return (map->map[(y * map->len + x)].m[0][2]);
}

void	draw_map(t_map *map, t_data img)
{
	t_matrix	cur_point;
	t_matrix	prev_row_point;
	t_matrix	next_col_point;
	size_t		i;

	i = 0;
	while (i < map->len * map->height)
	{
		cur_point = map->map[i];
		if (i >= map->len)
		{
			prev_row_point = map->map[i - map->len];
			bresenham(cur_point, prev_row_point, img);
			/*printf("(vertical) drawing (%f, %f) to (%f, %f)\n", cur_point.m[X], cur_point.m[Y], prev_row_point.m[X], prev_row_point.m[Y]);*/
			/*ft_printf("(vertical) drawing point %d to %d\n", i, i - map->len);*/
		}
		if (i % map->len < map->len - 1)
		{
			next_col_point = map->map[i + 1];
			bresenham(cur_point, next_col_point, img);
			/*printf("(horizontal) drawing (%f, %f) to (%f, %f)\n", cur_point.m[X], cur_point.m[Y], next_col_point.m[X], next_col_point.m[Y]);*/
			/*ft_printf("(horizontal) drawing point %d to %d\n", i, i + 1);*/
		}
		++i;
	}
}
// 119 = w; 97 = a; 115 = s; 100 = d;
int	key_hook(int keycode, t_vars *vars)
{
	ft_printf("%d\n", keycode);
	if (keycode >= 97 && keycode <= 119)
	{
		if (keycode == 119)
			rotate_map(vars->map, ANGLE, rotate_x);
		else if (keycode == 97)
			;
		else if (keycode == 115)
			;
		else if (keycode == 100)
			rotate_map(vars->map, ANGLE, rotate_z);
		mlx_destroy_image(vars->mlx, (vars->img));
		vars->img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
		draw_map(vars->map, *(vars->img));
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
	sleep(1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_map		map;
	t_data		img;
	t_vars		vars;

	setvbuf(stdout, NULL, _IONBF, 0);
	if (argc != 2)
		return (usage());
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "FdF");
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	vars.img = &img;
	init_map(&map, argv[1]);
	print_full_map(&map);
	scale_map(&map);
	vars.map = &map;
	print_full_map(&map);
	rotate_map(&map, ANGLE, rotate_x);
	print_full_map(&map);
	rotate_map(&map, ANGLE, rotate_y);
	mlx_key_hook(vars.win, key_hook, &vars);
	/*rotate_map(&map, ANGLE, rotate_z);*/
	print_full_map(&map);
	draw_map(&map, img);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
	ft_printf("map drawn\n");
	mlx_loop(vars.mlx);
	free_exit(&map, EXIT_SUCCESS);
	return (0);
}
