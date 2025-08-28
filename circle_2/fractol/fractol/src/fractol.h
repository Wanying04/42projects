/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 11:22:54 by wtang             #+#    #+#             */
/*   Updated: 2025/08/28 17:56:05 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <unistd.h>
#include "libft.h"
#include "mlx.h"

# define WIN_SIZE 800
# define MANDELBROT 1
# define JULIA 2

typedef struct	s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	
	double	min_re;
	double	max_re;
	double	min_im;
	double	max_im;
	int		max_iterations;

	double	zoom;
	double	offset_x;
	double	offset_y;
	
	int		color_scheme;
	
	double	julia_c_re;
	double	julia_c_im;
	
	int		type;
	int		is_julia_locked;
}	t_fractol;

//utils.c
void	display_help(void);
//init.c
void	init_fractol(t_fractol *fractol, char *av);
void	reset_fractol(t_fractol *fractol, int fractal_type);
void	init_environment(t_fractol *fractol);
void	error_exit(char *message);
//draw
void	draw_fractal(t_fractol *fractol);
int	cal_fractal(t_fractol *fractol, double cr, double ci);
int	cal_mandelbrot(t_fractol *fractol, double cr, double ci);
int	cal_julia(t_fractol *fractol, double zr, double zi);
void	set_pixel_color(t_fractol *fractol, int x, int y, int iter);
int	create_pink_purple_color(int iter, int max_iter);
//hooks.c
int	key_hook(int keycode, t_fractol *fractol);
int mouse_hook(int button, int x, int y, t_fractol *fractol);
int	end_fractol(t_fractol *fractol);
void	move_view(t_fractol *fractol, int keycode);
void	change_fractal_type(t_fractol *fractol, int type);
void	zoom_in(t_fractol *fractol, int x, int y);
void	zoom_out(t_fractol *fractol, int x, int y);

#endif