/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:28:02 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/27 14:32:45 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <math.h>
# include <mlx.h>

# ifndef WIDTH
#  define WIDTH 2920
# endif

# ifndef HEIGHT
#  define HEIGHT 2080
# endif

# define TILE_HEIGHT 32
# define TILE_WIDTH 32

# define ANGLE 0.785 

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}		t_point;

typedef struct s_ppoint
{
	int	x;
	int	y;
}		t_ppoint;

typedef struct s_dir
{
	int	x;
	int	y;
}		t_dir;

typedef struct s_map
{
	int		len;
	int		height;
	t_point	*map;
	size_t	capacity;
}			t_map;
/* main.c */

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/* parsing.c */

t_point	create_point(int x, int y, int z);
void	count_map_height(t_map map, char map_filename[]);
void	read_map(t_map *map, int map_fd);
t_ppoint	project_point(t_point point);
void	print_arr(char **map);
void	print_arr_int(int **arr);
int		**convert_map(char **map);
int		get_value(char *map, int y);
int		open_map(char map_filename[]);
int		ft_strlen_ws(char *str);
int		count_words(char *s, char sep);
void	set_map_dimensions(t_map *map, char map_filename[]);

/* bresenham.c */

void	bresenham(t_ppoint a, t_ppoint b, t_data img);
void	bresenham_steep(t_ppoint a, t_ppoint b, t_data img);
void	bresenham_gentle(t_ppoint a, t_ppoint b, t_data img);

/* error.c */
void	invalid_map(t_map *map);
int		usage(void);
void	free_exit(t_map *map, int exit_status);
/* main.c */
void	print_full_map(t_map *map);

/* dynamic_array_utils.c */
t_point	*double_array_size(t_map *map);

/* graphics.c */
int		z_to_color(int value);
void	print_square(t_data img, t_point origin, int size, int fill);
#endif
