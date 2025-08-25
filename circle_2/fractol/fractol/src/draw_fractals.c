/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:55:32 by wtang             #+#    #+#             */
/*   Updated: 2025/08/25 00:58:02 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

# define WIN_SIZE 800

# define MANDELBROT

void	draw_fractal(t_fractol *fractol)
{
	static	t_complex c;
	t_fractol	*frac;
	int	iter;
	int	x;
	int	y;

	mlx_clear_window(fractol->mlx, fractol->win);
	while (++y < WIN_SIZE)
	{
		while (++x < WIN_SIZE)
		{
			iter = cal_fractal();
			set_pixel_color();
		}
	}
	复平面坐标 = (屏幕坐标 / 缩放比例) + 偏移量
	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);
}

int	cal_fractal(t_fractol *frac, t_complex c, int x, int y)
{
	if (fractal->type == MANDELBROT)
		iter = cal_mandelbrot(frac, c);
	else if (fractal->type == JULIA)
		iter = cal_julia(frac, c, x, y);
}

int	cal_mandelbrot(t_fractol *frac, t_complex c)
{
	t_complex z = {0, 0};
	int	i = -1;

	while ()
	{
		
	}
	return (i);
}

int	cal_julia(t_fractol *frac, t_complex c, int x, int y)
{
	t_complex z;
}

void	set_pixel_color(t_fractol *fractol, int x, int y, int color)
{
	
}
