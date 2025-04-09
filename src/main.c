/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:47:55 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/09 09:47:57 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_scene(t_scene *scene)
{
	size_t	i;
	size_t	j;
	t_map	*map;

	map = scene->map;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->len)
		{
			map->map[i][j].px = map->map[i][j].x - (map->len >> 1);
			map->map[i][j].py = map->map[i][j].y - (map->height >> 1);
			map->map[i][j].pz = map->map[i][j].z;
			map->map[i][j].px *= scene->scale;
			map->map[i][j].py *= scene->scale;
			map->map[i][j].pz *= scene->scale;
			apply_extrusion(*scene, &(map->map[i][j]));
			map->map[i][j] = rotate_z(map->map[i][j], scene->rot[2]);
			map->map[i][j] = rotate_x(map->map[i][j], scene->rot[0]);
			map->map[i][j] = rotate_y(map->map[i][j], scene->rot[1]);
			apply_translation(*scene, &(map->map[i][j]));
		}
	}
	/*print_full_map(scene->map);*/
	/*print_actions(*scene);*/
}

void	update_rot(t_vars *vars, size_t axe, double angle)
{
	double	*rot;

	rot = vars->scene->rot;
	rot[axe] += angle;
	if (rot[axe] >= 2 * M_PI)
		rot[axe] -= 2 * M_PI;
	if (rot[axe] <= -2 * M_PI)
		rot[axe] += 2 * M_PI;
}

void	update_translation(t_vars *vars, size_t dir, int delta)
{
	double	*tr;

	tr = vars->scene->tr;
	tr[dir] += delta;
}

void	set_tr(t_vars *vars, double tx, double ty, double tz)
{
	double	*tr;

	tr = vars->scene->tr;
	tr[X_AXIS] = tx;
	tr[Y_AXIS] = ty;
	tr[Z_AXIS] = tz;
}

void	set_scale(t_vars *vars, size_t scale)
{
	vars->scene->scale = scale;
}

void	update_scale(t_vars *vars, int scale_delta)
{
	size_t	*scale;
	int		s_scale;

	scale = &(vars->scene->scale);
	s_scale = *scale + scale_delta;
	printf("s_scale = %d", s_scale);
	if (s_scale < 1)
		*scale = 1;
	else
		*scale = s_scale;
	printf("new scale : %zu\n", *scale);
}

void	set_ext(t_vars *vars, int ext)
{
	vars->scene->ext = ext;
}

void	update_extrusion(t_vars *vars, int ext)
{
	long long int	sum;

	sum = vars->scene->ext + ext;
	if (sum >= INT_MIN && sum <= INT_MAX)
		vars->scene->ext = sum;
	else if (sum <= INT_MIN)
		vars->scene->ext = INT_MIN;
	else
		vars->scene->ext = INT_MAX;
	vars->scene->ext = 20;
}

void	set_rot(t_vars	*vars, double ax, double ay, double az)
{
	double	*rot;

	rot = vars->scene->rot;
	rot[0] = ax;
	rot[1] = ay;
	rot[2] = az;
}

int	main(int argc, char *argv[])
{
	t_vars		vars;
	t_map		map;
	t_scene		scene;
	t_data		img;

	if (argc != 2)
		return (usage());
	map.h_capacity = 0;
	map.map = NULL;
	scene.map = &map;
	vars.scene = &scene;
	vars.img = &img;
	vars.img->img = NULL;
	init_mlx_data(&vars, argv[1]);
	mlx_key_hook(vars.win, key_hook, &vars);
	scene.scale = determine_scale(scene.map);
	center_map(&scene);
	rotate_map(&map, 0, rotate_y);
	render_map(&vars);
	mlx_loop(vars.mlx);
	free_exit(&vars, EXIT_SUCCESS);
	return (0);
}
