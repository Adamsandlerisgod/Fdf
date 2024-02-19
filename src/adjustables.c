/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjustables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:36:12 by whendrik          #+#    #+#             */
/*   Updated: 2023/06/28 12:12:14 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	if ((x <= 0) || (x > data->mlx.win_width))
		return ;
	if ((y <= 0) || (y > data->mlx.win_height))
		return ;
	dst = data->img.addr + (y * data->img.line_length + x * 
			(data->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	shift(float *p1, float *p2, t_fdf *data, char t)
{
	if (t == 'x')
	{
		*p1 += data->shift_x;
		*p2 += data->shift_x;
	}
	else if (t == 'y')
	{
		*p1 += data->shift_y;
		*p2 += data->shift_y;
	}
}

void	zoom_iso(float *x, float *y, int z, t_fdf *data)
{
	*x *= data->zoom;
	*y *= data->zoom;
	*x = (*x - *y) * cos(data->angle);
	*y = (*x + *y) * sin(data->angle) - z;
}

void	memory_store(t_fdf *data)
{
	int	i;
	int	j;

	data->z_matrix = (int ***)malloc(sizeof(int **) * (data->height + 1));
	i = 0;
	while (i < data->height)
	{
		j = 0;
		data->z_matrix[i] = (int **)malloc(sizeof(int *) * (data->width + 1));
		while (j < data->width)
		{
			data->z_matrix[i][j] = (int *)malloc(sizeof(int) * 2);
			j++;
		}
		data->z_matrix[i][j] = NULL;
		i++;
	}
}

void	adjustables(int key, t_fdf *data)
{
	if (key == 123)
		data->shift_x -= 20;
	if (key == 124)
		data->shift_x += 20;
	if (key == 126)
		data->shift_y -= 20;
	if (key == 125)
		data->shift_y += 20;
	if (key == 27 && data->zoom - 1 >= 0)
		data->zoom -= 1;
	if (key == 24 && data->zoom + 1 <= 40)
		data->zoom += 2;
	if (key == 25)
		data->angle -= 0.1;
	if (key == 29)
		data->angle += 0.1;
}
