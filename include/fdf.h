/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:14:23 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/19 21:54:51 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include "math.h"

#include "time.h"

# define WIN_W 1920
# define WIN_H 1080
# define WIN_W_MID 920
# define WIN_H_MID 540
# define WINDOW_TITLE "bchanaa's FdF"

# define INFO_W 400
# define INFO_H WIN_H
# define INFO_X 35
# define INFO_Y 80
# define INFO_Y_INC 25

# define DEG_TO_RAD(a) (a * M_PI / 180)
# define RAD_TO_DEG(r) (r * 180 / M_PI)

# define C_WHITE 0xffffff
# define C_BLUE 0x4060ff
# define C_GREEN 0x02d15f
# define DEFAULT_BGCOLOR 0x212222

# define TR_FACTOR 22
# define ANGLE_FACTOR (DEG_TO_RAD(5))
# define ZOOM_FACTOR 0.1

# define ISOMETRIC 1
# define ORTHOGRAPHIC 0
# define DEFAULT_PROJECTION ISOMETRIC

typedef unsigned char t_uc;

# define BLUE(c) ((t_uc)c & 255)
# define GREEN(c) ((t_uc)((c & 255 << 8) >> 8))
# define RED(c) ((t_uc)((c & 255 << 16) >> 16))

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
	int		iright;
	int		ibottom;
} t_point;

typedef struct s_line_vars
{
	int	coords[2];
	int	delta[2];
	int	inc[2];
	int	err[2];
	int	steps[2];
}    t_line_vars;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_point		**map;
	void		*img;
	char		*img_addr;
	float		scale;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			map_width;
	int			map_height;
	int			map_w_mid;
	int			map_h_mid;
	int			map_ratio_mid;
	int			cell_size;
	float		sc_cell_size;
	float		cell_size_z;
	float		sc_cell_size_z;
	int			tx;
	int			ty;
	float		angle_x;
	float		angle_y;
	float		angle_z;
	int			min_z;
	int			max_z;
	int			mouse_x;
	int			mouse_y;
	bool		projection;
	bool		is_dragging;
	bool		has_color;
} t_data;

t_point			*parse_point(char *s, int x, int y, t_data *data);
int				fill_matrix_line(t_point **matrix, int x, int y, t_data *data);
int				get_map_width(t_list *lst, int height);
t_point			**parse_landscape(char *filename, t_data *data);
void			exit_wmsg(const char *msg);
void			free_2darray(void **arr, bool free_root_p);
void			draw_line(t_data *data, t_point *p1, t_point *p2);
int				render(t_data *data);
int				init_data(t_data *data);
int				init_window(t_data *data);
int				get_color_from_hex(char *hex);
int				count_split(char *str, char c);
int				init_image(t_data *data, int img_width, int img_height);
void			calc_cell_size(t_data *data);
unsigned int	get_gradient_color(int color1, int color2, float percentage);
void			translate_point(t_data *data, t_point *pt);
int				handle_translate(t_data *data, int keycode);
int				handle_rotate(t_data *data, int keycode);
void			handle_height_scale(t_data *data, int keycode);
t_point			transform(t_data *data, t_point *pt);
void			switch_projection(t_data *data);
void			reset_data(t_data *data);
int				close_window(t_data *data);
void			draw_info(t_data *data);
void			bline(t_data *data, t_point p1, t_point p2, t_line_vars *v);
void			rotate_x(int *y, int *z, float *angle);
void			rotate_y(int *x, int *z, float *angle);
void			rotate_z(int *x, int *y, float *angle);
void			draw_line2(t_data *data, t_point *p1, t_point *p2);
int				abs(int a);
void			color_image_point(t_data *data, int x, int y, unsigned int color);
void			set_color_scheme(t_uc scheme, t_data *data);
// Event handlers
int				handle_key_press(int keycode, t_data *data);
int				handle_mouse_click(int button, int x, int y, t_data *data);
int				handle_mouse_move(int x, int y, t_data *data);
int				handle_mouse_release(int button, int x, int y, t_data *data);

// Cleanup functions
void			free_data(t_data *data);
void			destroy_all(t_data *data);
int				close_window(t_data *data);
#endif
