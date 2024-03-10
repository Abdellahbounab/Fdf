/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:19:24 by abounab           #+#    #+#             */
/*   Updated: 2024/03/10 19:29:12 by abounab          ###   ########.fr       */
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
	char *hexa_maj;

	num = 0;
	*i += 2;
	hexa = "0123456789abcdef";
	hexa_maj = "0123456789ABCDEF";
	while (str && str[*i])
	{
		val = ft_strchr(hexa ,str[*i]);
		if (val == -1)
			val = ft_strchr(hexa_maj, str[*i]);
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
	if (ft_strlen(str) == 8  && ft_strncmp(str, "0x", 1))
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
		if (str && str[i])
			axis->color = get_value(str, &i);
		if (str && str[i])
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
	t_details **cpy;

	y = 0;
	//gettin every line data into the map : *map[j] (malloced)
	arr = ft_split_space(ligne, &len);
	if (len >= min_width)
	{
		cpy = (t_details **) malloc (sizeof(t_details *) * len);
		if (!cpy)
			return (free_arr(arr, len), 0);
		while (y < len)
		{
			cpy[y] = get_data(arr[y], x, y);
			if (!cpy)
				return (free_arr(arr, len), free_axis(map), 0);
			y++;
		}
		*map = cpy;
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

int count_lignes(char *file)
{
	int fd = open (file, O_RDONLY);
	int len;

	len = 0;
	if (fd != -1)
	{
		while (get_next_line(fd))
			len++;
	}
	close(fd);
	return (0);
}

int	valid_axis(char *file, t_details ****map)
{
	int		fd;
	int		min_width;
	char	*ligne;
	int		i;
	t_details ***cpy;

	i = 0;
	cpy = (t_details ***) malloc (sizeof(t_details **) * count_lignes(file));
	fd = open(file, O_RDONLY);
	ligne = get_next_line(fd);
	min_width = words_count(ligne);
	while (ligne && *ligne)
	{
		if (extract_axis(ligne, &cpy[i], min_width, i))
		{
			// printf("(%s)", ligne);
			free(ligne);
			ligne = NULL;
			// printf("valid_axis: (%d, %d, %d, %d)\n", cpy[i][0]->x, cpy[i][0]->y, cpy[i][0]->z, cpy[i][0]->color);
			ligne = get_next_line(fd);
		}
		else    //freeing all malloced axises before exit
			return (printf("error extract\n"), free(ligne), clear_map(*map, i - 1), ft_errno(), 0);
		i++;	
	}
	if (!min_width)
		return (free(ligne), ft_errno(), 0);
	*map = cpy;
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
	void	*mlx;
	void	*mlx_win;
	t_details	***map;

	map = NULL;
	// starting point :
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
	// 		// check if map have the same width length as the first line or higher : if less == error
			if (valid_axis(argv[1], &map)) // check if map is only digits && colors hexa or decimial && insert the data required depends on its x, y, z
			{
	// 			// using the lib mlx to draw the lines that i got from map[][]
				mlx = mlx_init();
				int i = 0;
				// printf("map[0][0]:%d\n", map[0][0]->z);
				while (i < 10)
				{
					mlx_win = mlx_new_window(mlx, 500, 500, "Abounab");
					// draw_line(mlx, mlx_win, map[i][0], 500, 0, 0, 0xFFFFFF);
					mlx_pixel_put(mlx, mlx_win, 255, 255, map[i][0]->color);
					printf("(%d)", map[i][0]->z);
					i++;
					mlx_loop(mlx);
				}
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
