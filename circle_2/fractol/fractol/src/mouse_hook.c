/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:22:51 by wtang             #+#    #+#             */
/*   Updated: 2025/09/15 12:23:38 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	if (button == 4) // zoom in
		zoom_in(fractol, x, y);
	else if (button == 5) // zoom out
		zoom_out(fractol, x, y);
	draw_fractal(fractol);
	return (0);
}

void	zoom_in(t_fractol *fractol, int x, int y)
{
	double	mouse_r;
	double	mouse_i;
	double	zoom_factor;

	zoom_factor = 0.9;
	mouse_r = fractol->min_re + (double)x * (fractol->max_re - fractol->min_re) / WIN_SIZE;
	mouse_i = fractol->max_im - (double)y * (fractol->max_im - fractol->min_im) / WIN_SIZE;
	fractol->min_re = mouse_r + (fractol->min_re - mouse_r) * zoom_factor;
	fractol->max_re = mouse_r + (fractol->max_re - mouse_r) * zoom_factor;
	fractol->min_im = mouse_i + (fractol->min_im - mouse_i) * zoom_factor;
	fractol->max_im = mouse_i + (fractol->max_im - mouse_i) * zoom_factor;
	fractol->zoom *= zoom_factor;
}

void	zoom_out(t_fractol *fractol, int x, int y)
{
	double	mouse_r;
	double	mouse_i;
	double	zoom_factor;

	zoom_factor = 1.1;
	mouse_r = fractol->min_re + (double)x * (fractol->max_re - fractol->min_re) / WIN_SIZE;
	mouse_i = fractol->max_im - (double)y * (fractol->max_im - fractol->min_im) / WIN_SIZE;
	fractol->min_re = mouse_r + (fractol->min_re - mouse_r) * zoom_factor;
	fractol->max_re = mouse_r + (fractol->max_re - mouse_r) * zoom_factor;
	fractol->min_im = mouse_i + (fractol->min_im - mouse_i) * zoom_factor;
	fractol->max_im = mouse_i + (fractol->max_im - mouse_i) * zoom_factor;
	fractol->zoom *= zoom_factor;
}
