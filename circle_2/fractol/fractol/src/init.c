/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:51:24 by wtang             #+#    #+#             */
/*   Updated: 2025/08/27 00:20:30 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_fractol(t_fractol *fractol, int fractal_type)
{
	fractol->type = fractal_type;
	fractol->zoom = 1.0;
	fractol->offset_x = 0.0;
	fractol->offset_x = 0.0;
	fractol->max_iterations = 100;
	fractol->color_scheme = 0;
	fractol->julia_c_re = -0.7;
	fractol->julia_c_im = 0.27;
}

void	init_fractol(t_fractol *fractol, char *av)
{
	if (!fractol || !av)
		return ;
	reset_fractol(fractol, MANDELBROT);
	if (strncmp(av, "mandelbrot", 10) == 0)
		fractol->type = MANDELBROT;
	else if (strncmp(av, "julia", 5) == 0)
		fractol->type = JULIA;
	else
	{
		display_help();
		exit (1);
	}
	init_environment(fractol);
}

void	init_environment(t_fractol *fractol)
{
	int	pixel_bits;
	int	line_length;
	int	endian;
	
	fractol->mlx = mlx_init();
	if (!fractol->mlx)
		error_exit("ERROR: mlx_init failed");
	fractol->win = mlx_new_window(fractol->mlx, WIN_SIZE, WIN_SIZE, "FRACTAL");
	if (!fractol->win)
	{
		free(fractol->mlx);
		error_exit("ERROR: failed to create window");
	}
	fractol->img = mlx_new_image(fractol->mlx, WIN_SIZE, WIN_SIZE);
	if (!fractol->img)
	{
		mlx_destroy_window(fractol->mlx, fractol->win);
		free(fractol->mlx);
		error_exit("ERROR: failed to create image");
	}
	fractol->img_addr = mlx_get_data_addr(fractol->img, &pixel_bits, &line_length, &endian);
	fractol->bits_per_pixel = pixel_bits;
	fractol->line_length = line_length;
	fractol->endian = endian;
}

void	error_exit(char *message)
{
	write(2, message, strlen(message));
	write(2, "\n", 1);
	exit(1);
}
