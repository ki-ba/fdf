/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:40:26 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/25 11:36:07 by kbarru           ###   ########lyon.fr   */
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
	free(map->map);
	exit(exit_status);
}
