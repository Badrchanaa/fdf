/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:03:46 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/21 21:53:57 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>
#include <fcntl.h>

t_point	**parse_landscape(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	t_list	*lst;

	data->map_height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	lst = NULL;
	while (line)
	{
		ft_lstadd_back(&lst, ft_lstnew(line));
		(data->map_height)++;
		line = get_next_line(fd);
	}
	data->map = get_land_matrix(lst, data->map_height, &(data->map_width));
	ft_lstclear(&lst, free);
	return(data->map);
}

// int main2()
// {
// 	t_point **matrix;
// 	int		height;
// 	int		width;
// 	int		x;

// 	height = 0;
// 	width = 0;
// 	matrix = parse_landscape("test_maps/42.fdf", &width, &height);
// 	int y = 0;
// 	printf("height: %d\n", height);
// 	printf("width: %d\n", width);
// 	while (y < height)
// 	{
// 		x = 0;
// 		while (x < width)
// 		{
// 			t_point *pt = matrix[(y * width) + x];
// 			printf("x: %d y: %d z: %d c: %d\n", pt->x, pt->y, pt->z, pt->color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	printf("total points: %d (bytes: %lu)\n", width * height, sizeof(t_point *) * ( width * height + 1));
// 	free_2darray((void **)matrix, true);
// 	return (0);
// }

// int main()
// {
// 	main2();
// 	return (0);
// }