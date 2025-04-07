/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:28:02 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/03 16:37:21 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <math.h>
# include <mlx.h>

# ifndef WIDTH
#  define WIDTH 1920
# endif

# ifndef HEIGHT
#  define HEIGHT 1080
# endif

# define TILE_HEIGHT 16
# define TILE_WIDTH 16

# define PI 3.1415
# define ANGLE 0.39

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
}			t_data;
typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	px;
	double	py;
	double	pz;
}			t_point;

typedef struct s_dir
{
	int	x;
	int	y;
}		t_dir;

typedef struct s_map
{
	size_t	len;
	size_t	height;
	size_t	h_capacity;
	t_point	**map;
}			t_map;

typedef struct s_scene
{
	t_map	*map;
	size_t	scale;
	double	rot[3];
	double	tr[3];
}			t_scene;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*img;
	t_scene	*scene;
}			t_vars;

/* main.c */
void	init_map(t_map *map, int map_fd, size_t len);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	print_actions(t_scene scene);
void	print_full_map(t_map *map);

/* parsing.c */
t_point	create_point(double x, double y, double z);
void	count_map_height(t_map map, char map_filename[]);
void	read_map(t_map *map, int map_fd);
t_point	project_point(t_point point);
void	print_arr(char **map);
void	print_arr_int(int **arr);
int		**convert_map(char **map);
int		get_value(char *map, int y);
int		open_map(char map_filename[]);
int		ft_strlen_ws(char *str);
size_t	count_words(char *s, char sep);
void	set_map_dimensions(t_map *map, char map_filename[]);

/* bresenham.c */
void	bresenham(t_point a, t_point b, t_data img);

/* error.c */
void	invalid_map(t_map *map);
int		usage(void);
void	free_exit(t_map *map, int exit_status);
void	free_arr(t_point **arr, size_t n);
/* main.c */
void	print_full_map(t_map *map);

/* dynamic_array_utils.c */
void	double_array_size(t_map *map);

/* graphics.c */
int		z_to_color(int value);
void	print_square(t_data img, t_point origin, int size, int fill);

/* scale.c */
size_t	determine_scale(t_map *map);
void	translate_map(t_scene scene, int offset_x, int offset_y);
void	scale_map(t_scene *scene);
t_point	center_point(t_point p0);
void	center_map(t_scene *scene);
/* rotation.c */

void	rotate_map(t_map *map, double a, t_point (*r_f)(t_point pt, double a));
t_point	rotate_x(t_point p0, double a);
t_point	rotate_y(t_point p0, double a);
t_point	rotate_z(t_point p0, double a);
#endif
