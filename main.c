/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:19:24 by abounab           #+#    #+#             */
/*   Updated: 2024/04/08 20:34:29 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_map(t_details **map)
{
	int i = 0;
	int len = 0;
	
	if (map[0])
		len = map[0]->length;
	while (i < len)
	{
		printf("(%d, %.2f, %.2f)", map[i]->z, map[i]->x, map[i]->y);
		i++;
	}
	printf("\n");
}

void	ft_errno(void)
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
	while (str[i] && i < len)
	{
		if (str[i] != cmp[i])
			return (0);
		i++;
	}
	if (i == len || !(str[i] - cmp[i]))
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

int	ft_atox(char *str)
{
	int	num;
	int	val;
	int i;

	num = 0;
	i = 2;
	while (str && str[i] && i < 8)
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			val = ft_strchr("0123456789ABCDEF" ,str[i]);
		else
			val = ft_strchr("0123456789abcdef", str[i]);
		if (val != -1)
		{
			num *= 16;
			num += val;
		}
		else
			break;
		i++;
	}
	if (i < 8 || (i == 8 && str[i]))
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
	while (str && str[i] && ft_strchr("0123456789", str[i]) != -1)
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	if (str && str[i])
		num = 0;
	return (num * sign);
}

int	  get_value(char *str) //have to implements the hexa part
{
	int num;

	num = 0;
	if (ft_strncmp(str, "0x", 2))
		num = ft_atox(str);
	else
		num = ft_atoi(str);
	return (num);
}

t_details *create_data(int y_val, int x_val, int arr_len)
{
	t_details *axis;

	axis = (t_details *) malloc (sizeof(t_details));
	if (axis)
	{
		axis->y = y_val * 10;
		axis->x = x_val * 10;
		axis->z = 0; //get value would get the number in hexa or decimal (if error assign to 0, (white color is a default color))
		axis->color = 0xFFFFFF; //default color (white)
		axis->opacity = 100;
		axis->length = arr_len;
	}
	return (axis);
}

t_details *get_data(char *str, int y_val, int x_val, int arr_len)
{
	t_details *axis;
	char **arr;
	int	len;

	len = 0;
	arr = ft_split_space(str, " ,", &len);
	if (arr && len)
	{
		axis = create_data(y_val, x_val, arr_len);
		if (axis)
		{
			axis->z = get_value(arr[0]);
			if (len > 1)
				axis->color = get_value(arr[1]);
			if (len > 2)
				axis->opacity = get_value(arr[2]);
			return (axis);
		}
		return (NULL);
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

int	word_len(char *str, char *charset)
{
	int	len;

	len = 0;
	while (*str && ft_strchr(charset, *str) != -1)
		str++;
	while (*str && ft_strchr(charset, *str) == -1)
	{
		str++;
		len++;
	}
	return (len);
}

char	*ft_strdups(char **str, int len)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = (char *) malloc (sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	while (*str && i < len)
	{
		*(cpy + i) = *(*str)++;
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
				*(arr + i) = ft_strdups(&str, word_len(str, charset));
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
	t_details **cpy;

	i = 0;
	cpy = *map;
	while (cpy && i < len)
	{
		free(cpy[i]);
		cpy[i] = NULL;
		i++;
	}
	free(cpy);
}

t_details **extract_axis(char *ligne, int min_width, int y)
{
	char **arr;
	int	x;
	int len;
	t_details **cpy;

	x = 0;
	len = 0;
	arr = ft_split_space(ligne, " \t\n",&len);
	if (len >= min_width)
	{
		cpy = (t_details **) malloc (sizeof(t_details *) * len);
		if (!cpy)
			return (free_arr(arr, len), NULL);
		while (x < len)
		{
			cpy[x] = get_data(arr[x], y, x, len);
			if (!cpy[x])
				return (free_arr(arr, len), free_axis(&cpy, len), NULL);
			x++;
		}
		// read_map(cpy);
		return (free_arr(arr, len), cpy);
	}
	return (free_arr(arr, len), NULL);
}

void clear_map(t_details ***map, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free_axis(map + i, (*map[i])->length);
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
			free(str);
			str = NULL;
			str = get_next_line(fd);
		}
	}
	close(fd);
	return (len);
}

t_details	***valid_axis(char *file, int *x_map, int *y_map)
{
	int		fd;
	int		min_width;
	char	*ligne;
	int		i;
	t_details ***cpy;

	i = 0;
	cpy = (t_details ***) malloc (sizeof(t_details **) * count_lignes(file));
	if (!cpy)
		return (NULL);
	fd = open(file, O_RDONLY);
	ligne = get_next_line(fd);
	min_width = words_count(ligne, " \t");
	while (ligne && *ligne)
	{
		cpy[i] = extract_axis(ligne, min_width, i);
		if (!(*(cpy + i)))
			return (free(ligne), clear_map(cpy, i - 1), ft_errno(), NULL);
		free(ligne);
		ligne = get_next_line(fd);
		i++;
	}
	if (!min_width)
		return (free(ligne), ft_errno(), NULL);
	return (*y_map = i, *x_map = min_width, cpy);
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

// void    draw_line_bresenham(t_mlx_data mlx, t_details p1, t_details p2)
// {
// 	//find the slope |m| = (Delta_y)|y2 - y1| / (Delta_x)|x2 - x1|
// 	// for DDA : if (|m| <= 1) then {if (left->right) x += 1 and y += m / if (right -> left) x -= 1 and y -= m}
// 	        // : if (|m| > 1 && m > 0) then {if (left -> right) y += 1 and x += 1/m / if (right -> left) y -= 1 and x -= 1/m}
// 			// : if (|m| > 1 && m < 0) then {if (left -> right) y -= 1 and x -= 1/m / if (right -> left) y += 1 and x += 1/m}
//     int    m;
// 	int sign;
//     t_details	delta;
// 	t_details	position;

// 	int plus = 40;

// 	// isometric(&p1, &p2);

//     position.x = p1.x * 40;
//     position.y = p1.y * 40;
// 	delta.x = fabs(p2.x - p1.x);
// 	delta.y = fabs(p2.y - p1.y);
// 	m = delta.y / delta.x;

// 	sign = 1;
// 	if (p2.x > p1.x)
// 		sign = -1;
	
//     while(position.x <= p2.x)
//     {
//         if(abs(m) <= 1)
// 		{
// 			position.x += (1 * sign);
// 			position.y += (m * sign);
// 		}
//         else if (m > 0)
// 		{
// 			position.y += (1 * sign);
// 			position.x += (sign * 1 / m);
// 		}
// 		else
// 		{
// 			position.y -= (1 * sign);
// 			position.x -= (sign * 1 / m);
// 		}
// 		printf("position of x = %f/ position of y = %f\n", position.x, position.y);
//             mlx_pixel_put(mlx.mlx_ptr, mlx.mlx_window, position.x, position.y, p1.color);
//     }
// }

int draw_line_dda(t_mlx_data data, t_details p1, t_details p2)
{
	t_details printable;
	int steps;

	p1.x += 20;
	p1.y += 20;
	p2.x += 20;
	p2.y += 20;
 	printable.y = fabs(p2.y - p1.y);
	printable.x = fabs(p2.x - p1.x);
	steps = sqrt((printable.y * printable.y) + (printable.x * printable.x));
	printable.x /= steps;
 	printable.y /= steps;
	while (steps--)
	{
		mlx_pixel_put(data.mlx_ptr, data.mlx_window, p1.x, p1.y, p1.color);
		p1.x += printable.x;
		p1.y += printable.y;
	}
	return (1);
}

t_details  *isometric(t_details point)
{
	t_details *cpy;

	cpy = create_data((point.x + point.y) * sin(0.523599) - point.z, (point.x - point.y) * cos(0.523599), point.length);
	cpy->color = point.color;
	if (!cpy)
		return (NULL);
	return (cpy);
}

int	main(int argc, char **argv)
{
	t_details	***map;
	t_mlx_data mlx;


	map = NULL;
	// starting point :
			// 1 - validate .fdf file from argv[1]   VALIDE
			// 2 - check map : get all lines length as the first one	VALIDE
			// 3 - get details from the map (matrices of [x(width)][y(length)]) and getting the axis z	VALDIE
			// 3 - handle the hexa or decimal colors in each point	VALIDE
			// 4 - draw the points inside the mlx while connecting every point with its (x - 1) (x + 1) (y + 1) (y - 1)
			// 5 - rending colors with every points
	
	if (argc == 2)
	{
		if (valid_file(argv[1], ".fdf", ft_strlen(argv[1]))) // check file if end with .fdf , if exist, if permissions
		{
	// 		// check if map have the same width length as the first line or higher : if less == error
			map = valid_axis(argv[1], &mlx.x_map, &mlx.y_map);
			if (map) // check if map is only digits && colors hexa or decimial && insert the data required depends on its x, y, z
			{
				printf("map achieved :\n");
			}
		}
		else
			printf("error : file error\n");
	}

	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		ft_errno();
		//here where i got width and length of data map and i have to update it before assign it to the widnow
	mlx.mlx_window = mlx_new_window(mlx.mlx_ptr, 1500, 1000, "FDF");
	// square
	// draw_line(mlx, 50, 50, 200, 50, 0xFF00FF);
	// draw_line(mlx, 50, 200, 200, 200, 0x00FFFF);
	// draw_line(mlx, 50, 50, 50, 200, 0xFFFF00);
	// draw_line(mlx, 200, 50, 200, 200, 0xF0FF0F);
	// triangle


	


	t_details *tmp;
	t_details *tmp_y;
	t_details *tmp_x;
	// while (i + 1 < mlx.y_map)
	// 	read_map(map[i++]);

	int i;
	int j;

	i = 0;
	while(i < mlx.y_map)
    {
        j = 0;
        while(j < mlx.x_map)
        {
			tmp = isometric(*map[i][j]);
            // tmp = map[i][j];
            if(i + 1 < mlx.y_map)
			{
            	// tmp_y = isometric(map[i + 1][j]);
            	tmp_y = map[i + 1][j];
                draw_line_dda(mlx, *tmp, *tmp_y);
                // draw_line_dda(mlx, *map[i][j], *map[i + 1][j]);
			}
            if(j + 1 < mlx.x_map)
			{
            	// tmp_x = isometric(map[i][j + 1]);
            	tmp_x = map[i][j + 1];
                draw_line_dda(mlx, *tmp, *tmp_x);
			}
			free(tmp);
			tmp = NULL;
			// free(tmp_x);
			// tmp_x = NULL;
			// free(tmp_y);
			// tmp_y = NULL;
			j++;
        }
		printf("\n");
        i++;
    }

	// draw_line(mlx, 250, 0, 500, 500, 0x00FF00);

	mlx_loop(mlx.mlx_ptr);
	mlx_destroy_window(mlx.mlx_ptr, mlx.mlx_window);
	free(mlx.mlx_ptr);
	free(mlx.mlx_window);
	
	//adding valgrind to my linux ! to rememeber

	// knowledge : https://github.com/VBrazhnik/FdF/wiki


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
