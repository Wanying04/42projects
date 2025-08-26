/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:51:24 by wtang             #+#    #+#             */
/*   Updated: 2025/08/26 22:52:02 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	process_arg(char **av)
{
	char	*target_m;
	char	*target_j;

	target_m = "mandelbrot";
	target_j = "julia";
	if (strncmp(av, target_m) == 0 || strncmp(av, target_j) == 0)
	{
		init_environment(&fractol);
	}
	else
		display_help();
}

void	init_environment()
{
	mlx = mlx_init();
	if (!mlx_init)
		return (1);
	win = mlx_new_window(fractol->mlx, 1920, 1080, FRACTAL);
	if (!win)
	{
		mlx_destroy_window(fractol->mlx, win);
		return (1);
	}
	img = mlx_new_image(fractol->mlx_ptr, int width, int height);
	if (!img)
	{
		mlx_destroy_window(fractol->mlx, fractol->win);
		mlx_destroy_image(fractol->mlx, fractol->win);
		return (1);
	}
	mlx_get_data_addr(fractol->img, fractol->bits_per_pixel, fractol->line_length, fractol->endian);
}
