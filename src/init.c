/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:35:30 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/14 17:56:45 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	init_map(t_vars *vars, size_t len)
{
	t_map	*map;

	map = vars->scene->map;
	map->len = len;
	map->height = 0;
	map->h_capacity = 1;
	if (vars->map_fd < 0)
	{
		vars->scene->map = NULL;
		free_exit(vars, EXIT_FAILURE);
	}
	map->map = ft_calloc(1, sizeof(t_point *));
	if (!map->map)
		free_exit(vars, EXIT_FAILURE);
	map->map[0] = ft_calloc(len, sizeof(t_point));
	if (!map->map[0] || vars->map_fd < 0)
		free_exit(vars, EXIT_FAILURE);
}

void	init_scene(t_vars *vars)
{
	size_t	i;
	t_scene	*scene;

	scene = vars->scene;
	i = 0;
	read_map(vars);
	scene->scale = 1;
	while (i < 3)
	{
		scene->rot[i] = 0;
		scene->tr[i] = 0;
		++i;
	}
	scene->ext = 0;
	scene->rot[0] = DEFAULT_ROT_X;
	scene->rot[1] = DEFAULT_ROT_Y;
	scene->rot[2] = DEFAULT_ROT_Z;
}

int	init_mlx_data(t_vars *vars, char map_filename[])
{
	vars->win = NULL;
	vars->mlx = NULL;
	vars->map_fd = open_map(map_filename);
	if (vars->map_fd < 0)
		free_exit(vars, EXIT_FAILURE);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		free_exit(vars, EXIT_FAILURE);
	init_scene(vars);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FdF");
	if (!vars->win)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free_exit(vars, EXIT_FAILURE);
	}
	return (0);
}
