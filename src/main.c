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
#include "mlx.h"

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

void	render_scene(t_scene *scene)
{
	size_t	i;
	size_t	j;
	t_map	*map;

	map = scene->map;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->len)
		{
			map->map[i][j].px = map->map[i][j].x - ((map->len * 1) >> 1);
			map->map[i][j].py = map->map[i][j].y - ((map->height * 1 )>> 1);
			map->map[i][j].pz = map->map[i][j].z;
			/*printf("%f, %f after origin switch\n", map->map[i][j].px, map->map[i][j].py);*/
			map->map[i][j].px *= scene->scale;
			map->map[i][j].py *= scene->scale;
			map->map[i][j].pz *= scene->scale;
			/*printf("%f, %f after scaling\n", map->map[i][j].px, map->map[i][j].py);*/
			map->map[i][j].px += scene->tr[0];
			map->map[i][j].py += scene->tr[1];
			map->map[i][j].pz += scene->tr[2];
			/*printf("%f, %f after translation\n", map->map[i][j].px, map->map[i][j].py);*/
			map->map[i][j] = rotate_x(map->map[i][j], scene->rot[0]);
			map->map[i][j] = rotate_y(map->map[i][j], scene->rot[1]);
			map->map[i][j] = rotate_z(map->map[i][j], scene->rot[2]);
			/*map->map[i][j] = center_point(map->map[i][j]);*/
			++j;
		}
		++i;
	}
	center_map(scene);
}

void	render_map(t_vars	vars)
{
	t_data	*img;

	render_scene(vars.scene);
	img = vars.img;
	if (img->img)
		mlx_destroy_image(vars.mlx, img->img);
	img->img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	draw_map(vars.scene->map, *img);
	mlx_put_image_to_window(vars.mlx, vars.win, img->img, 0, 0);
}

int	key_hook(int keycode, t_vars *vars)
{
	t_map	*map;
	t_scene	*scene;
	int		kc;

	kc = keycode;
	scene = vars->scene;
	map = scene->map;
	(void)vars;
	if (keycode == 65307)
		free_exit(map, EXIT_SUCCESS);
	else if (kc == 119 || kc == 97 || kc == 115 || kc == 100)
	{
		if (keycode == 119)
			scene->rot[0] = (scene->rot[0] + ANGLE);
		else if (keycode == 97)
			scene->rot[1] = (scene->rot[1] - ANGLE);
		else if (keycode == 115)
			scene->rot[0] = (scene->rot[0] - ANGLE);
		else
			scene->rot[1] = (scene->rot[1] + ANGLE);
		render_scene(vars->scene);
		render_map(*vars);
	}
	ft_printf("%d pressed\n", keycode);
	print_actions(*scene);
	return (0);
}

int	init_mlx_data(t_vars *vars)
{
	t_map	*map;

	map = vars->scene->map;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		free_exit(map, EXIT_FAILURE);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FdF");
	if (!vars->win)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free_exit(map, EXIT_FAILURE);
	}
	return (0);
}

void	init_scene(t_scene *scene, int map_fd)
{
	size_t	i;

	i = 0;
	read_map(scene->map, map_fd);
	scene->scale = 1;
	while (i < 3)
	{
		scene->rot[i] = 0;
		scene->tr[i] = 0;
		++i;
	}
}

int	main(int argc, char *argv[])
{
	t_vars		vars;
	t_map		map;
	t_scene		scene;

	if (argc != 2)
		return (usage());
	scene.map = &map;
	init_scene(&scene, open_map(argv[1]));
	vars.scene = &scene;
	vars.img->img = NULL;
	init_mlx_data(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	scene.scale = determine_scale(scene.map);
	center_map(&scene);
	rotate_map(&map, 0, rotate_y);
	print_full_map(&map);
	render_map(vars);
	mlx_loop(vars.mlx);
	free_exit(&map, EXIT_SUCCESS);
	return (0);
}
