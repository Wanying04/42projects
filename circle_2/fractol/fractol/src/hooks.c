/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:50:26 by wtang             #+#    #+#             */
/*   Updated: 2025/08/28 17:56:22 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_fractol *fractol)
{
	if (keycode == 53) // ESC键
		end_fractol(fractol);
	else if (keycode >= 123 && keycode <= 126) // 方向键
		move_view(fractol, keycode);
	else if (keycode >= 18 && keycode <= 23) // 数字键1-6切换分形
		change_fractal_type(fractol, keycode - 17);
	return (0);
}

int mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	if (button == 4) // 鼠标滚轮向上 - 放大
		zoom_in(fractol, x, y);
	else if (button == 5) // 鼠标滚轮向下 - 缩小
		zoom_out(fractol, x, y);
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

void	move_view(t_fractol *fractol, int keycode)
{
	double	move_amount;

	move_amount = 0.1 * (fractol->max_re - fractol->min_re);
	
	if (keycode == 126) // 上箭头
	{
		fractol->min_im += move_amount;
		fractol->max_im += move_amount;
	}
	else if (keycode == 125) // 下箭头
	{
		fractol->min_im -= move_amount;
		fractol->max_im -= move_amount;
	}
	else if (keycode == 123) // 左箭头
	{
		fractol->min_re -= move_amount;
		fractol->max_re -= move_amount;
	}
	else if (keycode == 124) // 右箭头
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
	// 可以根据需要添加更多分形类型
	reset_fractol(fractol, fractol->type);
	draw_fractal(fractol);
}
