/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:07:22 by wtang             #+#    #+#             */
/*   Updated: 2025/09/15 16:33:14 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	cal_mandelbrot(t_fractol *fractol, double cr, double ci)
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
			break ;
		re_tmp = zr * zr - zi * zi + cr;
		zi = 2 * zr * zi + ci;
		zr = re_tmp;
		iter++;
	}
	return (iter);
}

int	cal_julia(t_fractol *fractol, double zr, double zi)
{
	int		iter;
	double	re_tmp;

	iter = 0;
	while (iter < fractol->max_iterations)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		re_tmp = zr * zr - zi * zi + fractol->julia_c_re;
		zi = 2 * zr * zi + fractol->julia_c_im;
		zr = re_tmp;
		iter++;
	}
	return (iter);
}
