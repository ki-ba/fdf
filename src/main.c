/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:41:46 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/14 17:58:48 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_vars		vars;
	t_map		map;
	t_scene		scene;
	t_data		img;

	if (argc != 2 || check_arg(argv[1]))
		return (usage());
	map.h_capacity = 0;
	map.map = NULL;
	scene.map = &map;
	vars.scene = &scene;
	vars.img = &img;
	vars.img->img = NULL;
	init_mlx_data(&vars, argv[1]);
	mlx_hook(vars.win, 02, (1L << 0), key_hook, &vars);
	mlx_hook(vars.win, 17, 0, free_exit, &vars);
	map.min = get_minimum(&map);
	map.max = get_maximum(&map);
	scene.scale = determine_scale(scene.map);
	center_map(&scene);
	render_map(&vars);
	mlx_loop(vars.mlx);
	free_exit(&vars, EXIT_SUCCESS);
	return (0);
}
