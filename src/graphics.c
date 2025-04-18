/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:18:31 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/18 11:22:25 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	@brief renders scene properties to the actual map.
*/
void	render_scene(t_scene *scene)
{
	size_t	i;
	size_t	j;
	t_map	*map;
	size_t	scale;
	double	min;

	scale = scene->scale;
	map = scene->map;
	min = get_minimum(map);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->len)
		{
			map->map[i][j].px = (map->map[i][j].x - (map->len >> 1)) * scale;
			map->map[i][j].py = (map->map[i][j].y - (map->height >> 1)) * scale;
			map->map[i][j].pz = map->map[i][j].z * scale;
			apply_extrusion(*scene, &(map->map[i][j]), min);
			map->map[i][j] = rotate_z(map->map[i][j], scene->rot[2]);
			map->map[i][j] = rotate_x(map->map[i][j], scene->rot[0]);
			map->map[i][j] = rotate_y(map->map[i][j], scene->rot[1]);
			apply_translation(*scene, &(map->map[i][j]));
		}
	}
}

/*
	@brief puts a pixel on current image.
	@brief includes protection if coordinates exceed image bounds.
	@param data the image data.
*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT))
	{
		dst = data->addr;
		dst += (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/*
	@brief draws the given map in given img.
*/

void	draw_map(t_map *map, t_data img)
{
	size_t		i;
	size_t		j;
	t_point		**arr;

	i = 0;
	arr = map->map;
	while (i < map->height)
	{
		j = 0;
		while (j < map->len)
		{
			if (j < map->len - 1)
			{
				bresenham(arr[i][j], arr[i][j + 1], img);
			}
			if (i < map->height - 1)
			{
				bresenham(arr[i][j], arr[i + 1][j], img);
			}
			++j;
		}
		++i;
	}
}

/*
	@brief computes the map according to the scene, destroys old image,
	@brief then creates a new one and draws the map inside.
*/
void	render_map(t_vars	*vars)
{
	t_data	*img;

	render_scene(vars->scene);
	img = vars->img;
	if (img->img)
		mlx_destroy_image(vars->mlx, img->img);
	img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!(img->img))
		free_exit(vars, EXIT_FAILURE);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		free_exit(vars, EXIT_FAILURE);
	draw_map(vars->scene->map, *img);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}
