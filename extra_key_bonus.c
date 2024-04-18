/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_key_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:30:56 by abounab           #+#    #+#             */
/*   Updated: 2024/04/18 17:00:01 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	extra_2d_projection(t_mlx_data *mlx)
{
	if (mlx->events.projection)
		mlx->events.projection = 0;
	else
		mlx->events.projection = 1;
	rotation_matrices(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->image.img);
	create_image(mlx);
	return (1);
}

int	extra_coloring(t_mlx_data *mlx)
{
	if (mlx->events.coloring)
		mlx->events.coloring = 0;
	else
		mlx->events.coloring = 1;
	rotation_matrices(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->image.img);
	create_image(mlx);
	return (1);
}

int	mlx_instruction_put(t_mlx_data mlx)
{
	void	*ptr;
	void	*window;

	ptr = mlx.mlx_ptr;
	window = mlx.mlx_window;
	mlx_string_put(ptr, window, 10, 10, 0xFF0000, "Instructions :");
	mlx_string_put(ptr, window, 15, 25, 255, "Rotation(z, x, y)");
	mlx_string_put(ptr, window, 15, 40, 255, "Translate(<,^, >, v)");
	mlx_string_put(ptr, window, 15, 55, 255, "Zooooooom(p, m)");
	mlx_string_put(ptr, window, 15, 70, 255, "Parallel(0)");
	mlx_string_put(ptr, window, 15, 85, 255, "Extra(space/delete)");
	return (1);
}
