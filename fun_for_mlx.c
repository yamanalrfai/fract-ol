/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_for_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalrfai <yalrfai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:17:21 by yalrfai           #+#    #+#             */
/*   Updated: 2025/01/04 16:05:51 by yalrfai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		data->pic.offsetx -= shift;
	else if (keysym == XK_Right)
		data->pic.offsetx += shift;
	else if (keysym == XK_Up)
		data->pic.offsety -= shift;
	else if (keysym == XK_Down)
		data->pic.offsety += shift;
	do_fract(data);
	return (0);
}

int	handle_close(t_mlx_data *data)
{
	free_data(data);
	return (0);
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
			if (x >= WIDTH * 0.1 && x < WIDTH * 0.9
				&& y >= HEIGHT * 0.1 && y < HEIGHT * 0.9)
				my_pixel_put(&data->imgd, x, y, color);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->imgd.img_ptr, 0, 0);
}

int	mouse_input(int button, int x, int y, t_mlx_data *data)
{
	double	mouse_re;
	double	mouse_im;
	double	new_mouse_re;
	double	new_mouse_im;

	mouse_re = map(x, WIDTH, -2.5 * data->pic.zoom + data->pic.offsetx,
			1.5 * data->pic.zoom + data->pic.offsetx);
	mouse_im = map(y, HEIGHT, -2 * data->pic.zoom + data->pic.offsety,
			2 * data->pic.zoom + data->pic.offsety);
	if (button == 1)
		find_color(data);
	else if (button == 4)
		data->pic.zoom *= 1.1;
	else if (button == 5)
		data->pic.zoom /= 1.1;
	new_mouse_re = map(x, WIDTH, -2.5 * data->pic.zoom + data->pic.offsetx,
			1.5 * data->pic.zoom + data->pic.offsetx);
	new_mouse_im = map(y, HEIGHT, -2 * data->pic.zoom + data->pic.offsety,
			2 * data->pic.zoom + data->pic.offsety);
	data->pic.offsetx += mouse_re - new_mouse_re;
	data->pic.offsety += mouse_im - new_mouse_im;
	do_fract(data);
	return (0);
}
