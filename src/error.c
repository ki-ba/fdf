/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:40:26 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/03 14:33:28 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	usage(void)
{
	ft_putstr_fd("Usage : ./fdf <map_name.fdf>\n", 1);
	return (1);
}

void	invalid_map(t_map *map)
{
	ft_putstr_fd("Invalid map\n", 2);
	free_exit(map, EXIT_FAILURE);
}

void	free_exit(t_map *map, int exit_status)
{
	if (map)
		free(map->map);
	exit(exit_status);
}

void	free_arr(t_point **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		++i;
	}
	free(arr);
}
