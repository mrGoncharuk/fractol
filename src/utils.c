/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 19:51:37 by mhonchar          #+#    #+#             */
/*   Updated: 2019/03/20 21:41:55 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_pp_img(char *pixels, int x, int y, int color)
{
	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
		*(int *)(pixels + (WIDTH * y + x) * 4) = color;
}

void			ft_move_color(t_win *win, int key)
{
	if (key == K_R)
		win->red++;
	if (key == K_G)
		win->green++;
	if (key == K_B)
		win->blue++;
}

void			ft_create_color(t_win *win, int it)
{
	double		k;
	int			color;

	k = it * log(2);
	if (it != win->max_it)
		color = (int)(win->red * k) | (int)(win->green * k) << 8 |
			(int)(win->blue * k) << 16;
	else
		color = 0xFFFFFF;
	ft_pp_img(win->pix_ptr, win->i, win->j, color);
}

double			interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

void			ft_set_default(t_win *win)
{
	double		w;
	double		h;

	w = 5;
	h = (w * HEIGHT) / WIDTH;
	win->min_val.x = -w / 2;
	win->min_val.y = -h / 2;
	win->max_val.x = win->min_val.x + w;
	win->max_val.y = win->min_val.y + h;
	win->max_it = 100;
	win->red = 5;
	win->green = 9;
	win->blue = 25;
}
