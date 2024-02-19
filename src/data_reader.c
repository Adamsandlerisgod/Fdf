/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:33:52 by whendrik          #+#    #+#             */
/*   Updated: 2023/06/28 12:06:33 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	get_height_width(char *filename, t_fdf *data)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY, 0);
	line = get_next_line(fd);
	data->width = (int)count_strings(line, ' ');
	height = 0;
	while (line != NULL)
	{
		if (data->width != (int)count_strings(line, ' '))
			return ;
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	data->height = height;
}

void	fill_and_free(char **commas, t_fdf *data, int pos_x, int pos_y)
{
	data->z_matrix[pos_y][pos_x][0] = ft_atoi(commas[0]);
	data->z_matrix[pos_y][pos_x][1] = ft_hexatoi(commas[1]);
	free(commas[0]);
	free(commas[1]);
	free(commas);
}

void	fill_matrixinator(char *line, t_fdf *data, int pos_y)
{
	char	**nums;
	int		pos_x;
	char	**commas;

	nums = ft_split(line, ' ');
	pos_x = 0;
	while (pos_x < data->width)
	{
		if (count_strings(nums[pos_x], ',') == 2)
		{
			commas = ft_split(nums[pos_x], ',');
			fill_and_free(commas, data, pos_x, pos_y);
		}
		else
		{
			data->z_matrix[pos_y][pos_x][0] = ft_atoi(nums[pos_x]);
			if (data->z_matrix[pos_y][pos_x][0] == 0)
				data->z_matrix[pos_y][pos_x][1] = 0xFFFFFF;
			else 
				data->z_matrix[pos_y][pos_x][1] = 0x0000FF;
		}
		free(nums[pos_x]);
		pos_x++;
	}
	free(nums);
}

int	data_reader(char *filename, t_fdf *data)
{
	char	*line;
	int		fd;
	int		i;

	get_height_width(filename, data);
	memory_store(data);
	fd = open(filename, O_RDONLY, 0);
	i = 0;
	while (i < data->height)
	{
		line = get_next_line(fd);
		fill_matrixinator(line, data, i);
		free(line);
		i++;
	}
	close(fd);
	data->z_matrix[i] = NULL;
	return (0);
}

/*	1. read file
**		- get height(how many lines) of text
**		- get width(how many numbers in line)
**		- allocate memory for **int by u
sing width and height (look your ft_strsplit() )
**		- read file and write number into **int matrix
**				by using ft_strsplit() and atoi()	*/