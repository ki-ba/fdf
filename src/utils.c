/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:14:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/16 18:43:33 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief calculates the length of current string until next occurence of
 * @brief the given char, or nullbyte, whichever occurs first.
 */
size_t	ft_strlen_c(char str[], char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	if (str[i] != c)
		return (0);
	return (i);
}

/**
 * @brief doubles the size of specified array in-place-ish.
 * @brief (updates the pointer and frees the old memory)
*/
void	double_array_size(t_vars *vars)
{
	size_t		i;
	t_point		**new_array;
	t_map		*map;

	map = vars->scene->map;
	new_array = ft_calloc(2 * map->height, sizeof(t_point *));
	if (!new_array)
		free_exit(vars, EXIT_FAILURE);
	i = -1;
	while (++i < map->height)
		new_array[i] = map->map[i];
	while (i < 2 * map->height)
	{
		new_array[i] = ft_calloc(map->len, sizeof(t_point));
		if (!new_array[i])
		{
			free_arr(new_array, i);
			free_exit(vars, EXIT_FAILURE);
		}
		++i;
	}
	map->h_capacity *= 2;
	free(map->map);
	map->map = new_array;
}
