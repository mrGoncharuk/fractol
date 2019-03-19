/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:25:08 by mhonchar          #+#    #+#             */
/*   Updated: 2019/03/19 20:39:01 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			ft_check_input(char *fract_name)
{
	if (!ft_strcmp(fract_name, "1") || !ft_strcmp(fract_name, "mandelbrot"))
		return (0);
	return (-1);
}

void		ft_print_usage(void)
{
	ft_putendl("Usage: ./fractol [fractal_name/fractal_number]");
	ft_putendl("Available fractals:");
	ft_putendl("1. Mandelbrot");
	ft_putendl("2. Julia");
}

double		interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
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
