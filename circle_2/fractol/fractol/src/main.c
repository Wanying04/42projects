/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 23:20:57 by wtang             #+#    #+#             */
/*   Updated: 2025/08/26 22:53:25 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fractol	fractol;

	if (ac != 2)
		display_help();
	process_arg(av);
	draw_fractal(fractol);
	mlx_key_hook(fractol->win, key_hook(), fractol);
	mlx_mouse_hook(fractol->win, mouse_hook(), fractol);
	mlx_hook(fractol->win, end_fractol(), fractol);
	mlx_loop();
	return (0);
}
