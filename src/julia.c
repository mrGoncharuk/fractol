/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 19:04:46 by mhonchar          #+#    #+#             */
/*   Updated: 2019/05/09 16:46:03 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_init_julia(t_win *win)
{
	ft_bzero(win->pix_ptr, WIDTH * HEIGHT * sizeof(int));
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	ft_set_default(win);
	win->julia_rotate = 1;
	win->ft_putfract = ft_pthread_julia;
}

void			ft_draw_julia(t_win *win, double x, double y)
{
	int		n;
	double	z_re;
	double	z_im;
	double	z_resqr;
	double	z_imsqr;

	z_re = x;
	z_im = y;
	z_resqr = z_re * z_re;
	z_imsqr = z_im * z_im;
	n = -1;
	while (z_resqr + z_imsqr <= 4.0 && ++n < win->max_it)
	{
		z_im = ft_pow(z_re + z_im, 2) - z_resqr - z_imsqr;
		z_im += win->c_im;
		z_re = z_resqr - z_imsqr + win->c_re;
		z_resqr = z_re * z_re;
		z_imsqr = z_im * z_im;
	}
	ft_create_color(win, n);
}

void			*ft_julia(void *w)
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
			ft_draw_julia(win, x, y);
			x += win->dx;
		}
		y += win->dy;
		win->j++;
	}
	return (w);
}

void			ft_pthread_julia(t_win *win)
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
		pthread_create((pt + i), NULL, ft_julia, (void*)(w + i));
	i = -1;
	while (++i < THREADS_AMOUNT)
		pthread_join(pt[i], NULL);
}
