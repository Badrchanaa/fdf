/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:14:23 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/22 18:50:50 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <X11/Xlib.h>
# include "mlx.h"
# include "libft.h"
# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include "math.h"
# include "keysym.h"

# define WIN_W 1380
# define WIN_H 720
# define WIN_W_MID (WIN_W / 2)
# define WIN_H_MID (WIN_H / 2)
# define WINDOW_TITLE "bchanaa's FdF"

# define INFO_X 35
# define INFO_Y 80

# define ZOOM_MIN 0.5
# define ZOOM_MAX 3

# define C_WHITE 0xffffff
# define C_BLUE 0x4060ff
# define C_GREEN 0x02d15f
# define DEFAULT_BGCOLOR 0x212222

# define TR_FACTOR 22
// 5 Degrees in radian
# define ANGLE_FACTOR 0.0872665
# define ISO_ANGLE_X 0.872665
# define ISO_ANGLE_Y 0.698132
# define ISO_ANGLE_Z 5.8294
# define ZOOM_FACTOR 0.1

# define ISOMETRIC 1
# define ORTHOGRAPHIC 0
# define DEFAULT_PROJECTION ISOMETRIC

typedef unsigned char	t_uc;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
	int		iright;
	int		ibottom;
}				t_point;

typedef struct s_line_vars
{
	t_point	p1;
	t_point	p2;
	int		coords[2];
	int		delta[2];
	int		inc[2];
	int		err[2];
	int		steps[2];
}			t_line_vars;

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
	volatile bool		is_locked;
}				t_data;

t_point			*parse_point(char *s, int x, int y, t_data *data);
int				fill_matrix_line(t_point **matrix, int x, int y, t_data *data);
int				get_map_width(t_list *lst, int height);
t_point			**parse_landscape(char *filename, t_data *data);
void			exit_wmsg(int err, char *str);
void			free_2darray(void **arr, bool free_root_p);
int				render(t_data *data);
int				init_data(t_data *data);
int				init_window(t_data *data);
int				get_color_from_hex(char *hex);
int				count_split(char *str, char c);
int				init_image(t_data *data, int img_width, int img_height);
void			calc_cell_size(t_data *data);
unsigned int	get_gradient_color(int color1, int color2, float percentage);
int				handle_rotate(t_data *data, int keycode);
void			handle_height_scale(t_data *data, int keycode);
t_point			*transform(t_data *data, t_point *pt, t_point *npt);
void			switch_projection(t_data *data);
void			reset_data(t_data *data);
void			draw_info(t_data *data);
void			bline(t_data *data, t_point *p1, t_point *p2, t_line_vars *v);
void			rotate_x(int *y, int *z, float *angle);
void			rotate_y(int *x, int *z, float *angle);
void			rotate_z(int *x, int *y, float *angle);
int				abs(int a);
int				rad_to_deg(double rad);
void			color_image_point(t_data *data, int x, int y, \
									unsigned int color);
void			set_map_color(t_data *data);
t_uc			red(unsigned int color);
t_uc			green(unsigned int color);
t_uc			blue(unsigned int color);
// Event handlers
int				handle_key_press(int keycode, t_data *data);
int				handle_mouse_click(int button, int x, int y, t_data *data);
int				handle_mouse_move(int x, int y, t_data *data);
int				handle_mouse_release(int button, int x, int y, t_data *data);

// Cleanup functions
void			destroy_all(t_data *data);
int				close_window(t_data *data);
#endif
