/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:44:19 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/01 18:47:55 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	assign_array(double *arr, size_t n, ...)
{
	size_t	i;
	va_list	args;

	i = 0;
	va_start(args, n);
	while (i < n)
	{
		arr[i] = va_arg(args, double);
		++i;
	}
	va_end(args);
}

void	rotate_map(t_map *map, double a, t_matrix (*r_f)(t_matrix, double))
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ft_printf("rotation function : %p\n", r_f);
	while (i < map->height)
	{
		j = 0;
		while (j < map->len)
		{
			/*free(&(map->map[i * map->len + j]));*/
			map->map[i * map->len + j] = r_f(map->map[i * map->len + j], a);
			++j;
		}
		++i;
	}
}
t_matrix	rotate_x(t_matrix point, double a)
{
	double		*mrx;
	t_matrix	p_point;
	t_matrix	rotation_mx;

	mrx = ft_calloc(9, sizeof(double));
	assign_array(mrx, 9, 1, 0, 0, 0, cos(a), sin(a), 0, -sin(a), cos(a));
	create_matrix(&rotation_mx, 3, 3, mrx);
	/*print_matrix(rotation_mx);*/
	mx_mult(&p_point, point, rotation_mx);
	return (p_point);
}

t_matrix	rotate_y(t_matrix point, double a)
{
	double		*mry;
	t_matrix	p_point;
	t_matrix	rotation_mx;

	mry = ft_calloc(9, sizeof(double));
	assign_array(mry, 9, cos(a), 0, sin(a), 0, 1, 0, -sin(a), 0, cos(a));
	create_matrix(&rotation_mx, 3, 3, mry);
	mx_mult(&p_point, point, rotation_mx);
	return (p_point);
}

t_matrix	rotate_z(t_matrix point, double a)
{
	double		*mrz;
	t_matrix	p_point;
	t_matrix	rotation_mx;

	mrz = ft_calloc(9, sizeof(double));
	assign_array(mrz, 9, cos(a), sin(a), 0, -sin(a), cos(a), 0, 0, 1);
	create_matrix(&rotation_mx, 3, 3, mrz);
	mx_mult(&p_point, point, rotation_mx);
	return (p_point);
}
