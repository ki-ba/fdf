/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:18:31 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/01 19:05:14 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, double x, double y, int color)
{
	char			*dst;
	int				intx;
	int				inty;

	intx = (int)round(x);
	inty = (int)round(y);
	/*printf("%d, %d\n", intx, inty);*/
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = data->addr + (inty * data->line_length + intx * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	else
	{
		;
		/*ft_putstr_fd("Warning : trying to draw outside of the window\n", 2);*/
	}
}

void	print_square(t_data img, t_matrix origin, int size, int fill)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			if (fill || (i == 0 || i == size || j == 0 || j == size))
				my_mlx_pixel_put(&img, origin.m[X] + i, origin.m[Y] + j, 0x00FFFFFF);
			++j;
		}
		++i;
	}
}

void	print_rectangle(t_data img, t_matrix a, t_matrix b)
{
	t_matrix	cur;

	cur.m[X] = a.m[X];
	cur.m[Y] = a.m[Y];
	while (cur.m[X] <= b.m[X])
	{
		cur.m[Y] = a.m[Y];
		while (cur.m[Y] <= b.m[Y])
		{
			if (cur.m[Y] == a.m[Y] || cur.m[X] == b.m[X] || cur.m[Y] == a.m[Y] || cur.m[Y] == b.m[Y])
				my_mlx_pixel_put(&img, cur.m[X], cur.m[Y], 0x00FFFFFF);
			++(cur.m[Y]);
		}
		++(cur.m[X]);
	}
}

int	z_to_color(int value)
{
	int	color;
	int	offset;

	offset = 0x00121212;
	color = (0x00ffffff & (value + offset));
	color = 0x00ffffff;
	return (color);
}
