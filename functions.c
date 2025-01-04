/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalrfai <yalrfai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:27:39 by yaman-alrif       #+#    #+#             */
/*   Updated: 2025/01/02 22:29:34 by yalrfai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	free_data(t_mlx_data *data)
{
	if (data->imgd.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->imgd.img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	if (data->mlx_ptr)
		free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
		*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
	}
}

void	color_screen(t_mlx_data *data, int color)
{
	int	x;
	int	y;

	y = -1;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (x >= WIDTH * 0.1 && x < WIDTH * 0.9 && y >= HEIGHT * 0.1 && y < HEIGHT * 0.9)
				my_pixel_put(&data->imgd, x, y, color);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->imgd.img_ptr, 0, 0);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	double	shift;
	if (keysym == XK_Escape)
	{
		free_data(data);
		exit(1);
	}
	shift = 0.1 * data->pic.zoom;
	if (keysym == XK_Left)
		data->pic.offsetX -= shift;
	else if (keysym == XK_Right)
		data->pic.offsetX += shift;
	else if (keysym == XK_Up)
		data->pic.offsetY -= shift;
	else if (keysym == XK_Down)
		data->pic.offsetY += shift;
	if (data->frac_name == 1)
		mandelbrot(data);
	else if (data->frac_name == 2)
		julia(data, data->x, data->y);
	else if (data->frac_name == 3)
		mandelbar(data);

	return (0);
}

int	handle_close(t_mlx_data *data)
{
	free_data(data);
	return (0);
}

int	strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2 || *s1 == '\0' || *s2 == '\0')
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}

void	make_data(t_mlx_data *data)
{
	data->pic = (t_pic){.zoom = 1.0, .offsetX = 0.0, .offsetY = 0.0};
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		perror("mlx_init() failed");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "test");
	if (!data->win_ptr)
		free_data(data);
	data->imgd.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->imgd.img_ptr)
		free_data(data);
	data->imgd.img_pixels_ptr = mlx_get_data_addr(data->imgd.img_ptr, &data->imgd.bits_per_pixel, &data->imgd.line_len, &data->imgd.endian);
	if (!data->imgd.img_pixels_ptr)
		free_data(data);
	data->color = 0x0000FF;
}

double	map(double value, double stop1, double start2, double stop2)
{
	return (start2 + (stop2 - start2) * ((value) / (stop1)));
}

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

void	find_color(t_mlx_data *data)
{
	if (data->color == 0xFF00FF)
		data->color = 0x0000FF;
	else
		data->color = 0xFF00FF;
}

int	mouse_input(int button, int x, int y, t_mlx_data *data)
{
	double	mouse_re;
	double	mouse_im;
	double	new_mouse_re;
	double	new_mouse_im;

	mouse_re = map(x, WIDTH, -2.5 * data->pic.zoom + data->pic.offsetX, 1.5 * data->pic.zoom + data->pic.offsetX);
	mouse_im = map(y, HEIGHT, -2 * data->pic.zoom + data->pic.offsetY, 2 * data->pic.zoom + data->pic.offsetY);
	if (button == 1)
		find_color(data);
	else if (button == 4)
		data->pic.zoom *= 1.1;
	else if (button == 5)
		data->pic.zoom /= 1.1;
	new_mouse_re = map(x, WIDTH, -2.5 * data->pic.zoom + data->pic.offsetX, 1.5 * data->pic.zoom + data->pic.offsetX);
	new_mouse_im = map(y, HEIGHT, -2 * data->pic.zoom + data->pic.offsetY, 2 * data->pic.zoom + data->pic.offsetY);
	data->pic.offsetX += mouse_re - new_mouse_re;
	data->pic.offsetY += mouse_im - new_mouse_im;
	if (data->frac_name == 1)
		mandelbrot(data);
	else if (data->frac_name == 2)
		julia(data, data->x, data->y);
	else if (data->frac_name == 3)
		mandelbar(data);
	return (0);
}

void	see_fractal(t_mlx_data *data, double x, double y, char *name)
{
	data->x = x;
	data->y = y;
	if (!strncmp(name, "mandelbrot", 11))
	{
		data->frac_name = 1;
		mandelbrot(data);
	}
	else if (!strncmp(name, "julia", 5))
	{
		data->frac_name = 2;
		julia(data, x, y);
	}
	else if (!strncmp(name, "mandelbar", 9))
	{
		data->frac_name = 3;
		mandelbar(data);
	}
}
