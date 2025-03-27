/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:45:44 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/27 12:45:32 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void	init_dir(t_dir *dir, t_ppoint a, t_ppoint b)
{
	int	dx;
	int	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (dy < 0)
		dir->y = -1;
	else if (dy == 0)
		dir->y = 0;
	else
		dir->y = 1;
	if (dx < 0)
		dir->x = -1;
	else if (dx == 0)
		dir->x = 0;
	else
		dir->x = 1;
}

void	bresenham_gentle(t_ppoint a, t_ppoint b, t_data img)
{
	t_point	cur_point;
	int		d;
	int		dy;
	int		dx;
	t_dir	dir;

	init_dir(&dir, a, b);
	cur_point.x = a.x;
	cur_point.x = a.x;
	cur_point.y = a.y;
	dy = abs(b.y - a.y);
	dx = abs(b.x - a.x);
	d = 2 * dy - dx;
	while (cur_point.x != b.x || cur_point.y != b.y)
	{
		if (d < 0)
			d += (2 * dy);
		else
		{
			d += (2 * dy - 2 * dx);
			cur_point.y += dir.y;
		}
		my_mlx_pixel_put(&img, cur_point.x, cur_point.y, z_to_color(cur_point.z));
		cur_point.x += dir.x;
	}
}

void	bresenham_steep(t_ppoint a, t_ppoint b, t_data img)
{
	t_point	cur_point;
	int		d;
	int		dy;
	int		dx;
	t_dir	dir;

	init_dir(&dir, a, b);
	cur_point.x = a.x;
	cur_point.y = a.y;
	dy = abs(b.y - a.y);
	dx = abs(b.x - a.x);
	d = 2 * dx - dy;
	while (cur_point.x != b.x || cur_point.y != b.y)
	{
		if (d < 0)
			d += (2 * dx);
		else
		{
			d += (2 * dx - 2 * dy);
			cur_point.x += dir.x;
		}
		my_mlx_pixel_put(&img, cur_point.x, cur_point.y, z_to_color(cur_point.z));
		cur_point.y += dir.y;
	}
}

void	bresenham(t_ppoint a, t_ppoint b, t_data img)
{
	float	m;

	if (b.x - a.x == 0)
	{
		bresenham_gentle(a, b, img);
		return ;
	}
	m = (b.y - a.y) / (b.x - a.x);
	if (m > -1 && m < 1)
		bresenham_gentle(a, b, img);
	else
		bresenham_steep(a, b, img);
}
