/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:01:05 by mhonchar          #+#    #+#             */
/*   Updated: 2019/05/09 18:20:37 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_deal_key(int key, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (key == K_NUM_0)
		ft_set_default(win);
	else if (key == K_ESC)
		exit(0);
	else if (key == K_LEFT_ARROW || key == K_RIGTH_ARROW || key == K_UP_ARROW
		|| key == K_DOWN_ARROW)
		ft_move_img(win, key);
	else if (key == K_NUM_PLUS && win->max_it < 120)
		win->max_it += 10;
	else if (key == K_NUM_MINUS && win->max_it > 100)
		win->max_it -= 10;
	else if (key == K_SPACEBAR)
		win->julia_rotate = !win->julia_rotate;
	else if (key == K_R || key == K_G || key == K_B)
		ft_move_color(win, key);
	else if (key == K_1 || key == K_2 || key == K_3 ||
		key == K_4 || key == K_5 || key == K_6 || key == K_7 || key == K_8)
		ft_set_fractal(win, key);
	else if (key == K_H)
		win->help = !(win->help);
	ft_rewrite(win);
	return (0);
}

void	ft_rewrite(t_win *win)
{
	ft_bzero(win->pix_ptr, WIDTH * HEIGHT * 4);
	win->ft_putfract(win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	ft_put_help(win);
}

void	ft_init_win(t_win *win)
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
	ft_set_fractal(win, win->frnumber);
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
	else if ((win.frnumber = ft_check_input(argv[1])) == -1)
	{
		ft_print_usage();
		return (0);
	}
	ft_init_win(&win);
	mlx_hook(win.win_ptr, 4, (1L << 0), mouse_press, (void*)&win);
	mlx_hook(win.win_ptr, 6, (1L << 0), mouse_move, (void*)&win);
	mlx_key_hook(win.win_ptr, ft_deal_key, (void*)&win);
	mlx_loop(win.mlx_ptr);
	return (0);
}
