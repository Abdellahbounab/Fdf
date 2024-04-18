/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:27:44 by abounab           #+#    #+#             */
/*   Updated: 2024/04/18 17:41:55 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	translate(int key, t_mlx_data *mlx)
{
	if (key == UP)
		mlx->events.vertical--;
	if (key == DOWN)
		mlx->events.vertical++;
	if (key == RIGHT)
		mlx->events.horizone++;
	if (key == LEFT)
		mlx->events.horizone--;
	rotation_matrices(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->image.img);
	create_image(mlx);
	return (1);
}

static int	rotate(int key, t_mlx_data *mlx)
{
	if (key == Z_BTN)
		mlx->events.z_rotation -= 0.05;
	if (key == X_BTN)
		mlx->events.x_rotation += 0.5;
	if (key == Y_BTN)
		mlx->events.y_rotation += 0.5;
	rotation_matrices(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->image.img);
	create_image(mlx);
	return (1);
}

static int	zoom(int key, t_mlx_data *mlx)
{
	if (key == ZOOM_IN)
		mlx->events.zoom += 0.5;
	if (key == ZOOM_OUT)
		mlx->events.zoom -= 0.5;
	rotation_matrices(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->image.img);
	create_image(mlx);
	return (1);
}

static int	parallel(t_mlx_data *mlx)
{
	if (mlx->events.parallel)
	{
		mlx->events.parallel = 0;
		mlx->events.x_rotation = 1.585;
	}
	else
	{
		mlx->events.parallel = 1;
		mlx->events.x_rotation = M_PI_4;
	}
	rotation_matrices(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->image.img);
	create_image(mlx);
	return (1);
}

int	get_key(int key, t_mlx_data *mlx)
{
	if (key == UP || key == DOWN || key == RIGHT || key == LEFT)
		translate(key, mlx);
	else if (key == Z_BTN || key == X_BTN || key == Y_BTN)
		rotate(key, mlx);
	else if (key == ZOOM_IN || key == ZOOM_OUT)
		zoom(key, mlx);
	else if (key == BTN_0)
		parallel(mlx);
	else if (key == EXTRA)
		extra_2d_projection(mlx);
	else if (key == COLORING)
		extra_coloring(mlx);
	else if (key == ESC)
		esc_button(mlx);
	return (1);
}
