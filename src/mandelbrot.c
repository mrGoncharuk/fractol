/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:55:44 by mhonchar          #+#    #+#             */
/*   Updated: 2019/03/19 19:26:26 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void			ft_pp_img(char *pixels, int x, int y, int color)
{
	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
		*(int *)(pixels + (WIDTH * y + x) * 4) = color;
}

void			ft_create_color(t_win *win, int n)
{
	int		br;

	if (n != win->max_it)
	{
		br = (n * 16) % 256;
		ft_pp_img(win->pix_ptr, win->i, win->j, (br | br << win->col_offset
			| br << win->col_offset * 2));
	}
	else
		ft_pp_img(win->pix_ptr, win->i, win->j, 0xFFFFFF);
}

void			ft_draw_fractal(t_win *win, double x, double y)
{
	int		n;
	double	z_re;
	double	z_im;
	double	z_resqr;
	double	z_imsqr;

	z_re = 0;
	z_im = 0;
	z_resqr = z_re * z_re;
	z_imsqr = z_im * z_im;
	n = -1;
	while (z_resqr + z_imsqr <= 4.0 && ++n < win->max_it)
	{
		z_im = ft_pow(z_re + z_im, 2) - z_resqr - z_imsqr;
		z_im += y;
		z_re = z_resqr - z_imsqr + x;
		z_resqr = z_re * z_re;
		z_imsqr = z_im * z_im;
	}
	ft_create_color(win, n);
}

void			*ft_mandelbrot(void *w)
{
	t_win		*win;
	double		x;
	double		y;

	win = (t_win *)w;
	y = win->min_val.y + win->dy * win->j;
	while (win->j < win->j_max)
	{
		win->i = -1;
		x = win->min_val.x;
		while (++win->i < WIDTH)
		{
			ft_draw_fractal(win, x, y);
			x += win->dx;
		}
		y += win->dy;
		win->j++;
	}
	return (w);
}

void			ft_pthread_mandelbrot(t_win *win)
{
	pthread_t	pt[THREADS_AMOUNT];
	t_win		w[THREADS_AMOUNT];
	int			i;

	win->dx = (win->max_val.x - win->min_val.x) / (WIDTH);
	win->dy = (win->max_val.y - win->min_val.y) / (HEIGHT);
	i = 0;
	while (i < THREADS_AMOUNT - 1)
	{
		ft_memcpy((void*)&w[i], (void*)win, sizeof(t_win));
		w[i].j = (HEIGHT / THREADS_AMOUNT) * i;
		w[i].j_max = (HEIGHT / THREADS_AMOUNT) * (i + 1);
		i++;
	}
	ft_memcpy((void*)&w[i], (void*)win, sizeof(t_win));
	w[i].j = (HEIGHT / THREADS_AMOUNT) * i;
	w[i].j_max = HEIGHT;
	i = -1;
	while (++i < THREADS_AMOUNT)
		pthread_create((pt + i), NULL, ft_mandelbrot, (void*)(w + i));
	i = -1;
	while (++i < THREADS_AMOUNT)
		pthread_join(pt[i], NULL);
}
