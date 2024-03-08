/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:19:24 by abounab           #+#    #+#             */
/*   Updated: 2024/03/08 20:29:28 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mlx.h>
#include "get_next_line.h"

typedef struct s_details{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_details;

int	valid_axis(char *file, t_details ***map)
{
	int		fd;
	char	*ligne;

	fd = open(file, O_RDONLY);
	ligne = get_next_line(fd);
	while (ligne)
	{
		// check if map have the same width length as the first line or higher : if less == error
		extract_axis(ligne, map);
		// check if map is only digits && colors hexa or decimial && insert the data required depends on its x, y, z
		
		ligne = get_next_line(fd);
	}
}

int	ft_strncmp(char *str, char *cmp, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (str[i] != cmp[i])
			return (0);
		i++;
	}
	if (!(str[i] - cmp[i]))
		return (1);
	return (0);
}

int	valid_file(char *name, char *fdf, int len)
{
	if (ft_strncmp(name + len - 4, fdf, 4))
		if (open(name, O_RDONLY) != -1)
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_details	**map;


	//starting point :
			// 1 - validate .fdf file from argv[1]
			// 2 - check map : get all lines length as the first one
			// 3 - get details from the map (matrices of [x(width)][y(length)]) and getting the axis z
			// 3 - handle the hexa or decimal colors in each point
			// 4 - draw the points inside the mlx while connecting every point with its (x - 1) (x + 1) (y + 1) (y - 1)
			// 5 - rending colors with every points
	
	if (argc == 2)
	{
		if (valid_file(argv[1], ".fdf", ft_strlen(argv[1]))) // check file if end with .fdf , if exist, if permissions
		{
			// check if map have the same width length as the first line or higher : if less == error
			if (valid_axis(argv[1], &map)) // check if map is only digits && colors hexa or decimial && insert the data required depends on its x, y, z
			{
				// using the lib mlx to draw the lines that i got from map[][]
			}
		}
	}




	// mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, 500, 500, "Abounab");
	// draw_line(mlx, mlx_win, 500, 500, 0, 0, 0xFFFFFF);
	// draw_line(mlx, mlx_win, 500, 0, 0, 500, 0xFFFFFF);
	// mlx_mouse_hook(mlx_win, &mouse_event, 0);
	// mlx_loop(mlx);
	// mlx_destroy_display(mlx);
}
