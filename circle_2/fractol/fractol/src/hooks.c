/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:50:26 by wtang             #+#    #+#             */
/*   Updated: 2025/09/15 12:23:32 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_fractol *fractol)
{
	if (keycode == 53) // ESC exit
		end_fractol(fractol);
	else if (keycode >= 123 && keycode <= 126) // move views
		move_view(fractol, keycode);
	else if (keycode >= 18 && keycode <= 19) // change fractals
		change_fractal_type(fractol, keycode - 17);
	return (0);
}

int	end_fractol(t_fractol *fractol)
{
	if (fractol->img)
		mlx_destroy_image(fractol->mlx, fractol->img);
	if (fractol->win)
		mlx_destroy_window(fractol->mlx, fractol->win);
	if (fractol->mlx)
	{
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

void	move_view(t_fractol *fractol, int keycode)
{
	double	move_amount;

	move_amount = 0.1 * (fractol->max_re - fractol->min_re);
	
	if (keycode == 126) // up
	{
		fractol->min_im += move_amount;
		fractol->max_im += move_amount;
	}
	else if (keycode == 125) // down
	{
		fractol->min_im -= move_amount;
		fractol->max_im -= move_amount;
	}
	else if (keycode == 123) // left
	{
		fractol->min_re -= move_amount;
		fractol->max_re -= move_amount;
	}
	else if (keycode == 124) // right
	{
		fractol->min_re += move_amount;
		fractol->max_re += move_amount;
	}
}

void	change_fractal_type(t_fractol *fractol, int type)
{
	if (type == 1)
		fractol->type = MANDELBROT;
	else if (type == 2)
		fractol->type = JULIA;
	reset_fractol(fractol, fractol->type);
	draw_fractal(fractol);
}
