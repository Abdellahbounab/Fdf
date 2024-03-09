/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:19:24 by abounab           #+#    #+#             */
/*   Updated: 2024/03/09 22:50:52 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_errno(void)
{
	write (2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	free_arr(char **arr, int len)
{
	int	i;

	i = 0;
	while (arr && i < len)
		free(arr[i++]);
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

int	ft_strchr(char *str, unsigned char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atox(char *str ,int *i)
{
	int	num;
	int	val;
	char *hexa;

	num = 0;
	*i += 2;
	hexa = "0123456789abcdef";
	while (str && str[*i])
	{
		val = ft_strchr(hexa ,str[*i]);
		if (val > -1)
		{
			num *= 16;
			num += val;
		}
		else
			break;
		(*i)++;
	}
	if (str && str[*i] && (str[*i] != ' ' || str[*i] != '\t'))
		num = 0;
	while (str && str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	return (num);
}

int	ft_atoi(char *str ,int *i)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	if (str && (str[*i] == '-' || str[*i] == '+'))
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	while (str && str[*i] && str[*i] >= '0' && str[*i] <= '9')
	{
		num *= 10;
		num += str[*i] - '0';
		(*i)++;
	}
	if (str && str[*i] && (str[*i] != ' ' || str[*i] != '\t'))
		num = 0;
	while (str && str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	return (num * sign);
}

int	get_value(char *str, int *i) //have to implements the hexa part
{
	int val;
	int sign;
	int num;

	val = 0;
	sign = 1;
	num = 0;
	if (str[*i] == ',')
		(*i)++;
	if (ft_strlen(str) > 2 && ft_strncmp(str, "0x", 2))
		num = ft_atox(str, i);
	else
		num = ft_atoi(str, i);
	return (num);
}

t_details *get_data(char *str, int x_val, int y_val)
{
	t_details *axis;
	int	i;

	i = 0;
	axis = (t_details *) malloc (sizeof(t_details));
	if (axis)
	{
		axis->x = x_val;
		axis->y = y_val;
		axis->z = get_value(str, &i); //get value would get the number in hexa or decimal (if error assign to 0, (white color is a default color))
		axis->color = 0xFFFFFF; //default color (white)
		axis->opacity = 100;
		if (str[i])
			axis->color = get_value(str, &i);
		if (str[i])
			axis->opacity = get_value(str, &i);//opacity would be activated only if bonus part is maked
		return (axis);
	}
	return (NULL);
}

int	words_count(char *str)
{
	int	len;

	len = 0;
	if (*str && (*str != ' ' && *str != '\t' && *str != '\n'))
	{
		len++;
		str++;
	}
	while (*str)
	{
		if (*str && (*str != ' ' && *str != '\t' && *str != '\n')
			&& ((*(str - 1) == ' ') || (*(str - 1) == '\t') 
				|| (*(str - 1) == '\n')))
			len++;
		str++;
	}
	return (len);
}

int	word_len(char **str)
{
	int	len;

	len = 0;
	while (*str && (**str == ' ' || **str == '\t' || **str == '\n'))
		(*str)++;
	while (**str && **str != ' ' && **str != '\t' && **str != '\n')
	{
		(*str)++;
		len++;
	}
	return (len);
}

char	*ft_strdups(char *str, int len)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = (char *) malloc (sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	while (i < len)
	{
		*(cpy + i) = *(str + i);
		i++;
	}
	*(cpy + i) = 0;
	return (cpy);
}

char	**ft_split_space(char *str, int *len)
{
	char	**arr;
	int		i;

	i = 0;
	*len = words_count(str);
	if (len)
	{
		arr = (char **) malloc (sizeof(char *) * (*len + 1));
		if (!arr)
			return (NULL);
		while (*str && i < *len)
		{
			while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
				str++;
			if (*str)
			{
				*(arr + i) = ft_strdups(str, word_len(&str));
				if (!*(arr + i))
					return (free_arr(arr, i), NULL);
				i++;
			}
		}
		return (*(arr + i) = 0, arr);
	}
	return (0);
}

void free_axis(t_details ***map)
{
	int i;

	i = 0;
	while (*map && *map[i])
	{
		free(*map[i]);
		*map[i] = NULL;
		i++;
		printf("i : %d\n", i);
	}
}

int extract_axis(char *ligne, t_details ***map, int min_width, int x)
{
	char **arr;
	int	y;
	int len;

	y = 0;
	//gettin every line data into the map : *map[j] (malloced)
	arr = ft_split_space(ligne, &len);
	if (len >= min_width)
	{
		*map = (t_details **) malloc (sizeof(t_details *) * len);
		if (!arr)
			return (free(map), free_arr(arr, len), 0);
		while (arr[y])
		{
			printf("str : %d (", y);
			*map[y] = get_data(arr[y], x, y);
			if (!*map[y])
				return (free_arr(arr, len), free_axis(map), 0);
			printf("extract_axis(%d, %d, %d)\n", (*map[y])->x, (*map[y])->y, (*map[y])->z);
			y++;
		}
		return (free_arr(arr, len), 1);
	}
	return (0);
}

void clear_map(t_details ***map, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free_axis(&map[i]);
	}
}

int	valid_axis(char *file, t_details ***map)
{
	int		fd;
	int		min_width;
	char	*ligne;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	ligne = get_next_line(fd);
	min_width = words_count(ligne);//get the number of elements in the first line after checking valid digits && hexa for colors
	// printf("min width : %d\n", min_width);
	while (ligne && *ligne)
	{
		// check if map have the same width length as the first line or higher : if less == error
		// check if map is only digits && colors hexa or decimal && insert the data required depends on its x, y, z
		if (extract_axis(ligne, &map[i], min_width, i))
		{
			free(ligne);
			printf("valid_axis: (%d, %d, %d)\n", map[i][0]->x, map[i][0]->y,map[i][0]->z);
			ligne = get_next_line(fd);
		}
		else    //freeing all malloced axises before exit
			return (printf("error extract\n"), free(ligne), clear_map(map, i - 1), ft_errno(), 0);
		i++;	
	}
	if (!min_width)
		return (free(ligne), ft_errno(), 0);
	return (1);
}

int	valid_file(char *name, char *fdf, int len)
{
	int fd;

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
	// void	*mlx;
	// void	*mlx_win;
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
				printf("done\n");
			}
		}
		else
			printf("error : file error\n");
	}




	//about map :
			//min width must be in first line
			//only digits can make the highness or will get z'0
			//colors can take hexa or decimal
			//if planning for bonus must add opacity



	// mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, 500, 500, "Abounab");
	// draw_line(mlx, mlx_win, 500, 500, 0, 0, 0xFFFFFF);
	// draw_line(mlx, mlx_win, 500, 0, 0, 500, 0xFFFFFF);
	// mlx_mouse_hook(mlx_win, &mouse_event, 0);
	// mlx_loop(mlx);
	// mlx_destroy_display(mlx);
}
