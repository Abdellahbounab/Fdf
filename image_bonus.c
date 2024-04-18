/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:34:19 by abounab           #+#    #+#             */
/*   Updated: 2024/04/18 19:56:20 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	increase(t_details **data, int zoom)
{
	int	old_plus;

	old_plus = (*data)->z;
	if (old_plus + zoom > 0)
	{
		(*data)->x = (*data)->x / old_plus * (old_plus + zoom);
		(*data)->y = (*data)->y / old_plus * (old_plus + zoom);
		(*data)->z = old_plus + zoom;
	}
	else
	{
		(*data)->x = 0;
		(*data)->y = 0;
		(*data)->z = 0;
	}
	return (1);
}

void	create_image(t_mlx_data *mlx)
{
	int	i;
	int	j;

	i = 0;
	mlx->image.img = mlx_new_image(mlx->mlx_ptr, mlx->width_dimension,
			mlx->height_dimension);
	mlx->image.addr = mlx_get_data_addr(mlx->image.img, &mlx->image.bit_px, 
			&mlx->image.line_length, &mlx->image.endian);
	while (i < mlx->y_map)
	{
		j = 0;
		while (j < mlx->x_map)
		{
			if (j + 1 < mlx->x_map)
				dda(*mlx, *mlx->map_cpy[i][j], *mlx->map_cpy[i][j + 1]);
			if (i + 1 < mlx->y_map)
				dda(*mlx, *mlx->map_cpy[i][j], *mlx->map_cpy[i + 1][j]);
			j++;
		}
		i++;
	}
	clear_map(mlx->map_cpy, i);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, mlx->image.img, 0,
		0);
	mlx_instruction_put(*mlx);
}

int	add_events(t_hook *events)
{
	events->z_rotation = -(M_PI_4);
	events->y_rotation = 0;
	events->x_rotation = atan(sqrt(2));
	events->horizone = 0;
	events->vertical = 0;
	events->zoom = 0;
	events->parallel = 1;
	events->projection = 1;
	events->coloring = 0;
	return (1);
}
