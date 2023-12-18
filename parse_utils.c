/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:54:51 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/18 22:02:47 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>
#include <fcntl.h>

t_point	get_point(char *s)
{
	t_point	*point;
	int		color;
	char	**arr;
	char	*
	if (!s)
		return (NULL);
	if (strchr(s, ','))
	{
		arr = ft_split(s, ',');
		color = arr[1];
		s = arr;
	}
}

t_point	*map_list_to_matrix(t_list *lst, int height)
{
	t_list	*curr;
	t_point	*map_matrix;
	char	**arr;
	int		width;

	if (!lst)
		return (NULL);
	curr = lst;
	arr = ft_split(lst->content, ' ');
	width = 
	map_matrix = malloc(sizeof(t_point *) * (lst_size * width));
	while (curr)
	{
		ft_split(curr, ' ');
		curr = curr->next;
	}	
}

t_point	*parse_map(char *filename)
{
	int		fd;
	char	*line;
	t_list	*lst;
	int		map_height;
	t_point	*map;

	map_height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	lst = NULL;
	while (line)
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_split(line, ' '));
		map_height++;
		free(line);
		line = get_next_line(fd);
	}
	map = map_list_to_matrix(lst, height);
		
}