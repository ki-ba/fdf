/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:14:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/03 16:22:54 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

/*	@brief doubles the size of specified array in-place-ish.
*	@brief (updates the pointer and frees the old memory)
*/
void	double_array_size(t_map *map)
{
	size_t		i;
	t_point		**new_array;

	new_array = ft_calloc(2 * map->height, sizeof(t_point *));
	if (!new_array)
		free_exit(map, EXIT_FAILURE);
	i = 0;
	while (i < map->height)
	{
		new_array[i] = map->map[i];
		++i;
	}
	while (i < 2 * map->height)
	{
		new_array[i] = ft_calloc(map->len, sizeof(t_point));
		if (!new_array[i])
		{
			free_arr(new_array, i);
			free_exit(map, EXIT_FAILURE);
		}
		++i;
	}
	map->h_capacity *= 2;
	/*free(map->map);*/
	map->map = new_array;
}
