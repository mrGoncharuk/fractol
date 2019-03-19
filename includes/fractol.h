/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:01:02 by mhonchar          #+#    #+#             */
/*   Updated: 2019/03/19 20:38:50 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>
# define WIDTH 1600
# define HEIGHT 900
# define THREADS_AMOUNT 4

# define K_MOUSE_LEFT 1
# define K_MOUSE_RIGHT 2
# define K_MOUSE_WHEEL_DOWN 4
# define K_MOUSE_WHEEL_UP 5
# define K_LEFT_ARROW 123
# define K_RIGTH_ARROW 124
# define K_UP_ARROW 126
# define K_DOWN_ARROW 125
# define K_NUM_PLUS 69
# define K_NUM_MINUS 78
# define K_NUM_0 82

# define K_NUM_7 89
# define K_NUM_4 86
# define K_NUM_8 91
# define K_NUM_6 88
# define K_NUM_2 84
# define K_NUM_9 92
# define K_NUM_3 85
# define K_NUM_1 83

# define K_ESC 53
# define K_SPACEBAR 49
# define K_H 4
# define K_G 5
# define K_L 37
# define K_I 34

# define C_RED 0xFF0000
# define C_GREEN 0x00FF00
# define C_BLUE 0x0000FF
# define C_WHITE 0xFFFFFF
# define C_YELLOW 0xD8CE0F

typedef struct	s_vector2
{
	double		x;
	double		y;
}				t_vector2;

typedef struct	s_win
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*pix_ptr;
	int			max_it;
	double		dx;
	double		dy;
	t_vector2	min_val;
	t_vector2	max_val;
	int			i;
	int			j;
	int			j_max;
	int			col_offset;
}				t_win;

typedef struct	s_frac
{
	char		*pix_ptr;
	int			max_it;
	double		dx;
	double		dy;
	t_vector2	min_val;
	t_vector2	max_val;
	int			i;
	int			j;
	int			j_max;
}				t_frac;

void			ft_pp_img(char *pixels, int x, int y, int color);
int				ft_check_input(char *fract_name);
void			ft_print_usage();
void			ft_pthread_mandelbrot(t_win *win);
void			ft_rewrite(t_win *win);
void			ft_mouse_zoom(t_win *win, double interpolation, int x, int y);
double			interpolate(double start, double end, double interpolation);
void			ft_move_img(t_win *win, int key);

#endif
