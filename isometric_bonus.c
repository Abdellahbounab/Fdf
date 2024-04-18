/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:35:04 by abounab           #+#    #+#             */
/*   Updated: 2024/04/18 16:37:34 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	rotate_by_y(t_details **map, double raduis)
{
	int	cpy_x;
	int	cpy_y;
	int	cpy_z;

	cpy_x = (*map)->x;
	cpy_y = (*map)->y;
	cpy_z = (*map)->z;
	(*map)->x = cos(raduis) * cpy_x + 0 * cpy_y + sin(raduis) * cpy_z;
	(*map)->y = 0 * cpy_x + 1 * cpy_y + 0 * cpy_z;
	(*map)->z = -sin(raduis) * cpy_z + 0 * cpy_y + cos(raduis) * cpy_z;
}

static void	rotate_by_x(t_details **map, double raduis)
{
	int	cpy_x;
	int	cpy_y;
	int	cpy_z;

	cpy_x = (*map)->x;
	cpy_y = (*map)->y;
	cpy_z = (*map)->z;
	(*map)->x = 1 * cpy_x + 0 * cpy_y + 0 * cpy_z;
	(*map)->y = 0 * cpy_x + cos(raduis) * cpy_y + -sin(raduis) * cpy_z;
	(*map)->z = 0 * cpy_z + sin(raduis) * cpy_y + cos(raduis) * cpy_z;
}

static void	rotate_by_z(t_details **map, double raduis)
{
	int	cpy_x;
	int	cpy_y;
	int	cpy_z;

	cpy_x = (*map)->x;
	cpy_y = (*map)->y;
	cpy_z = (*map)->z;
	(*map)->x = cos(raduis) * cpy_x + -sin(raduis) * cpy_y + 0 * cpy_z;
	(*map)->y = sin(raduis) * cpy_x + cos(raduis) * cpy_y + 0 * cpy_z;
	(*map)->z = 0 * cpy_z + 0 * cpy_y + 1 * cpy_z;
}

int	rotation_matrices(t_mlx_data *mlx)
{
	int	i;
	int	j;

	i = 0;
	mlx->map_cpy = get_mlx_cpy(mlx);
	while (i < mlx->y_map)
	{
		j = 0;
		while (j < mlx->x_map)
		{
			if (mlx->events.projection)
			{
				if (mlx->events.parallel)
					rotate_by_z(&mlx->map_cpy[i][j],
						mlx->events.z_rotation);
				rotate_by_x(&mlx->map_cpy[i][j], mlx->events.x_rotation);
				if (mlx->events.y_rotation)
					rotate_by_y(&mlx->map_cpy[i][j],
						mlx->events.y_rotation);
			}
			j++;
		}
		i++;
	}
	return (1);
}
