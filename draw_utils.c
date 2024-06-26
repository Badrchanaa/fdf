/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:51:03 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/19 21:41:00 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color_image_point(t_data *data, int x, int y, unsigned int color)
{
	if (x >= 0 && y >= 0 && x < WIN_W && y < WIN_H)
	{
		*(unsigned int *)(data->img_addr + y * data->size_line + x * (data->bits_per_pixel / 8)) = color;
	}
}

void	draw_line(t_data *data, t_point *p1, t_point *p2)
{
	int		i;
	int		dx;
	int		dy;
	float	c_percent;
	int		p_color;
	float	dist;

	i = 0;	
	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	dist = sqrt(pow(dx, 2) + pow(dy, 2));
	while (i < (int)dist)
	{
		c_percent = (float)i / (float)dist;
		p_color = get_gradient_color(p1->color, p2->color, c_percent);
		color_image_point(data, p1->x + dx / dist * i,
						p1->y + (dy / dist * i), p_color);
		i++;
	}
}

void	clear_image(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_W)
	{
		j = 0;
		while (j < WIN_H)
		{
				color_image_point(data, i, j, DEFAULT_BGCOLOR);
			j++;
		}
		i++;
	}
}

void	draw_number(t_data *data, unsigned int pos, int num, char *prefix)
{
	char	*str;
	char	*tmp;

	tmp = ft_itoa(num);
	if (!tmp)
		return ;
	str = ft_strjoin(prefix, tmp);
	free(tmp);
	if (!str)
		return;
	mlx_string_put(data->mlx, data->win, (pos << 16) >> 16, (pos >> 16), C_WHITE, str);
	free(str);
}

void	draw_info(t_data *data)
{
	draw_number(data, (80 << 16) | INFO_X, data->map_width, "MAP WIDTH   : ");
	draw_number(data, (105 << 16) | INFO_X, data->map_height, "MAP HEIGHT  : ");
	draw_number(data, (130 << 16) | INFO_X, RAD_TO_DEG(data->angle_x), "X ANGLE : ");
	draw_number(data, (155 << 16) | INFO_X, RAD_TO_DEG(data->angle_y), "Y ANGLE : ");
	draw_number(data, (180 << 16) | INFO_X, RAD_TO_DEG(data->angle_z), "Z ANGLE : ");
	draw_number(data, (205 << 16) | INFO_X, data->cell_size_z, "HEIGHT FACTOR : ");
	draw_number(data, (230 << 16) | INFO_X, data->scale * 10, "ZOOM (x10): ");
}

void	draw_usage_info(t_data *data)
{
	mlx_string_put(data->mlx, data->win, INFO_X, INFO_Y + 210, C_WHITE, "USAGE:");
	mlx_string_put(data->mlx, data->win, INFO_X, INFO_Y + 242, C_WHITE, "  +/- Height Factor : < >");
	mlx_string_put(data->mlx, data->win, INFO_X, INFO_Y + 264, C_WHITE, "  Rotate X : I O ");
	mlx_string_put(data->mlx, data->win, INFO_X, INFO_Y + 286, C_WHITE, "  Rotate Y : K L ");
	mlx_string_put(data->mlx, data->win, INFO_X, INFO_Y + 308, C_WHITE, "  Rotate Z : N M ");
	mlx_string_put(data->mlx, data->win, INFO_X, INFO_Y + 330, C_WHITE, "  Switch projection : S");
	mlx_string_put(data->mlx, data->win, INFO_X, INFO_Y + 352, C_WHITE, "  Reset map : R");
	mlx_string_put(data->mlx, data->win, INFO_X, INFO_Y + 374, C_WHITE, "  Translate : Arrows or Left click & drag");
}

int	render(t_data *data)
{
	int			i;
	t_point		**map;
	t_point 	*pt;
	t_line_vars	v;

	i = 0;
	clear_image(data);
	map = data->map;
	while (map[i])
	{
		pt = map[i];
		if (pt->iright != -1)
			bline(data, transform_point(data, pt), transform_point(data, map[pt->iright]), &v);
		if (pt->ibottom != -1)
			bline(data, transform_point(data, pt), transform_point(data, map[pt->ibottom]), &v);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	draw_info(data);
	draw_usage_info(data);
	return (0);
}