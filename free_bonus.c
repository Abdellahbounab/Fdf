/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:33:03 by abounab           #+#    #+#             */
/*   Updated: 2024/04/18 16:33:21 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_errno(char *str, int sign)
{
	if (!sign)
	{
		write(1, "\033[32mSuccess: ", 15);
		write(1, str, ft_strlen(str));
		write(1, "\033[0m", 4);
	}
	else
	{
		write(1, "\033[31mError: ", 13);
		write(1, str, ft_strlen(str));
		write(1, "\033[0m", 4);
	}
	exit(sign);
	return (0);
}

void	free_arr(char **arr, int len)
{
	int	i;

	i = 0;
	while (arr && arr[i] && i < len)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_axis(t_details ***map, int len)
{
	int			i;
	t_details	**cpy;

	i = 0;
	cpy = *map;
	while (cpy && cpy[i] && i < len)
	{
		free(cpy[i]);
		cpy[i] = NULL;
		i++;
	}
	free(cpy);
	cpy = NULL;
}

void	clear_map(t_details ***map, int len)
{
	int	i;

	i = 0;
	while (map[i] && i < len)
	{
		free_axis(map + i, (*map[i])->length);
		i++;
	}
}

int	exit_program(t_mlx_data *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->image.img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_window);
	clear_map(mlx->mlx_map, mlx->y_map);
	return (ft_errno("Windows Closed", 0));
}
