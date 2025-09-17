/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:50:26 by wtang             #+#    #+#             */
/*   Updated: 2025/09/15 16:34:36 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_fractol *fractol)
{
	if (keycode == 65307)
		end_fractol(fractol);
	else if (keycode >= 65361 && keycode <= 65364)
		move_view(fractol, keycode);
	draw_fractal(fractol);
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
	if (keycode == 65362)
	{
		fractol->min_im += move_amount;
		fractol->max_im += move_amount;
	}
	else if (keycode == 65364)
	{
		fractol->min_im -= move_amount;
		fractol->max_im -= move_amount;
	}
	else if (keycode == 65361)
	{
		fractol->min_re -= move_amount;
		fractol->max_re -= move_amount;
	}
	else if (keycode == 65363)
	{
		fractol->min_re += move_amount;
		fractol->max_re += move_amount;
	}
}
