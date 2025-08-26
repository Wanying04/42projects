/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:55:32 by wtang             #+#    #+#             */
/*   Updated: 2025/08/27 00:34:10 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_fractal(t_fractol *fractol)
{
	double	cr;
	double	ci;
	int	iter;
	int	x;
	int	y;

	y = -1;
	mlx_clear_window(fractol->mlx, fractol->win);
	while (++y < WIN_SIZE)
	{
		x = -1;
		while (++x < WIN_SIZE)
		{
			cr = fractol->min_re + (double)x * (fractol->max_re - fractol->min_r) / WIN_SIZE;
			ci = fractol->max_im - (double)y * (fractol->max_im - fractol->min_i) / WIN_SIZE;
			iter = cal_fractal(fractol, cr, ci, x, y);
			set_pixel_color(fractol, x, y, iter);
		}
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}

int	cal_fractal(t_fractol *fractol, double cr, double ci, int x, int y)
{
	int	iter;
	
	if (fractol->type == MANDELBROT)
		iter = cal_mandelbrot(fractol, cr, ci);
	else if (fractol->type == JULIA)
		iter = cal_julia(fractol, cr, ci);
	return (iter);
}

int	cal_maldelbrot(t_fractol *fractol, double cr, double ci)
{
	double	zr;
	double	zi;
	int		iter;
	double	re_tmp;

	zr = 0.0;
	zi = 0.0;
	iter = 0;
	while (iter < fractol->max_iterations)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break;
		re_tmp = zr * zr - zi * zi + cr;
		zi = 2 * zr * zi + ci;
		zr = re_tmp;
		iter++;
	}
	return (iter);
}

int	cal_julia(t_fractol *fractol, double zr, double zi)
{
	int	iter;
	double	re_tmp;

	iter = 0;
	while (iter < fractol->max_iterations)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break;
		re_tmp = zr * zr - zi * zi + fractol->julia_c_re;
		zi = 2 * zr * zi + fractol->julia_c_im;
		zr = re_tmp;
		iter++;
	}
	return (iter);
}

void	set_pixel_color(t_fractol *fractol, int x, int y, int iter)
{
	int	color;
	int	offset;
	
	if (iter == fractol->max_iterations)
		color = 0x000000;
	else
		color = create_pink_purple_color(iter, fractol->max_iterations);
	offset = (y * fractol->line_length) + (x * (fractol->bits_per_pixel / 8));
	*(unsigned int *)(fractol->img_addr + offset) = color;
}

int	create_pink_purple_color(int iter, int max_iter)
{
	double	ratio = (double)iter / max_iter;
	int		r, g, b;
	
	// 粉紫色渐变：粉色(0xFFC0CB) → 紫色(0x800080)
	r = 255 - (int)(75 * ratio);
    g = 192 - (int)(112 * ratio);
    b = 203 - (int)(123 * ratio);
	return (r << 16 | g << 8 | b);
}
