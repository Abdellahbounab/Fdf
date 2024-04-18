/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:30:55 by abounab           #+#    #+#             */
/*   Updated: 2024/04/18 16:31:45 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	count_lignes(char *file, int *y_map)
{
	int		fd;
	int		len;
	char	*str;

	len = 0;
	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	if (fd != -1)
	{
		while (str)
		{
			len++;
			free(str);
			str = NULL;
			str = get_next_line(fd);
		}
	}
	close(fd);
	return (*y_map = len, len);
}

static int	create_mlx(t_mlx_data mlx, t_details ***map, char *title)
{
	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		ft_errno("mlx failed", 1);
	mlx.mlx_map = map;
	add_events(&mlx.events);
	calculate_dimension(&mlx);
	mlx.mlx_window = mlx_new_window(mlx.mlx_ptr, mlx.width_dimension,
			mlx.height_dimension, title);
	create_image(&mlx);
	mlx_key_hook(mlx.mlx_window, get_key, &mlx);
	mlx_hook(mlx.mlx_window, 17, 0, exit_program, &mlx);
	mlx_loop(mlx.mlx_ptr);
	mlx_destroy_window(mlx.mlx_ptr, mlx.mlx_window);
	free(mlx.mlx_ptr);
	mlx.mlx_ptr = NULL;
	free(mlx.mlx_window);
	mlx.mlx_window = NULL;
	return (1);
}

static t_details	***valid_axis(char *file, int *x_map, int *y_map)
{
	int			fd;
	int			min_width;
	char		*ligne;
	int			i;
	t_details	***cpy;

	i = 0;
	cpy = (t_details ***)malloc(sizeof(t_details **) * count_lignes(file,
				y_map));
	if (!cpy)
		return (NULL);
	fd = open(file, O_RDONLY);
	ligne = get_next_line(fd);
	min_width = words_count(ligne, " \t\n");
	while (ligne && *ligne)
	{
		cpy[i] = extract_axis(&ligne, min_width, i, *y_map);
		if (!cpy[i])
			return (clear_map(cpy, i - 1), ft_errno("failed", 1), NULL);
		ligne = get_next_line(fd);
		i++;
	}
	if (!min_width)
		return (ft_errno("No data found.", 1), NULL);
	return (*y_map = i, *x_map = min_width, cpy);
}

static int	valid_file(char *name, char *fdf, int len)
{
	int	fd;

	if (ft_strncmp(name + len - 4, fdf, 4))
	{
		fd = open(name, O_RDONLY);
		if (fd > -1)
			return (close(fd), 1);
		close(fd);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_details	***map;
	t_mlx_data	mlx;

	map = NULL;
	if (argc == 2)
	{
		if (valid_file(argv[1], ".fdf", ft_strlen(argv[1])))
		{
			map = valid_axis(argv[1], &mlx.x_map, &mlx.y_map);
			if (map)
				create_mlx(mlx, map, argv[1]);
		}
		else
			ft_errno("No file", 1);
	}
}
