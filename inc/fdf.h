/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:28:02 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/15 16:52:35 by kbarru           ###   ########lyon.fr   */
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

# define ANGLE 0.39269908169

# ifndef INT_MIN
#  define INT_MIN -2147483648
# endif

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

# define DEFAULT_ROT_X 0.79
# define DEFAULT_ROT_Y 0.38
# define DEFAULT_ROT_Z 2

# define X_AXIS 0
# define Y_AXIS 1
# define Z_AXIS 2

# define DEF_TR_STEP 50
# define DEF_SCALE_STEP 1
# define DEF_EXT_STEP 1

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
	double	min;
	double	max;
	t_point	**map;
}			t_map;

typedef struct s_scene
{
	t_map	*map;
	size_t	scale;
	double	rot[3];
	double	tr[3];
	int		ext;
}			t_scene;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*img;
	int		map_fd;
	t_scene	*scene;
}			t_vars;

/* parsing.c */
/*static size_t count_words(char *s, char sep);*/
int		check_arg(char *str);
int		open_map(char map_filename[]);
void	read_map(t_vars *vars);

/* bresenham.c */
void	bresenham(int diff, t_point a, t_point b, t_data img);

/* error.c */
void	invalid_map(t_vars *vars, char last_line[]);
int		usage(void);
void	destroy_map(t_map *map);
int		free_exit(t_vars *vars, int exit_status);
void	free_arr(t_point **arr, size_t n);

/* dynamic_array_utils.c */
void	double_array_size(t_vars *vars);

/* graphics.c */
void	render_scene(t_scene *scene);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_map(t_map *map, t_data img);
int		z_to_color(int diff, double value);
void	render_map(t_vars *vars);

/* init.c */
void	init_map(t_vars *vars, size_t len);
void	init_scene(t_vars *vars);
int		init_mlx_data(t_vars *vars, char map_filename[]);

/* scale.c */
size_t	determine_scale(t_map *map);
void	center_map(t_scene *scene);

/* rotation.c */
void	rotate_map(t_map *map, double a, t_point (*r_f)(t_point pt, double a));
t_point	rotate_x(t_point p0, double a);
t_point	rotate_y(t_point p0, double a);
t_point	rotate_z(t_point p0, double a);

/* point_utils.c */
t_point	create_point(double x, double y, double z);
int		get_value(char *line, int x);
void	apply_translation(t_scene scene, t_point *point);
void	apply_extrusion(t_scene scene, t_point *point, double min);

/* point_utils_2.c */
double	get_minimum(t_map *map);
double	get_maximum(t_map *map);

/* hooks.c */
int		key_hook_2(int keycode, t_vars *vars);
int		key_hook(int keycode, t_vars *vars);

/* setters.c */

void	set_tr(t_vars *vars, double tx, double ty, double tz);
void	set_scale(t_vars *vars, size_t scale);
void	set_ext(t_vars *vars, int ext);
void	set_rot(t_vars *vars, double ax, double ay, double az);

/* updaters.c */
void	update_rot(t_vars *vars, size_t axe, double angle);
void	update_translation(t_vars *vars, size_t dir, int delta);
void	update_scale(t_vars *vars, int scale_delta);
void	update_extrusion(t_vars *vars, int ext);

#endif
