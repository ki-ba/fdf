/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:45:44 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/15 16:57:53 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	create_color(t_point a, t_point b, int diff, char axis)
{
	double	val;

	if (axis == 'x')
	{
		if (a.x == b.x)
			return (z_to_color(diff, 0));
		else
			val = (b.z - a.z) / (b.x - a.x);
	}
	else if (a.y == b.y)
		return (z_to_color(diff, 0));
	else
		val = (b.z - a.z) / (b.y - a.y);
	if (val == 0)
		return (z_to_color(diff, 0));
	return (z_to_color(diff, val));
}

static void	init_dir(t_dir *dir, t_point a, t_point b)
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

static void	bresenham_gentle(int diff, t_point a, t_point b, t_data img)
{
	int		d;
	int		dy;
	int		dx;
	t_dir	dir;

	(void)diff;
	init_dir(&dir, a, b);
	dy = fabs(b.y - a.y);
	dx = fabs(b.x - a.x);
	d = 2 * dy - dx;
	while (a.x != b.x || a.y != b.y)
	{
		if (d < 0)
			d += (2 * dy);
		else
		{
			d += (2 * dy - 2 * dx);
			a.y += dir.y;
		}
		my_mlx_pixel_put(&img, a.x, a.y, create_color(a, b, diff, 'x'));
		a.x += dir.x;
	}
}

static void	bresenham_steep(int diff, t_point a, t_point b, t_data img)
{
	int		d;
	int		dy;
	int		dx;
	t_dir	dir;

	(void)diff;
	init_dir(&dir, a, b);
	dy = fabs(b.y - a.y);
	dx = fabs(b.x - a.x);
	d = 2 * dx - dy;
	while (a.x != b.x || a.y != b.y)
	{
		if (d < 0)
			d += (2 * dx);
		else
		{
			d += (2 * dx - 2 * dy);
			a.x += dir.x;
		}
		my_mlx_pixel_put(&img, a.x, a.y, create_color(a, b, diff, 'y'));
		a.y += dir.y;
	}
}

void	bresenham(int diff, t_point a, t_point b, t_data img)
{
	double	m;

	a.x = (int)round(a.px);
	a.y = (int)round(a.py);
	b.x = (int)round(b.px);
	b.y = (int)round(b.py);
	if (b.x - a.x == 0)
	{
		bresenham_gentle(diff, a, b, img);
		return ;
	}
	m = (b.y - a.y) / (b.x - a.x);
	if (m > -1 && m < 1)
		bresenham_gentle(diff, a, b, img);
	else
		bresenham_steep(diff, a, b, img);
}
