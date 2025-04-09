/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:18:31 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/08 18:09:36 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		/*ft_putstr_fd("warning : drawing outside of window\n", 2);*/
		;
	else
	{
		dst = data->addr;
		dst += (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
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

int	z_to_color(int value)
{
	int	color;

	color = (0x00ffffff & (value + 0x00505050));
	return (color);
}

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
	draw_map(vars->scene->map, *img);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}

