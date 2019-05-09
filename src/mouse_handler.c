/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:14:10 by mhonchar          #+#    #+#             */
/*   Updated: 2019/05/09 17:56:15 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			mouse_press(int button, int x, int y, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (button == K_MOUSE_LEFT)
	{
		ft_mouse_zoom(win, 0.9, x, y);
		ft_rewrite(win);
	}
	if (button == K_MOUSE_RIGHT)
	{
		ft_mouse_zoom(win, 1.1, x, y);
		ft_rewrite(win);
	}
	if (button == K_MOUSE_WHEEL_UP)
	{
		ft_wheel_zoom(win, 0.9);
		ft_rewrite(win);
	}
	if (button == K_MOUSE_WHEEL_DOWN)
	{
		ft_wheel_zoom(win, 1.1);
		ft_rewrite(win);
	}
	return (0);
}

int			mouse_move(int x, int y, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (win->julia_rotate)
	{
		win->c_re = ((double)x / WIDTH) * 2 - 1;
		win->c_im = ((double)y / HEIGHT) * 2 - 1;
	}
	ft_rewrite(win);
	return (0);
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

void		ft_wheel_zoom(t_win *win, double interpolation)
{
	double	m_re;
	double	m_im;

	m_re = (double)(WIDTH / 2) / (WIDTH / (win->max_val.x - win->min_val.x))
		+ win->min_val.x;
	m_im = (double)(HEIGHT / 2) / (HEIGHT / (win->max_val.y - win->min_val.y))
		+ win->min_val.y;
	win->min_val.x = interpolate(m_re, win->min_val.x, interpolation);
	win->max_val.x = interpolate(m_re, win->max_val.x, interpolation);
	win->min_val.y = interpolate(m_im, win->min_val.y, interpolation);
	win->max_val.y = interpolate(m_im, win->max_val.y, interpolation);
}
