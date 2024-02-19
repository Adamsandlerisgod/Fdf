/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:59:27 by whendrik          #+#    #+#             */
/*   Updated: 2023/06/28 12:06:21 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

float	mod(float i)
{
	if (i < 0)
		return (-i);
	return (i);
}

float	max_1(float i, float j)
{
	if (i > j)
		return (i);
	return (j);
}

void	bresenham_x(float x1, float y1, float x2, t_fdf *data)
{
	float	x_step;
	float	y_step;
	float	max;
	float	y2;

	data->cor_store.z1 = data->z_matrix[(int)y1][(int)x1][0];
	data->cor_store.z2 = data->z_matrix[(int)y1][(int)(x2)][0];
	y2 = y1;
	zoom_iso(&x1, &y1, data->cor_store.z1, data);
	zoom_iso(&x2, &y2, data->cor_store.z2, data);
	shift(&x1, &x2, data, 'x');
	shift(&y1, &y2, data, 'y');
	max = max_1(mod((x2 - x1)), mod((y2 - y1)));
	x_step = (x2 - x1) / max;
	y_step = (y2 - y1) / max;
	while ((int)(x1 - x2) || (int)(y1 - y2))
	{
		my_mlx_pixel_put(data, x1, y1, data->color);
		x1 += x_step;
		y1 += y_step;
	}
}

void	bresenham_y(float x1, float y1, float y2, t_fdf *data)
{
	float	x_step;
	float	y_step;
	float	max;
	float	x2;

	data->cor_store.z1 = data->z_matrix[(int)y1][(int)x1][0];
	data->cor_store.z2 = data->z_matrix[(int)y2][(int)x1][0];
	x2 = x1;
	zoom_iso(&x1, &y1, data->cor_store.z1, data);
	zoom_iso(&x2, &y2, data->cor_store.z2, data);
	shift(&x1, &x2, data, 'x');
	shift(&y1, &y2, data, 'y');
	max = max_1(mod((x2 - x1)), mod((y2 - y1)));
	x_step = (x2 - x1) / max;
	y_step = (y2 - y1) / max;
	while ((int)(x1 - x2) || (int)(y1 - y2))
	{
		my_mlx_pixel_put(data, x1, y1, data->color);
		x1 += x_step;
		y1 += y_step;
	}
}

void	draw(t_fdf *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			data->color = data->z_matrix[(int)y][(int)x][1];
			if (x < data->width -1)
				bresenham_x(x, y, x + 1, data);
			if (y < data->height -1)
				bresenham_y(x, y, y + 1, data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx.mlx,
		data->mlx.mlx_win, data->img.img, 0, 0);
}
