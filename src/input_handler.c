/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:25:08 by mhonchar          #+#    #+#             */
/*   Updated: 2019/04/01 20:05:34 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
}

void		ft_mouse_zoom(t_win *win, double interpolation, int x, int y)
{
	double	m_re;
	double	m_im;

	m_re = (double)x / (WIDTH / (win->max_val.x - win->min_val.x))
		+ win->min_val.x;
	m_im = (double)y / (HEIGHT / (win->max_val.y - win->min_val.y))
		+ win->min_val.y;
	win->min_val.x = interpolate(m_re, win->min_val.x, interpolation);
	win->max_val.x = interpolate(m_re, win->max_val.x, interpolation);
	win->min_val.y = interpolate(m_im, win->min_val.y, interpolation);
	win->max_val.y = interpolate(m_im, win->max_val.y, interpolation);
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
	else if (frnumber == FR_SPINNER && win->ft_putfract != ft_pthread_spinner)
		ft_init_spinner(win);
	else if (frnumber == FR_BSHIP && win->ft_putfract != ft_pthread_bship)
		ft_init_bship(win);
}
