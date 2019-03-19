/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:01:05 by mhonchar          #+#    #+#             */
/*   Updated: 2019/03/19 20:38:36 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		ft_deal_key(int key, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (key == K_NUM_0)
		ft_bzero(((t_win *)param)->pix_ptr, WIDTH * HEIGHT);
	if (key == K_SPACEBAR)
	{
		if (win->col_offset == 8)
			win->col_offset = 1;
		else
			win->col_offset++;
	}
	if (key == K_ESC)
		exit(0);
	if (key == K_LEFT_ARROW || key == K_RIGTH_ARROW || key == K_UP_ARROW
		|| key == K_DOWN_ARROW)
		ft_move_img(win, key);
	if (key == K_NUM_PLUS)
		win->max_it += 20;
	if (key == K_NUM_MINUS && win->max_it > 100)
		win->max_it -= 20;
	ft_rewrite(win);
	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_win	*win;

	win = param;
	if (button == K_MOUSE_LEFT || button == K_MOUSE_WHEEL_UP)
	{
		ft_mouse_zoom(win, 0.9, x, y);
		ft_rewrite(win);
	}
	if (button == K_MOUSE_RIGHT || button == K_MOUSE_WHEEL_DOWN)
	{
		ft_mouse_zoom(win, 1.1, x, y);
		ft_rewrite(win);
	}
	printf("[%d]\n", button);
	return (0);
}

void	ft_rewrite(t_win *win)
{
	ft_bzero(win->pix_ptr, WIDTH * HEIGHT * 4);
	ft_pthread_mandelbrot(win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}

void	ft_win_init(t_win *win)
{
	int		bpp;
	int		size_line;
	int		endian;
	double	w;
	double	h;

	bpp = 32;
	size_line = WIDTH;
	endian = 0;
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIDTH, HEIGHT, "fract'ol");
	win->img_ptr = mlx_new_image(win->mlx_ptr, WIDTH, HEIGHT);
	win->pix_ptr = mlx_get_data_addr(win->img_ptr, &bpp, &size_line, &endian);
	w = 5;
	h = (w * HEIGHT) / WIDTH;
	win->min_val.x = -w / 2;
	win->min_val.y = -h / 2;
	win->max_val.x = win->min_val.x + w;
	win->max_val.y = win->min_val.y + h;
	win->max_it = 100;
	win->col_offset = 4;
	ft_rewrite(win);
}

int		main(int argc, char **argv)
{
	t_win	win;

	if (argc != 2)
	{
		ft_print_usage();
		return (0);
	}
	else if (ft_check_input(argv[1]))
	{
		ft_print_usage();
		return (0);
	}
	ft_win_init(&win);
	mlx_hook(win.win_ptr, 4, (1L << 0), mouse_press, (void*)&win);
	mlx_key_hook(win.win_ptr, ft_deal_key, (void*)&win);
	mlx_loop(win.mlx_ptr);
	return (0);
}
