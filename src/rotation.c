/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:01:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/18 10:20:20 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	* @brief updates coordinates of given point
	* @brief after map is rotated of `a` radians around the x axis.
*/
t_point	rotate_x(t_point p0, double a)
{
	t_point	p1;

	p1.x = p0.x;
	p1.y = p0.y;
	p1.z = p0.z;
	p1.px = p0.px;
	p1.py = p0.py * cos(a) - p0.pz * sin(a);
	p1.pz = p0.py * sin(a) + p0.pz * cos(a);
	return (p1);
}

/*
	* @brief updates coordinates of given point
	* @brief after map is rotated of `a` radians around the y axis.
*/
t_point	rotate_y(t_point p0, double a)
{
	t_point	p1;

	p1.x = p0.x;
	p1.y = p0.y;
	p1.z = p0.z;
	p1.px = p0.px * cos(a) - p0.pz * sin(a);
	p1.py = p0.py;
	p1.pz = p0.px * sin(a) + p0.pz * cos(a);
	return (p1);
}

/*
	* @brief updates coordinates of given point
	* @brief after map is rotated of `a` radians around the z axis.
*/
t_point	rotate_z(t_point p0, double a)
{
	t_point	p1;

	p1.x = p0.x;
	p1.y = p0.y;
	p1.z = p0.z;
	p1.px = p0.px * cos(a) - p0.py * sin(a);
	p1.py = p0.px * sin(a) + p0.py * cos(a);
	p1.pz = p0.pz;
	return (p1);
}
