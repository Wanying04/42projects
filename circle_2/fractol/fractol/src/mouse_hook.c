/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:22:51 by wtang             #+#    #+#             */
/*   Updated: 2025/09/15 16:38:31 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	if (button == 4)
		zoom_in(fractol, x, y);
	else if (button == 5)
		zoom_out(fractol, x, y);
	draw_fractal(fractol);
	return (0);
}

void	zoom_in(t_fractol *f, int x, int y)
{
	double	mouse_r;
	double	mouse_i;
	double	zoom_factor;

	zoom_factor = 0.9;
	mouse_r = f->min_re + (double)x * (f->max_re - f->min_re) / WIN_SIZE;
	mouse_i = f->max_im - (double)y * (f->max_im - f->min_im) / WIN_SIZE;
	f->min_re = mouse_r + (f->min_re - mouse_r) * zoom_factor;
	f->max_re = mouse_r + (f->max_re - mouse_r) * zoom_factor;
	f->min_im = mouse_i + (f->min_im - mouse_i) * zoom_factor;
	f->max_im = mouse_i + (f->max_im - mouse_i) * zoom_factor;
	f->zoom *= zoom_factor;
}

void	zoom_out(t_fractol *f, int x, int y)
{
	double	mouse_r;
	double	mouse_i;
	double	zoom_factor;

	zoom_factor = 1.1;
	mouse_r = f->min_re + (double)x * (f->max_re - f->min_re) / WIN_SIZE;
	mouse_i = f->max_im - (double)y * (f->max_im - f->min_im) / WIN_SIZE;
	f->min_re = mouse_r + (f->min_re - mouse_r) * zoom_factor;
	f->max_re = mouse_r + (f->max_re - mouse_r) * zoom_factor;
	f->min_im = mouse_i + (f->min_im - mouse_i) * zoom_factor;
	f->max_im = mouse_i + (f->max_im - mouse_i) * zoom_factor;
	f->zoom *= zoom_factor;
}
