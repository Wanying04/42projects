/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 23:20:57 by wtang             #+#    #+#             */
/*   Updated: 2025/09/16 12:05:53 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	display_help(void)
{
	write(1, "Usage:\n", 7);
	write(1, "  ./fractol mandelbrot\n", 23);
	write(1, "  ./fractol julia [real_part] [imaginary_part]\n", 46);
	write(1, "\nExamples:\n", 11);
	write(1, "  ./fractol mandelbrot\n", 23);
	write(1, "  ./fractol julia\n", 18);
	write(1, "  ./fractol julia -0.7 0.27015\n", 31);
	write(1, "  ./fractol julia -0.75 0.11\n", 29);
	write(1, "  ./fractol julia 0.285 0.01\n", 29);
	exit(1);
}

int	main(int ac, char **av)
{
	t_fractol	fractol;

	if (ac < 2 || ac > 4)
		display_help();
	init_fractol(&fractol, ac, av);
	draw_fractal(&fractol);
	mlx_key_hook(fractol.win, key_hook, &fractol);
	mlx_mouse_hook(fractol.win, mouse_hook, &fractol);
	mlx_hook(fractol.win, 17, 0, end_fractol, &fractol);
	mlx_loop(fractol.mlx);
	return (0);
}
