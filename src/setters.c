/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:21:35 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/14 14:22:22 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	@brief sets translation in scene to given values.
	@param vars pointer to program data.
	@param tx x translation
	@param ty y translation
	@param tz z translation
*/
void	set_tr(t_vars *vars, double tx, double ty, double tz)
{
	double	*tr;

	tr = vars->scene->tr;
	tr[X_AXIS] = tx;
	tr[Y_AXIS] = ty;
	tr[Z_AXIS] = tz;
}

/*
	@brief updates scene scale to given value.
	@param vars pointer to program data
	@param scale the desired scale
*/
void	set_scale(t_vars *vars, size_t scale)
{
	vars->scene->scale = scale;
}

/*
	@brief updates scene extrusion to given value.
	@param vars pointer to program data
	@param ext the desired extrusion 
*/
void	set_ext(t_vars *vars, int ext)
{
	vars->scene->ext = ext;
}

/*
	@brief sets rotation in scene to given values.
	@param vars pointer to program data.
	@param ax x rotation
	@param ay y rotation
	@param az z rotation
*/
void	set_rot(t_vars	*vars, double ax, double ay, double az)
{
	double	*rot;

	rot = vars->scene->rot;
	rot[0] = ax;
	rot[1] = ay;
	rot[2] = az;
}
