/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:14:23 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/12 22:43:45 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# include "math.h"

# define WIN_W 1920
# define WIN_H 1080
# define WINDOW_TITLE "bchanaa's FdF"
# define C_WHITE 16777215
# define TR_FACTOR 25

# define BLUE(c) ((t_uc)c & 255)
# define GREEN(c) (((t_uc)c & (255 << 8)) >> 8)
# define RED(c) (((t_uc)c & (255 << 16)) >> 16)
# define DEG_TO_RAD(a) (a * M_PI / 180)
// # define MALLOC_ERR_MSG "Error: malloc error"

typedef unsigned char t_uc;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
} t_point;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_point	**map;
	void	*img;
	char	*img_addr;
	double	scale;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		map_width;
	int		map_height;
	int		cell_size;
	int		cell_size_z;
	int		tx;
	int		ty;
	int		angle_x;
	int		angle_y;
	int		angle_z;
} t_data;


t_point			**get_land_matrix(t_list *lst, int height, int *width);
t_point			**parse_landscape(char *filename, t_data *data);
void			exit_wmsg(const char *msg);
void			free_2darray(void **arr, bool free_root_p);
void			draw_line(t_data *data, t_point *p1, t_point *p2);
int				draw_land(t_data *data);
void			init_data(t_data *data);
int				init_window(t_data *data);
int				get_color_from_hex(char *hex);
int				count_split(char *str, char c);
int				init_image(t_data *data, int img_width, int img_height);
void			calc_cell_size(t_data *data);
unsigned int	get_gradient_color(int color1, int color2, double percentage);
int				translate(t_data *data, int keycode);
int				handle_rotate(t_data *data, int keycode);
t_point			*rotate_point(t_data *data, t_point *pt);

#endif
