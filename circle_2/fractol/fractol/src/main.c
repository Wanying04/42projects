/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 23:20:57 by wtang             #+#    #+#             */
/*   Updated: 2025/08/25 00:47:44 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fractol	fractol;

	if (ac != 2)
		display_help();
	process_arg();
	init_environment();
	draw_fractal();
	mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param);
	mlx_mouse_hook(void *win_ptr, int (*funct_ptr)(), void *param);
	mlx_hook(void *win_ptr, int (*funct_ptr)(), void *param);//窗口关闭
	mlx_loop();
	return (0);
}

void	display_help()
{
	
}

void	process_arg()
{
	
}

typedef struct	s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	
	double	min_re;
	double	max_re;
	double	min_im;
	double	max_im;
	int		max_iterations;
	
	int		color_scheme;
	
	double	julia_c_re;
	double	julia_c_im;
	
	int		fractal_type;
	int		is_julia_locked;
}	t_fractol

void	init_environment()
{
	
	
	mlx = mlx_init();
	if (!mlx_init)
		//如果失败，返回错误信息并强制退出
	win = mlx_new_window(void *mlx_ptr, 1920, 1080, FRACTAL);
		//创建失败的话，清理，返回错误信息并强制退出
		//图像交替轮上的方法，一个展示一个候场
	img = mlx_new_image(void *mlx_ptr, int width, int height);
		//创建失败的话，清理，返回错误信息并强制退出
	mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
	
}



int	key_hook(int keycode, void *param)
{
	
}

int mouse_hook(int button, int x, int y, void *param)
{
	
}

int	end_fractol(t_fractol *fractol)
{
	
}
