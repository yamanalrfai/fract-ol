/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaman-alrifai <yaman-alrifai@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:58:25 by yaman-alrif       #+#    #+#             */
/*   Updated: 2025/01/08 13:21:50 by yaman-alrif      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <X11/keysym.h>
# include <stdio.h>
# define WIDTH 700
# define HEIGHT 700
# define MAX_ITR 200

typedef struct s_pic
{
	double	zoom;
	double	offsetx;
	double	offsety;
}	t_pic;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		frac_name;
	t_img	imgd;
	t_pic	pic;
	int		color;
	double	x;
	double	y;
}	t_mlx_data;

void	free_data(t_mlx_data *data, int want);
void	my_pixel_put(t_img *img, int x, int y, int color);
void	color_screen(t_mlx_data *data, int color);
int		handle_input(int keysym, t_mlx_data *data);
int		handle_close(t_mlx_data *data);
int		strncmp(const char *s1, const char *s2, size_t n);
void	make_data(t_mlx_data *data);
double	map(double value, double stop1, double start2, double stop2);
int		see_iteration(double c_re, double c_im, double z_re, double z_im);
void	mandelbrot(t_mlx_data *data);
void	julia(t_mlx_data *data, double c_re, double c_im);
int		see_iteration_bar(double c_re, double c_im, double z_re, double z_im);
void	mandelbar(t_mlx_data *data);
void	find_color(t_mlx_data *data);
int		mouse_input(int button, int x, int y, t_mlx_data *data);
void	see_fractal(t_mlx_data *data, double x, double y, char *name);
void	do_fract(t_mlx_data *data);
#endif
