/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 23:20:57 by wtang             #+#    #+#             */
/*   Updated: 2025/08/26 23:31:28 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fractol	fractol;

	if (ac != 2)
		display_help();
	init_fractol(&fractol, av[1]);
	draw_fractal(&fractol);
	mlx_key_hook(fractol.win, key_hook, &fractol);
	mlx_mouse_hook(fractol.win, mouse_hook, &fractol);
	mlx_hook(fractol.win, 17, 0, end_fractol, &fractol);
	mlx_loop(fractol.mlx);
	return (0);
}
