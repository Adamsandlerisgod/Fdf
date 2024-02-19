/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:18:48 by whendrik          #+#    #+#             */
/*   Updated: 2023/06/28 12:20:52 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

int	key_hook(int key, t_fdf *data)
{
	printf("%d \n", key);
	if (key == 53)
	{
		mlx_destroy_image(data->mlx.mlx, data->img.img);
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
		exit (0);
		return (0);
	}
	adjustables(key, data);
	mlx_destroy_image(data->mlx.mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx.mlx, data->mlx.win_width
			+ (data->zoom * 100), data->mlx.win_height + (data->zoom * 80));
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	draw(data);
	return (0);
}

int	loop_hook(t_fdf *data)
{
	mlx_destroy_image(data->mlx.mlx, data->img.img);
	mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	exit (0);
}

void	presets(t_fdf *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.win_width = 1500;
	data->mlx.win_height = 1200;
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->mlx.win_width,
			data->mlx.win_height, "fdf");
	data->img.img = mlx_new_image(data->mlx.mlx, data->mlx.win_width,
			data->mlx.win_height);
	data->img.addr = mlx_get_data_addr(data->img.img, 
			&data->img.bits_per_pixel, &data->img.line_length,
			&data->img.endian);
	if (data->width < 200 && data->height < 150)
		data->zoom = 40;
	else
		data->zoom = 2;
	data->shift_x = 550;
	data->shift_y = 350;
	data->angle = 0.5;
}

int	main(int ac, char **argv)
{
	t_fdf	*data;

	if (ac == 2)
	{
		data = (t_fdf *)malloc(sizeof(t_fdf));
		data_reader(argv[1], data);
		presets(data);
		draw(data);
		mlx_key_hook(data->mlx.mlx_win, key_hook, data);
		mlx_hook(data->mlx.mlx_win, 17, 0, loop_hook, data);
		mlx_loop(data->mlx.mlx);
	}
	return (0);
}
