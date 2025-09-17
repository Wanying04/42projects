/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:55:32 by wtang             #+#    #+#             */
/*   Updated: 2025/09/15 16:32:49 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_fractal(t_fractol *f)
{
	double	cr;
	double	ci;
	int		iter;
	int		x;
	int		y;

	y = -1;
	mlx_clear_window(f->mlx, f->win);
	while (++y < WIN_SIZE)
	{
		x = -1;
		while (++x < WIN_SIZE)
		{
			cr = f->min_re + (double)x * (f->max_re - f->min_re) / WIN_SIZE;
			ci = f->max_im - (double)y * (f->max_im - f->min_im) / WIN_SIZE;
			iter = cal_fractal(f, cr, ci);
			set_pixel_color(f, x, y, iter);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

int	cal_fractal(t_fractol *fractol, double cr, double ci)
{
	int	iter;

	iter = 0;
	if (fractol->type == MANDELBROT)
		iter = cal_mandelbrot(fractol, cr, ci);
	else if (fractol->type == JULIA)
		iter = cal_julia(fractol, cr, ci);
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
	double	ratio;
	int		r;
	int		g;
	int		b;

	ratio = (double)iter / max_iter;
	r = 255 - (int)(75 * ratio);
	g = 192 - (int)(112 * ratio);
	b = 203 - (int)(123 * ratio);
	return (r << 16 | g << 8 | b);
}
