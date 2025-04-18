/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:08:52 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/08 18:08:52 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	@brief interprets num8 and num2 to extrude up or down
*/
static void	key_hook_ext(int kc, t_vars *vars)
{
	if (kc == 65431 || kc == 65433)
	{
		if (kc == 65431)
		{
			vars->scene->ext += DEF_EXT_STEP;
		}
		else
			vars->scene->ext -= DEF_EXT_STEP;
		render_scene(vars->scene);
		render_map(vars);
	}
}

/*
	@brief interprets + and - to scale up or down
*/
static void	key_hook_scale(int kc, t_vars *vars)
{
	if (kc == 45 || kc == 61 || kc == 65451 || kc == 65453)
	{
		if (kc == 61 || kc == 65451)
			update_scale(vars, DEF_SCALE_STEP);
		else
			update_scale(vars, -DEF_SCALE_STEP);
		render_scene(vars->scene);
		render_map(vars);
	}
	else
		key_hook_ext(kc, vars);
}

/*
	@brief interprets arrow keys to update translation
*/

static void	key_hook_tr(int kc, t_vars *vars)
{
	if (kc >= 65361 && kc <= 65364)
	{
		if (kc == 65362)
			update_translation(vars, Y_AXIS, -DEF_TR_STEP);
		if (kc == 65364)
			update_translation(vars, Y_AXIS, DEF_TR_STEP);
		if (kc == 65361)
			update_translation(vars, X_AXIS, -DEF_TR_STEP);
		if (kc == 65363)
			update_translation(vars, X_AXIS, DEF_TR_STEP);
		render_scene(vars->scene);
		render_map(vars);
	}
	else
		key_hook_scale(kc, vars);
}

/*
	@brief interprets resetters (R, T , Y)
*/
static void	key_hook_2(int keycode, t_vars *vars)
{
	if (keycode == 114 || keycode == 116 || keycode == 121)
	{
		if (keycode == 114)
			set_rot(vars, DEFAULT_ROT_X, DEFAULT_ROT_Y, DEFAULT_ROT_Z);
		else if (keycode == 116)
			set_rot(vars, 0, 0, 0);
		else if (keycode == 121)
			set_rot(vars, 1.57, 0, 0);
		set_tr(vars, WIDTH >> 1, HEIGHT >> 1, 0);
		set_scale(vars, determine_scale(vars->scene->map));
		set_ext(vars, 0);
		render_scene(vars->scene);
		render_map(vars);
	}
	else
		key_hook_tr(keycode, vars);
}

/*
	@brief catches and interprets keypress.
	@param keycode the ascii code of the pressed key.
	@param vars pointer to the program data
*/
int	key_hook(int keycode, t_vars *vars)
{
	int		kc;

	kc = keycode;
	if (keycode == 65307)
		free_exit(vars, EXIT_SUCCESS);
	else if (kc == 119 || kc == 97 || kc == 115 || kc == 100)
	{
		if (keycode == 119)
			update_rot(vars, 0, ANGLE);
		else if (keycode == 97)
			update_rot(vars, 1, -ANGLE);
		else if (keycode == 115)
			update_rot(vars, 0, -ANGLE);
		else
			update_rot(vars, 1, ANGLE);
		render_scene(vars->scene);
		render_map(vars);
	}
	else
		key_hook_2(keycode, vars);
	return (0);
}
