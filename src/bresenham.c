/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:45:44 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/01 20:14:18 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void	init_dir(t_dir *dir, t_matrix a, t_matrix b)
{
	int	dx;
	int	dy;

	dx = b.m[X] - a.m[X];
	dy = b.m[Y] - a.m[Y];
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

void	bresenham_gentle(t_matrix a, t_matrix b, t_data img)
{
	double		**cur_point;
	int			d;
	int			dy;
	int			dx;
	t_dir		dir;

	init_dir(&dir, a, b);
	cur_point = a.m;
	dy = fabs(b.m[Y] - a.m[Y]);
	dx = fabs(b.m[X] - a.m[X]);
	d = 2 * dy - dx;
	while ((cur_point[X]) != b.m[X] || (cur_point[Y]) != b.m[Y])
	{
		if (d < 0)
			d += (2 * dy);
		else
		{
			d += (2 * dy - 2 * dx);
			cur_point[Y] += dir.y;
		}
		my_mlx_pixel_put(&img, cur_point[X], cur_point[Y], z_to_color(cur_point[Z]));
		cur_point[X] += dir.x;
	}
}

void	bresenham_steep(t_matrix a, t_matrix b, t_data img)
{
	double	**cur_point;
	int		d;
	int		dy;
	int		dx;
	t_dir	dir;

	init_dir(&dir, a, b);
	cur_point = a.m;
	dy = fabs(b.m[Y] - a.m[Y]);
	dx = fabs(b.m[X] - a.m[X]);
	d = 2 * dx - dy;
	while ((cur_point[X]) != b.m[X] || (cur_point[Y]) != b.m[Y])
	{
		if (d < 0)
			d += (2 * dx);
		else
		{
			d += (2 * dx - 2 * dy);
			cur_point[X] += dir.x;
		}
		my_mlx_pixel_put(&img, cur_point[X], cur_point[Y], z_to_color(cur_point[Z]));
		cur_point[Y] += dir.y;
	}
}

void	round_point(t_matrix *p)
{
	p->m[X] = round(p->m[X]);
	p->m[Y] = round(p->m[Y]);
	p->m[Z] = round(p->m[Z]);
}
void	bresenham(t_matrix a, t_matrix b, t_data img)
{
	float		m;
	t_matrix	a1;
	t_matrix	b1;

	mx_dup(&a1, &a);
	mx_dup(&b1, &b);
	round_point(&a1);
	round_point(&b1);
	/*printf("bresenham : a : (%f, %f) -> b : (%f, %f) \n", (a.m[X]), (a.m[Y]), (b.m[X]), (b.m[Y]));*/
	if (b.m[X] - a.m[X] == 0)
		bresenham_gentle(a1, b1, img);
	else
	{
		m = (b.m[Y] - a.m[Y]) / (b.m[X] - a.m[X]);
		if (m > -1 && m < 1)
			bresenham_gentle(a1, b1, img);
		else
			bresenham_steep(a1, b1, img);
	}
}
