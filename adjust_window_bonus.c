/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_window_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:26:01 by abounab           #+#    #+#             */
/*   Updated: 2024/04/18 20:09:38 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	return_y(t_details ***map, int x_width, int y_width, int *y_min)
{
	int	i;
	int	j;
	int	min;
	int	max;

	i = 0;
	min = map[i][i]->y;
	max = map[i][i]->y;
	while (i < y_width)
	{
		j = 0;
		while (j < x_width)
		{
			if (min > map[i][j]->y)
				min = map[i][j]->y;
			if (max < map[i][j]->y)
				max = map[i][j]->y;
			j++;
		}
		i++;
	}
	*y_min = abs(min);
	return (abs(max - min));
}

static int	return_x(t_details ***map, int x_width, int y_width, int *x_min)
{
	int	i;
	int	j;
	int	min;
	int	max;

	i = 0;
	min = map[i][i]->x;
	max = map[i][i]->x;
	while (i < y_width)
	{
		j = 0;
		while (j < x_width)
		{
			if (min > map[i][j]->x)
				min = map[i][j]->x;
			if (max < map[i][j]->x)
				max = map[i][j]->x;
			j++;
		}
		i++;
	}
	*x_min = abs(min);
	return (abs(max - min));
}

int	calculate_dimension(t_mlx_data *mlx)
{
	rotation_matrices(mlx);
	mlx->width_dimension = return_x(mlx->map_cpy, mlx->x_map, mlx->y_map,
			&mlx->x_min);
	mlx->height_dimension = return_y(mlx->map_cpy, mlx->x_map, mlx->y_map,
			&mlx->y_min);
	mlx->scale_x = (double)1000 / mlx->width_dimension;
	mlx->scale_y = (double)1000 / mlx->height_dimension;
	if (!mlx->width_dimension || !mlx->height_dimension)
	{
		if (!mlx->width_dimension)
			mlx->width_dimension = 25;
		if (!mlx->height_dimension)
			mlx->height_dimension = 25;
		return (1);
	}
	if (mlx->scale_x > 1)
		mlx->scale_x = (double)500 / mlx->width_dimension;
	if (mlx->scale_y > 5)
		mlx->scale_y = (double)500 / mlx->height_dimension;
	mlx->width_dimension *= mlx->scale_x;
	mlx->width_dimension += 100;
	mlx->height_dimension *= mlx->scale_y;
	mlx->scale_y /= 1.5;
	return (1);
}

int	esc_button(t_mlx_data *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->image.img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_window);
	clear_map(mlx->mlx_map, mlx->y_map);
	ft_errno("Windows Closed", 0);
	return (1);
}
