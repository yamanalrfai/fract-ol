/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalrfai <yalrfai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:19:03 by yaman-alrif       #+#    #+#             */
/*   Updated: 2025/01/04 16:26:09 by yalrfai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		divisor;

	result = 0.0;
	fraction = 0.0;
	sign = 1;
	divisor = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		fraction = fraction * 10.0 + (*str++ - '0');
		divisor *= 10;
	}
	return (sign * (result + fraction / divisor));
}

static double	ft_atof_okay(const char *str)
{
	int	dot_count;

	dot_count = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str == '.')
		{
			if (dot_count > 0)
				return (0);
			dot_count++;
		}
		else if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	check_args(char **v)
{
	if (!(ft_atof_okay(v[2]) && ft_atof_okay(v[3])))
		return (0);
	else
		return (1);
}

int	main(int c, char **v)
{
	t_mlx_data	data;

	if ((c == 2 && !strncmp(v[1], "mandelbrot", 11))
		|| (c == 2 && !strncmp(v[1], "mandelbar", 10))
		|| (c == 4 && !strncmp(v[1], "julia", 6) && check_args(v)))
	{
		make_data(&data);
		if (c == 2)
			see_fractal(&data, 0, 0, v[1]);
		else if (c == 4)
			see_fractal(&data, ft_atof(v[2]), ft_atof(v[3]), v[1]);
		mlx_key_hook(data.win_ptr, handle_input, &data);
		mlx_hook(data.win_ptr, 17, 0, handle_close, &data);
		mlx_mouse_hook(data.win_ptr, mouse_input, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
	{
		perror("Usage: ./fractol beetle-mandelbrot-julia <real> <imaginary>");
		exit(EXIT_FAILURE);
	}
	return (0);
}
