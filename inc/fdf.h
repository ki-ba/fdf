/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:28:02 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/01 20:09:30 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "matrix.h"
# include <math.h>
# include <mlx.h>

# ifndef WIDTH
#  define WIDTH 1920 
# endif

# ifndef HEIGHT
#  define HEIGHT 1080 
# endif

# ifndef X
#  define X 0][0
# endif

# ifndef Y
#  define Y 0][1
# endif

# ifndef Z
#  define Z 0][2
# endif
# define TILE_HEIGHT 16
# define TILE_WIDTH 16

# define PI 3.1415
# define ANGLE 120 

# ifndef INT_MIN
#  define INT_MIN -2147483648
# endif

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

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

typedef struct s_dir
{
	int	x;
	int	y;
}		t_dir;

typedef struct s_map
{
	size_t		len;
	size_t		height;
	t_matrix	*map;
	size_t		capacity;
}				t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*img;
	t_map	*map;
}				t_vars;

/* main.c */
void		my_mlx_pixel_put(t_data *data, double x, double y, int color);

/* parsing.c */
void		create_point(t_matrix *point, double x, double y, double z);
void		count_map_height(t_map map, char map_filename[]);
void		read_map(t_map *map, int map_fd);
t_matrix	project_point(t_matrix point);
void		print_arr(char **map);
void		print_arr_int(int **arr);
int			**convert_map(char **map);
int			get_value(char *map, int y);
int			open_map(char map_filename[]);
int			ft_strlen_ws(char *str);
size_t		count_words(char *s, char sep);
void		set_map_dimensions(t_map *map, char map_filename[]);

/* bresenham.c */
void		bresenham(t_matrix a, t_matrix b, t_data img);

/* error.c */
void		invalid_map(t_map *map);
int			usage(void);
void		free_exit(t_map *map, int exit_status);
/* main.c */
void		print_full_map(t_map *map);

/* dynamic_array_utils.c */
t_matrix	*double_array_size(t_map *map);
double		**duplicate_mx_arr(t_matrix *src);
void		mx_dup(t_matrix *dup, t_matrix *src);

/* graphics.c */
int			z_to_color(int value);
void		print_square(t_data img, t_matrix origin, int size, int fill);

/* scale.c */
int			determine_scale(t_map *map);
void		scale_map(t_map *map);
t_matrix	center_point(t_map map, t_matrix point);
t_matrix	get_center(t_map map);

/* rotation.c */
void		assign_array(double *arr, size_t n, ...);
void		rotate_map(t_map *map, double a, t_matrix (*r_f)(t_matrix, double));
t_matrix	rotate_x(t_matrix point, double a);
t_matrix	rotate_y(t_matrix point, double a);
t_matrix	rotate_z(t_matrix point, double a);

#endif
