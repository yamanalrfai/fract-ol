/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalrfai <yalrfai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:23:23 by yalrfai           #+#    #+#             */
/*   Updated: 2025/01/04 15:26:25 by yalrfai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	find_color(t_mlx_data *data)
{
	if (data->color == 0xFF00FF)
		data->color = 0x0000FF;
	else
		data->color = 0xFF00FF;
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

double	map(double value, double stop1, double start2, double stop2)
{
	return (start2 + (stop2 - start2) * ((value) / (stop1)));
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
