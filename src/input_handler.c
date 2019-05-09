/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:25:08 by mhonchar          #+#    #+#             */
/*   Updated: 2019/05/09 18:13:19 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_put_help(t_win *win)
{
	mlx_string_put(win->mlx_ptr, win->win_ptr, 50, 25, C_YELLOW,
		"Press H to toggle help menu");
	if (win->help == 1)
	{
		mlx_string_put(win->mlx_ptr, win->win_ptr, 50, 40, C_YELLOW,
			"Zoom fractal: mouse button/wheel");
		mlx_string_put(win->mlx_ptr, win->win_ptr, 50, 55, C_YELLOW,
			"Move image: arrows");
		mlx_string_put(win->mlx_ptr, win->win_ptr, 50, 70, C_YELLOW,
			"Play with colors: R, G, B");
		mlx_string_put(win->mlx_ptr, win->win_ptr, 50, 85, C_YELLOW,
			"Swap fractal: 1-8");
		mlx_string_put(win->mlx_ptr, win->win_ptr, 50, 100, C_YELLOW,
			"Stop/Start Julia rotation: spacebar");
		mlx_string_put(win->mlx_ptr, win->win_ptr, 50, 115, C_YELLOW,
			"Change iterations: NUM_PLUS/MINUS");
		mlx_string_put(win->mlx_ptr, win->win_ptr, 50, 130, C_YELLOW,
			"Set default position: Num 0");
		mlx_string_put(win->mlx_ptr, win->win_ptr, 50, 145, C_YELLOW,
			"Exit: Esc");
	}
}

int			ft_check_input(char *fract_name)
{
	if (!ft_strcmp(fract_name, "1") || !ft_strcmp(fract_name, "mandelbrot"))
		return (FR_MANDELBROT);
	if (!ft_strcmp(fract_name, "2") || !ft_strcmp(fract_name, "julia"))
		return (FR_JULIA);
	if (!ft_strcmp(fract_name, "3") || !ft_strcmp(fract_name, "burningship"))
		return (FR_BSHIP);
	if (!ft_strcmp(fract_name, "4") || !ft_strcmp(fract_name, "spinner"))
		return (FR_SPINNER);
	if (!ft_strcmp(fract_name, "5") || !ft_strcmp(fract_name, "fish"))
		return (FR_FISH);
	if (!ft_strcmp(fract_name, "6") || !ft_strcmp(fract_name, "flower"))
		return (FR_FLOWER);
	if (!ft_strcmp(fract_name, "7") || !ft_strcmp(fract_name, "heart"))
		return (FR_HEART);
	if (!ft_strcmp(fract_name, "8") || !ft_strcmp(fract_name, "splash"))
		return (FR_SPLASH);
	return (-1);
}

void		ft_print_usage(void)
{
	ft_putendl("Usage: ./fractol [fractal_name/fractal_number]");
	ft_putendl("Available fractals:");
	ft_putendl("1. mandelbrot");
	ft_putendl("2. julia");
	ft_putendl("3. burningship");
	ft_putendl("4. spinner");
	ft_putendl("5. fish");
	ft_putendl("6. flower");
	ft_putendl("7. heart");
	ft_putendl("8. splash");
}

void		ft_move_img(t_win *win, int key)
{
	double	x_move_pow;
	double	y_move_pow;

	x_move_pow = 25 / (WIDTH / (win->max_val.x - win->min_val.x));
	y_move_pow = 25 / (HEIGHT / (win->max_val.y - win->min_val.y));
	if (key == K_LEFT_ARROW)
	{
		win->min_val.x -= x_move_pow;
		win->max_val.x -= x_move_pow;
	}
	else if (key == K_RIGTH_ARROW)
	{
		win->min_val.x += x_move_pow;
		win->max_val.x += x_move_pow;
	}
	else if (key == K_DOWN_ARROW)
	{
		win->min_val.y += y_move_pow;
		win->max_val.y += y_move_pow;
	}
	else if (key == K_UP_ARROW)
	{
		win->min_val.y -= y_move_pow;
		win->max_val.y -= y_move_pow;
	}
}

void		ft_set_fractal(t_win *win, int frnumber)
{
	if (frnumber == FR_MANDELBROT && win->ft_putfract != ft_pthread_mandelbrot)
		ft_init_mandelbrot(win);
	else if (frnumber == FR_JULIA && win->ft_putfract != ft_pthread_julia)
		ft_init_julia(win);
	else if (frnumber == FR_SPINNER && win->ft_putfract != ft_pthread_spinner)
		ft_init_spinner(win);
	else if (frnumber == FR_BSHIP && win->ft_putfract != ft_pthread_bship)
		ft_init_bship(win);
	else if (frnumber == FR_JULIA && win->ft_putfract != ft_pthread_julia)
		ft_init_julia(win);
	else if (frnumber == FR_FISH && win->ft_putfract != ft_pthread_fish)
		ft_init_fish(win);
	else if (frnumber == FR_FLOWER && win->ft_putfract != ft_pthread_flower)
		ft_init_flower(win);
	else if (frnumber == FR_HEART && win->ft_putfract != ft_pthread_heart)
		ft_init_heart(win);
	else if (frnumber == FR_SPLASH && win->ft_putfract != ft_pthread_splash)
		ft_init_splash(win);
}
