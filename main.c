/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:19:24 by abounab           #+#    #+#             */
/*   Updated: 2024/03/12 15:54:10 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void read_map(t_details **map)
{
	int i = 0;
	int len = 0;
	
	if (map[0])
		len = map[0]->length;
	while(i < len)
	{
		printf("(%d, %d, %d)", map[i]->z, map[i]->x, map[i]->y);
		i++;
	}
	printf("\n");
}

void ft_errno(void)
{
	write (2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	free_arr(char **arr, int len)
{
	int	i;

	i = 0;
	while (arr && arr[i] && i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
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

//if found = i else -1
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

int	ft_atox(char *str)
{
	int	num;
	int	val;
	int i;
	char *hexa;
	char *hexa_maj;

	num = 0;
	i = 2;
	hexa = "0123456789abcdef";
	hexa_maj = "0123456789ABCDEF";
	while (str && str[i] && i < 8)
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			val = ft_strchr(hexa_maj ,str[i]);
		else
			val = ft_strchr(hexa, str[i]);
		if (val > -1)
		{
			num *= 16;
			num += val;
		}
		else
			break;
		i++;
	}
	// printf("num : %d\n", num);
	if (str && str[i] && (str[i] != ' ' || str[i] != '\t'))
		num = 0;
	while (str && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (num);
}

int	ft_atoi(char *str)
{
	int	num;
	int	sign;
	int i;

	num = 0;
	sign = 1;
	i = 0;
	if (str && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str && str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	if (str && str[i] && (str[i] != ' ' || str[i] != '\t'))
		num = 0;
	while (str && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (num * sign);
}

int	  get_value(char *str) //have to implements the hexa part
{
	int num;

	num = 0;
	if (ft_strncmp(str, "0x", 1))
		num = ft_atox(str);
	else
		num = ft_atoi(str);
	return (num);
}

t_details *create_data(int x_val, int y_val, int arr_len)
{
	t_details *axis;

	axis = (t_details *) malloc (sizeof(t_details));
	if (axis)
	{	
		axis->x = x_val;
		axis->y = y_val;
		axis->z = 0; //get value would get the number in hexa or decimal (if error assign to 0, (white color is a default color))
		axis->color = 0xFFFFFF; //default color (white)
		axis->opacity = 100;
		axis->length = arr_len;
	}
	return (axis);
}

t_details *get_data(char *str, int x_val, int y_val, int arr_len)
{
	t_details *axis;
	char **arr;
	int	len;

	len = 0;
	arr = ft_split_space(str, ",\0", &len);
	axis = (t_details *) malloc (sizeof(t_details));
	if (axis && arr && len)
	{
		axis = create_data(x_val, y_val, arr_len);
		axis->z = get_value(arr[0]); //get value would get the number in hexa or decimal (if error assign to 0, (white color is a default color))
		if (len > 1)
			axis->color = get_value(arr[1]);
		if (len > 2)
			axis->opacity = get_value(arr[2]);//opacity would be activated only if bonus part is maked
		return (axis);
	}
	return (NULL);
}

int	words_count(char *str, char *charset)
{
	int	len;

	len = 0;
	if (*str && ft_strchr(charset, *str) == -1)
	{
		len++;
		str++;
	}
	while (*str)
	{
		if (*str && ft_strchr(charset, *str) == -1 && ft_strchr(charset , *(str - 1)) != -1)
			len++;
		str++;
	}
	return (len);
}

int	word_len(char **str, char *charset)
{
	int	len;

	len = 0;
	while (*str && ft_strchr(charset, **str) != -1)
		(*str)++;
	while (**str && ft_strchr(charset, **str) == -1)
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

char	**ft_split_space(char *str, char *charset, int *len)
{
	char	**arr;
	int		i;

	i = 0;
	*len = words_count(str, charset);
	if (str && *len)
	{
		arr = (char **) malloc (sizeof(char *) * (*len + 1));
		if (!arr)
			return (NULL);
		while (str && *str && i < *len)
		{
			while (*str && ft_strchr(charset, *str) != -1)
				str++;
			if (*str)
			{
				*(arr + i) = ft_strdups(str, word_len(&str, charset));
				if (!*(arr + i))
					return (free_arr(arr, i), NULL);
				i++;
			}
		}
		return (*(arr + i) = 0, arr);
	}
	return (0);
}

void free_axis(t_details ***map, int len)
{
	int i;

	i = 0;
	while (*map && i < len)
	{
		// printf("(%d, %d, %d, %d)", (*map[i])->x, (*map[i])->y, (*map[i])->z, (*map[i])->color);
		free(*map[i]);
		*map[i] = NULL;
		printf("i : %d\n", i);
		i++;
	}
	printf("\n");
}

int extract_axis(char *ligne, t_details ***map, int min_width, int x)
{
	char **arr;
	int	y;
	int len;
	t_details **cpy;

	y = 0;
	len = 0;
	arr = ft_split_space(ligne, " \t\n\0",&len);
	if (len >= min_width)
	{
		cpy = (t_details **) malloc (sizeof(t_details *) * len);
		if (!cpy)
			return (free_arr(arr, len), 0);
		while (y < len)
		{
			cpy[y] = get_data(arr[y], x, y, len);
			if (!cpy)
				return (free_arr(arr, len), free_axis(&cpy, len), 0);
			y++;
		}
		*map = cpy;
		return (free_arr(arr, len), 1);
	}
	return (free_arr(arr, len), 0);
}

void clear_map(t_details ***map, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		printf("(%d)\n", (*map[i])->length);
		free_axis(&map[i], (*map[i])->length);
		i++;
	}
}

int count_lignes(char *file)
{
	int fd ;
	int len;
	char *str;

	len = 0;
	fd = open (file, O_RDONLY);
	str = get_next_line(fd);
	if (fd != -1)
	{
		while (str)
		{
			len++;
			str = get_next_line(fd);
		}
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
	min_width = words_count(ligne, " \0");
	while (ligne && *ligne)
	{
		if (extract_axis(ligne, &cpy[i], min_width, i))
		{
			free(ligne);
			ligne = NULL;
			ligne = get_next_line(fd);
		}
		else
			return (printf("error extract\n"), free(ligne), clear_map(cpy, i), ft_errno(), 0);
		read_map(cpy[i]);
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
