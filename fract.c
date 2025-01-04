/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalrfai <yalrfai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:27:39 by yaman-alrif       #+#    #+#             */
/*   Updated: 2025/01/04 15:24:38 by yalrfai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	see_iteration(double c_re, double c_im, double z_re, double z_im)
{
	int		iteration;
	double	xtemp;

	iteration = 0;
	while (z_re * z_re + z_im * z_im < 4 && iteration < max_iteration)
	{
		xtemp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = xtemp;
		++iteration;
	}
	return (iteration);
}

void	mandelbrot(t_mlx_data *data)
{
	double	x;
	double	y;
	int		iteration;
	double	c_re;
	double	c_im;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			c_re = map(x, WIDTH, -2.5 * data->pic.zoom + data->pic.offsetX, 1.5 * data->pic.zoom + data->pic.offsetX);
			c_im = map(y, HEIGHT, -2 * data->pic.zoom + data->pic.offsetY, 2 * data->pic.zoom + data->pic.offsetY);
			iteration = see_iteration(c_re, c_im, 0, 0);
			if (iteration == max_iteration)
				my_pixel_put(&data->imgd, x, y, 0xf0f0f0);
			else
				my_pixel_put(&data->imgd, x, y, data->color + iteration * 1000);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->imgd.img_ptr, 0, 0);
}

void	julia(t_mlx_data *data, double c_re, double c_im)
{
	double	x;
	double	y;
	int		iteration;
	double	z_re;
	double	z_im;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			z_re = map(x, WIDTH, -2.5 * data->pic.zoom + data->pic.offsetX, 1.5 * data->pic.zoom + data->pic.offsetX);
			z_im = map(y, HEIGHT, -2 * data->pic.zoom + data->pic.offsetY, 2 * data->pic.zoom + data->pic.offsetY);
			iteration = see_iteration(c_re, c_im, z_re, z_im);
			if (iteration == max_iteration)
				my_pixel_put(&data->imgd, x, y, 0xf0f0f0);
			else
				my_pixel_put(&data->imgd, x, y, data->color + iteration * 1000);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->imgd.img_ptr, 0, 0);
}

int	see_iteration_bar(double c_re, double c_im, double z_re, double z_im)
{
	int		iteration;
	double	xtemp;

	iteration = 0;
	while (z_re * z_re + z_im * z_im < 4 && iteration < max_iteration)
	{
		xtemp = z_re * z_re - z_im * z_im + c_re;
		z_im = -2 * z_re * z_im + c_im;
		z_re = xtemp;
		++iteration;
	}
	return (iteration);
}

void	mandelbar(t_mlx_data *data)
{
	double	x;
	double	y;
	int		iteration;
	double	c_re;
	double	c_im;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			c_re = map(x, WIDTH, -2.5 * data->pic.zoom + data->pic.offsetX, 1.5 * data->pic.zoom + data->pic.offsetX);
			c_im = map(y, HEIGHT, -2 * data->pic.zoom + data->pic.offsetY, 2 * data->pic.zoom + data->pic.offsetY);
			iteration = see_iteration_bar(c_re, c_im, 0, 0);
			if (iteration == max_iteration)
				my_pixel_put(&data->imgd, x, y, 0xf0f0f0);
			else
				my_pixel_put(&data->imgd, x, y, data->color + iteration * 1000);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->imgd.img_ptr, 0, 0);
}
