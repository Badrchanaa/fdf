/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:42:28 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/16 18:47:37 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdio.h>

int	handle_mouse_click(int button, int x, int y, void *p)
{
	static int count;
	(void)p;
	count++;
	ft_printf("[%d] x: %d y: %d button: %d.\n", count, x, y, button);
	return (0);
}

int handle_mouse_move(int x, int y, int *a)
{
	static int count;
	count++;
	printf("x: %d y: %d a: %d\n", x, y, *a);
	return (0);
}

int	main(int argc, char **argv)
{
	void	*p_win;
	void	*p_mlx;
	int		a;

	a = 1337;
	(void)argc;
	(void)argv;
	p_mlx = mlx_init();
	if (!p_mlx)
		return (1);
	p_win = mlx_new_window(p_mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	if (!p_win)
		return (1);
	for (int i=0; i < 50; i++)
	{
		for(int j=0; j < 50; j++)
		{
			mlx_pixel_put(p_mlx, p_win, 200 + i, 200 + j, 0xFFFFFF);
		}
	}
	ft_printf("colored\n");
	mlx_mouse_hook(p_win, handle_mouse_click, &a);
	mlx_hook(p_win, 6, 0, handle_mouse_move, &a);
	mlx_loop(p_mlx);
	return (0);
}
