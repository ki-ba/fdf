/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:18:31 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/03 16:27:16 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	{
		/*ft_printf("warning : %d, %d is outside of window\n", x, y);*/
		;
	}
	else
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	print_square(t_data img, t_point origin, int size, int fill)
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
				my_mlx_pixel_put(&img, origin.x + i, origin.y + j, 0x00FFFFFF);
			++j;
		}
		++i;
	}
}

void	print_rectangle(t_data img, t_point a, t_point b)
{
	t_point	cur;

	cur.x = a.x;
	cur.y = a.y;
	while (cur.x <= b.x)
	{
		cur.y = a.y;
		while (cur.y <= b.y)
		{
			if (cur.x == a.x || cur.x == b.x || cur.y == a.y || cur.y == b.y)
				my_mlx_pixel_put(&img, cur.x, cur.y, 0x00FFFFFF);
			++(cur.y);
		}
		++(cur.x);
	}
}

int	z_to_color(int value)
{
	int	color;

	color = (0x00ffffff & (value + 0x00505050));
	/*ft_printf("%x\n", color);*/
	return (color);
}
