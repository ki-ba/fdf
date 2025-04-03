/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:14:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/26 14:17:25 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	copy_array(t_point *dest, t_point *src, int n)
{
	int	i;

	i = 0;
	while (i * 12 < n)
	{
		dest[i] = src[i];
		++i;
	}
}

/*	@brief doubles the size of specified array in-place-ish.
*	@brief (updates the pointer and frees the old memory)
*/
t_point	*double_array_size(t_map *map)
{
	t_point		*new_array;

	new_array = ft_calloc(2 * map->capacity, sizeof(t_point));
	copy_array(new_array, map->map, map->capacity * sizeof(t_point));
	map->capacity = 2 * (map->capacity);
	free(map->map);
	map->map = new_array;
	return (new_array);
}
