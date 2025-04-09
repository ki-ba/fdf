/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:40:26 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/03 14:33:28 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

int	usage(void)
{
	ft_putstr_fd("Usage : ./fdf <map_name.fdf>\n", 1);
	return (1);
}

void	invalid_map(t_vars *vars, char last_line[])
{
	free(last_line);
	ft_putstr_fd("Invalid map\n", 2);
	free_exit(vars, EXIT_FAILURE);
}

void	destroy_map(t_map *map)
{
	size_t	i;

	if (!map)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < map->h_capacity)
		free(map->map[i]);
	free(map->map);
}

void	free_exit(t_vars *vars, int exit_status)
{
	if (vars->map_fd >= 0)
		close(vars->map_fd);
	if (!vars->scene->map)
		exit(exit_status);
	destroy_map(vars->scene->map);
	if (vars->img->img)
		mlx_destroy_image(vars->mlx, vars->img->img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	exit(exit_status);
}

void	free_arr(t_point **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		++i;
	}
	free(arr);
}
