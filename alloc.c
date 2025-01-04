/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalrfai <yalrfai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:20:30 by yalrfai           #+#    #+#             */
/*   Updated: 2025/01/04 15:21:29 by yalrfai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
