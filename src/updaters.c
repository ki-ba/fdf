/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updaters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:22:34 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/18 10:19:59 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	@brief adds `angle` to the scene rotation on given axis
	@brief and mods it by 2*pi.
*/
void	update_rot(t_vars *vars, size_t axis, double angle)
{
	double	*rot;

	rot = vars->scene->rot;
	rot[axis] += angle;
	if (rot[axis] >= 2 * M_PI)
		rot[axis] -= 2 * M_PI;
	if (rot[axis] <= -2 * M_PI)
		rot[axis] += 2 * M_PI;
}

/*
	@brief adds `delta` to the scene translationon given direction.
*/
void	update_translation(t_vars *vars, size_t dir, int delta)
{
	double	*tr;

	tr = vars->scene->tr;
	tr[dir] += delta;
}

/*
	@brief adds `scale_delta` to current scene scale.
*/
void	update_scale(t_vars *vars, int scale_delta)
{
	size_t	*scale;
	int		s_scale;

	scale = &(vars->scene->scale);
	s_scale = *scale + scale_delta;
	if (s_scale < 1)
		*scale = 1;
	else
		*scale = s_scale;
}

/*
	@brief adds `ext` to current scene extrusion.
*/
void	update_extrusion(t_vars *vars, int ext)
{
	long long int	sum;

	sum = vars->scene->ext + ext;
	if (sum >= INT_MIN && sum <= INT_MAX)
		vars->scene->ext = sum;
	else if (sum <= INT_MIN)
		vars->scene->ext = INT_MIN;
	else
		vars->scene->ext = INT_MAX;
	vars->scene->ext = 20;
}
