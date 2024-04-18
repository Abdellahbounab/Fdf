/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:33:34 by abounab           #+#    #+#             */
/*   Updated: 2024/04/18 19:42:52 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static t_details	*create_data(int y_val, int x_val, int arr_len, int max_y)
{
	t_details	*axis;
	int			plus;

	axis = (t_details *)malloc(sizeof(t_details));
	if (!axis)
		return (NULL);
	plus = 100;
	if (max_y < 100)
		plus = 100 / max_y;
	axis->y = y_val * plus;
	axis->x = x_val * plus;
	axis->z = plus;
	axis->color = 0xFFFFFF;
	axis->length = arr_len;
	return (axis);
}

static int	cpy_map(t_mlx_data *mlx, t_details ****cpy)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mlx->y_map)
	{
		j = -1;
		(*cpy)[i] = (t_details **)malloc(sizeof(t_details *) * mlx->x_map);
		while (++j < mlx->x_map)
		{
			(*cpy)[i][j] = create_data(i + mlx->events.vertical, j
					+ mlx->events.horizone, mlx->x_map, mlx->y_map);
			if (!(*cpy)[i][j])
				return (free_axis(cpy[i], j), clear_map((*cpy), i), 0);
			increase(&(*cpy)[i][j], mlx->events.zoom);
			if ((*cpy)[i][j]->z)
				(*cpy)[i][j]->z = mlx->mlx_map[i][j]->z;
			if (mlx->events.coloring && (*cpy)[i][j]->z <= 0)
				(*cpy)[i][j]->color = 0;
			else
				(*cpy)[i][j]->color = mlx->mlx_map[i][j]->color;
		}
	}
	return (1);
}

t_details	***get_mlx_cpy(t_mlx_data *mlx)
{
	t_details	***cpy;

	cpy = (t_details ***)malloc(sizeof(t_details **) * mlx->y_map);
	if (!cpy)
		return (NULL);
	if (!cpy_map(mlx, &cpy))
		return (NULL);
	return (cpy);
}

static t_details	*get_data(char *str, int y_val, int x_val, int len[])
{
	t_details	*axis;
	char		**arr;
	int			length;

	length = 0;
	arr = ft_split_space(str, " ,", &length);
	if (arr)
	{
		axis = create_data(y_val, x_val, len[0], len[1]);
		if (axis)
		{
			axis->z *= get_value(arr[0]);
			if (length > 1)
				axis->color = get_value(arr[1]);
			if (!length || (length == 1 && str[ft_strlen(str) - 1] == ','))
				axis->color = 0;
			return (free_arr(arr, length), axis);
		}
		return (free_arr(arr, length), NULL);
	}
	return (free_arr(arr, length), NULL);
}

t_details	**extract_axis(char **ligne, int min_width, int y, int max_y)
{
	char		**arr;
	int			x;
	int			len[2];
	t_details	**cpy;

	x = 0;
	arr = ft_split_space(*ligne, " \t\n", &len[0]);
	free(*ligne);
	len[1] = max_y;
	*ligne = NULL;
	if (len[0] >= min_width)
	{
		cpy = (t_details **)malloc(sizeof(t_details *) * len[0]);
		if (!cpy)
			return (free_arr(arr, len[0]), NULL);
		while (x < len[0])
		{
			cpy[x] = get_data(arr[x], y, x, len);
			if (!cpy[x])
				return (free_arr(arr, len[0]), free_axis(&cpy, len[0]), NULL);
			x++;
		}
		return (free_arr(arr, len[0]), cpy);
	}
	return (free_arr(arr, len[0]), NULL);
}
