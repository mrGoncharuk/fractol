/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:01:05 by mhonchar          #+#    #+#             */
/*   Updated: 2019/03/20 21:41:28 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		ft_deal_key(int key, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (key == K_NUM_0)
		ft_set_default(win);
	if (key == K_ESC)
		exit(0);
	if (key == K_LEFT_ARROW || key == K_RIGTH_ARROW || key == K_UP_ARROW
		|| key == K_DOWN_ARROW)
		ft_move_img(win, key);
	if (key == K_NUM_PLUS)
		win->max_it += 20;
	if (key == K_NUM_MINUS && win->max_it > 100)
		win->max_it -= 20;
	if (key == K_R || key == K_G || key == K_B)
		ft_move_color(win, key);
	if (key == K_1 || key == K_2)
		ft_set_fractal(win, key);
	printf("[key = %d]\n", key);
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
	win->ft_putfract(win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}

void	ft_init_win(t_win *win, int frnumber)
{
	int		bpp;
	int		size_line;
	int		endian;

	bpp = 32;
	size_line = WIDTH;
	endian = 0;
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIDTH, HEIGHT, "fract'ol");
	win->img_ptr = mlx_new_image(win->mlx_ptr, WIDTH, HEIGHT);
	win->pix_ptr = mlx_get_data_addr(win->img_ptr, &bpp, &size_line, &endian);
	win->ft_putfract = NULL;
	ft_set_fractal(win, frnumber);
	ft_rewrite(win);
}

int		main(int argc, char **argv)
{
	t_win	win;
	int		frnumber;

	if (argc != 2)
	{
		ft_print_usage();
		return (0);
	}
	else if ((frnumber = ft_check_input(argv[1])) == -1)
	{
		ft_print_usage();
		return (0);
	}
	ft_init_win(&win, frnumber);
	mlx_hook(win.win_ptr, 4, (1L << 0), mouse_press, (void*)&win);
	mlx_key_hook(win.win_ptr, ft_deal_key, (void*)&win);
	mlx_loop(win.mlx_ptr);
	return (0);
}
