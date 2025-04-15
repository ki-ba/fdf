/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:19:22 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/15 16:50:55 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	create_point(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.px = x;
	point.py = y;
	point.pz = z;
	return (point);
}

int	get_value(char *line, int x)
{
	int		word_index;
	int		i;
	int		map_len;
	int		n;

	map_len = ft_strlen(line);
	i = 0;
	word_index = 0;
	while (word_index < x && i < map_len)
	{
		if (line[i] == ' ')
			++word_index;
		++i;
	}
	n = ft_atoi(line + i);
	return (n);
}

void	apply_translation(t_scene scene, t_point *point)
{
	point->px += scene.tr[0];
	point->py += scene.tr[1];
	point->pz += scene.tr[2];
}

void	apply_extrusion(t_scene scene, t_point *point, double min)
{
	if (point->z > min)
		point->pz += fabs(point->pz - min) * scene.ext;
}
