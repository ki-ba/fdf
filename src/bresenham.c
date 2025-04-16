/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:45:44 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/16 18:39:35 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		my_mlx_pixel_put(&img, a.x, a.y, DEF_COLOR);
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
		my_mlx_pixel_put(&img, a.x, a.y, DEF_COLOR);
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
