/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:14:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/01 13:35:45 by kbarru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stddef.h>

void	copy_array(t_matrix *dest, t_matrix *src)
{
	size_t	i;
	size_t	h;
	size_t	len;

	len = src->j;
	h = src->i;
	i = 0;
	while (i < len * h)
	{
		dest->m[i / len][i % len] = src->m[i / len][i % len];
		++i;
	}
}

/*	@brief doubles the size of specified array in-place-ish.
*	@brief (updates the pointer and frees the old memory)
*/
t_matrix	*double_array_size(t_map *map)
{
	t_matrix	*new_array;

	new_array = ft_calloc(2 * map->capacity, sizeof(t_matrix));
	/*create_null_matrix(new_array, map->len, map->height);*/
	/*copy_array(new_array, map->map, map->capacity);*/
	ft_memmove(new_array, map->map, map->capacity * sizeof(t_matrix));
	map->capacity = 2 * (map->capacity);
	free(map->map);
	map->map = new_array;
	return (new_array);
}

double	**duplicate_mx_arr(t_matrix *src)
{
	double		**dup;
	t_matrix	dup_mx;

	create_null_matrix(&dup_mx, src->i, src->j);
	copy_array(&dup_mx, src);
	dup = dup_mx.m;
	dup_mx.m = NULL;
	return (dup);
}

void	mx_dup(t_matrix *dup, t_matrix *src)
{
	dup->i = src-> i;
	dup->j = src->j;
	create_null_matrix(dup, dup->i, dup->j);
	copy_array(dup, src);
}
