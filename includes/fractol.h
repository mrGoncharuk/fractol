/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:01:02 by mhonchar          #+#    #+#             */
/*   Updated: 2019/03/24 20:32:20 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>
# define WIDTH 800
# define HEIGHT 800
# define THREADS_AMOUNT 4

# define K_MOUSE_LEFT 65437
# define K_MOUSE_RIGHT 2
# define K_MOUSE_WHEEL_DOWN 4
# define K_MOUSE_WHEEL_UP 5
# define K_LEFT_ARROW 65361
# define K_UP_ARROW 65362
# define K_RIGTH_ARROW 65363
# define K_DOWN_ARROW 65364
# define K_NUM_PLUS 65451
# define K_NUM_MINUS 65453
# define K_NUM_0 65438

# define K_NUM_7 89
# define K_NUM_4 86
# define K_NUM_8 91
# define K_NUM_6 88
# define K_NUM_2 84
# define K_NUM_9 92
# define K_NUM_3 85
# define K_NUM_1 83

# define K_1 49
# define K_2 50
# define K_3 20
# define K_4 21
# define K_5 23
# define K_6 22

# define FR_MANDELBROT K_1
# define FR_JULIA K_2

# define K_ESC 65307
# define K_SPACEBAR 49
# define K_H 4
# define K_R 114
# define K_G 103
# define K_B 98
# define K_L 83
# define K_I 84

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
	void		(*ft_putfract)(struct s_win*);
	double		c_im;
	double		c_re;
	int			max_it;
	double		dx;
	double		dy;
	t_vector2	min_val;
	t_vector2	max_val;
	int			i;
	int			j;
	int			j_max;
	int			col_offset;
	int			red;
	int			green;
	int			blue;
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
void			ft_create_color(t_win *win, int it);
double			interpolate(double start, double end, double interpolation);
void			ft_set_default(t_win *win);
void			ft_move_color(t_win *win, int key);

int				ft_check_input(char *fract_name);
void			ft_print_usage();
void			ft_mouse_zoom(t_win *win, double interpolation, int x, int y);
void			ft_move_img(t_win *win, int key);
void			ft_set_fractal(t_win *win, int frnumber);

void			ft_pthread_mandelbrot(t_win *win);
void			ft_init_mandelbrot(t_win *win);
void			ft_pthread_julia(t_win *win);
void			ft_init_julia(t_win *win);
void			ft_rewrite(t_win *win);

#endif
