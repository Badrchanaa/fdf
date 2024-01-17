/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:14:23 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/17 22:47:34 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// ADD USAGE TO INFO
// ADD TERRAIN COLOR SCHEME
// FIX ZOOM ISSUE WHEN SWITCHING PROJECTION
// FIX SWTICH PROJECTION ISSUE
#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include "math.h"

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
# define ANGLE_FACTOR (DEG_TO_RAD(2))
# define ZOOM_FACTOR 0.1

# define ISOMETRIC 1
# define ORTHOGRAPHIC 0
# define DEFAULT_PROJECTION ISOMETRIC

typedef unsigned char t_uc;

# define BLUE(c) ((t_uc)c & 255)
# define GREEN(c) ((t_uc)((c & 255 << 8) >> 8))
# define RED(c) ((t_uc)((c & 255 << 16) >> 16))

// # define MALLOC_ERR_MSG "Error: malloc error"

typedef struct s_point
{
	int		z;
	int		color;
	short	x;
	short	y;
	int		ileft;
	int		ibottom;
} t_point;

typedef struct s_line_vars
{
	double			percent;
	int				dx;
	int				steps;
	int				steps_i;
	int				dy;
	int				sx;
	int				sy;
	int				error;
} t_line_vars;

typedef struct s_data
{
	t_line_vars	*line_vars;
	void		*mlx;
	void		*win;
	t_point		**map;
	t_point		*draw_p1;
	t_point		*draw_p2;
	void		*img;
	char		*img_addr;
	double		scale;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			map_width;
	int			map_height;
	int			map_w_mid;
	int			map_h_mid;
	int			cell_size;
	double		sc_cell_size;
	int			cell_size_z;
	double		sc_cell_size_z;
	int			tx;
	int			ty;
	double		angle_x;
	double		angle_y;
	double		angle_z;
	double		cos_x;
	double		cos_y;
	double		cos_z;
	double		sin_x;
	double		sin_y;
	double		sin_z;
	int			min_z;
	int			max_z;
	short		mouse_x;
	short		mouse_y;
	bool		projection;
	bool		is_dragging;
	bool		has_color;
} t_data;

t_point			**get_map_matrix(t_list *lst, t_data *data);
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
unsigned int	get_gradient_color(int color1, int color2, double percentage);
void			translate_point(t_data *data, t_point *pt);
int				handle_translate(t_data *data, int keycode);
int				handle_rotate(t_data *data, int keycode);
void			rotate_point(t_data *data, t_point *pt);
void			transform_point(t_data *data, t_point *pt);
void			switch_projection(t_data *data);
void			reset_data(t_data *data);
int				close_window(t_data *data);
void			draw_info(t_data *data);
void			bline(t_data *data, t_point *p1, t_point *p2);
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
