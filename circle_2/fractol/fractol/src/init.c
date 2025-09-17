/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:51:24 by wtang             #+#    #+#             */
/*   Updated: 2025/09/15 20:27:27 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_fractol(t_fractol *fractol, int fractal_type)
{
	fractol->type = fractal_type;
	fractol->zoom = 1.0;
	fractol->offset_x = 0.0;
	fractol->offset_y = 0.0;
	fractol->max_iterations = 100;
	fractol->color_scheme = 0;
	fractol->julia_c_re = -0.7;
	fractol->julia_c_im = 0.27;
	if (fractal_type == MANDELBROT)
	{
		fractol->min_re = -2.0;
		fractol->max_re = 1.0;
		fractol->min_im = -1.5;
		fractol->max_im = 1.5;
	}
	else if (fractal_type == JULIA)
	{
		fractol->min_re = -2.0;
		fractol->max_re = 2.0;
		fractol->min_im = -2.0;
		fractol->max_im = 2.0;
	}
}

void	error_exit(char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(1);
}

void	init_mlx_image(t_fractol *f)
{
	f->img = mlx_new_image(f->mlx, WIN_SIZE, WIN_SIZE);
	if (!f->img)
	{
		mlx_destroy_window(f->mlx, f->win);
		mlx_destroy_display(f->mlx);
		free(f->mlx);
		error_exit("ERROR: failed to create image");
	}
}

void	init_environment(t_fractol *f)
{
	int	pixel_bits;
	int	line_length;
	int	endian;

	f->mlx = mlx_init();
	if (!f->mlx)
		error_exit("ERROR: mlx_init failed");
	f->win = mlx_new_window(f->mlx, WIN_SIZE, WIN_SIZE, "FRACTAL");
	if (!f->win)
	{
		mlx_destroy_display(f->mlx);
		free(f->mlx);
		error_exit("ERROR: failed to create window");
	}
	init_mlx_image(f);
	f->img_addr = mlx_get_data_addr(f->img, &pixel_bits, &line_length, &endian);
	f->bits_per_pixel = pixel_bits;
	f->line_length = line_length;
	f->endian = endian;
}

void	init_fractol(t_fractol *fractol, int ac, char **av)
{
	if (!fractol || !av || ac < 2)
		return ;
	if (ft_strncmp(av[1], "mandelbrot", 11) == 0)
	{
		if (ac != 2)
			display_help();
		reset_fractol(fractol, MANDELBROT);
	}
	else if (ft_strncmp(av[1], "julia", 6) == 0)
	{
		reset_fractol(fractol, JULIA);
		if (ac == 4)
		{
			if (!is_valid_number(av[2]) || !is_valid_number(av[3]))
				display_help();
			fractol->julia_c_re = ft_atof(av[2]);
			fractol->julia_c_im = ft_atof(av[3]);
		}
		else if (ac != 2)
			display_help();
	}
	else
		display_help();
	init_environment(fractol);
}
