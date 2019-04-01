/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:25:07 by mhonchar          #+#    #+#             */
/*   Updated: 2019/04/01 18:52:34 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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


void	ft_draw_fractal(t_frac *win, double x, double y)
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
		z_im = ft_square(z_re + z_im) - z_resqr - z_imsqr;
		z_im += y;
		z_re = z_resqr - z_imsqr + x;
		z_resqr = ft_square(z_re);
		z_imsqr = ft_square(z_im);
	}
	ft_create_color(win, n);
}

void	*ft_mandelbrot(void *w)
{
	t_frac		*win;
	double		x;
	double		y;
	//int		color;	

	
	win = (t_frac *)w;
	printf("threaded [j = %d] [j_max = %d]\n", win->j, win->j_max);
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


void			ft_draw_bship(t_win *win, double x, double y)
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
        // z_im = ft_abs(z_im);
		// z_re = ft_abs(z_re);
		z_im = ft_pow(z_re + z_im, 2) - z_resqr - z_imsqr;
		z_im += y;
		z_re = fabs(z_resqr - z_imsqr + x);
		z_resqr = z_re * z_re;
		z_imsqr = z_im * z_im;
	}
	ft_create_color(win, n);
}


void	ft_pthread_mandelbrot(t_win *win)
{
	pthread_t	pt[THREADS_AMOUNT];
	t_frac		w[THREADS_AMOUNT];
	int			i;

	win->dx = (win->max_val.x - win->min_val.x) / (WIDTH);
	win->dy = (win->max_val.y - win->min_val.y) / (HEIGHT);
	i = 0;
	while (i < THREADS_AMOUNT - 1)
	{
		printf("kek\n");
		ft_memcpy((void*)&w[i], ((void*)win + sizeof(void *) * 3), sizeof(t_win) - (sizeof(void *) + sizeof(int)) * 3);
		w[i].j = (HEIGHT / THREADS_AMOUNT) * i;
		printf("kek\n");
		w[i].j_max = (HEIGHT / THREADS_AMOUNT) * (i + 1);

		printf("[i = %d] [j = %d] [j_max = %d]\n", i, w[i].j, w[i].j_max);
		i++;
	}
	w[i].j = (HEIGHT / THREADS_AMOUNT) * i;
	w[i].j_max = HEIGHT;
	printf("[i = %d] [j = %d] [j_max = %d]\n", i, w[i].j, w[i].j_max);
	i = -1;
	while (++i < THREADS_AMOUNT)
		pthread_create((pt + i), NULL, ft_mandelbrot, (void*)(w + i));
	i = -1;
	
	while (++i < THREADS_AMOUNT)
	{
		printf("[i = %d]\n", i);
		pthread_join(pt[i], NULL);
	}
}




