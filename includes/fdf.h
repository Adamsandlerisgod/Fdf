/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:08:04 by whendrik          #+#    #+#             */
/*   Updated: 2023/06/28 11:42:15 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct t_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_img;

typedef struct t_temp
{
	float	x2;
	float	y2;
	float	z1;
	float	z2;
}		t_temp;

typedef struct t_mlx
{
	void	*mlx;
	void	*mlx_win;
	int		win_width;
	int		win_height;

}		t_mlx;

typedef struct t_fdf
{
	int		height;
	int		width;
	int		***z_matrix;
	int		zoom;
	int		color;
	int		shift_x;
	int		shift_y;
	float	angle;
	t_mlx	mlx;
	t_img	img;
	t_temp	cor_store;
}		t_fdf;

int		key_hook(int key, t_fdf *data);
int		data_reader(char *filename, t_fdf *data);
void	bresenham(float x1, float y1, float x2, t_fdf *data);
void	draw(t_fdf *data);

/*Adjustables*/
void	zoom(float *x, float *y, t_fdf *data);
void	shift(float *p1, float *p2, t_fdf *data, char t);
void	isometric(float *x, float *y, int z, t_fdf *data);
void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color);
void	zoom_iso(float *x, float *y, int z, t_fdf *data);
void	adjustables(int key, t_fdf *data);
void	memory_store(t_fdf *data);

#endif