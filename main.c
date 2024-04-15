/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:19:24 by abounab           #+#    #+#             */
/*   Updated: 2024/04/14 22:56:52 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// https://github.com/ailopez-o/42Barcelona-FdF

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
	if (( i < 8 || i == 8) && str[i])
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

t_details *create_data(int y_val, int x_val, int arr_len, int max_y)
{
	t_details *axis;
	int plus;

	axis = (t_details *) malloc (sizeof(t_details));
	plus = 100 / max_y;
	if (max_y > 100)
		plus = max_y / 10;
	if (axis)
	{
		axis->y = y_val * plus;
		axis->x = x_val * plus;
		axis->z = 0; //get value would get the number in hexa or decimal (if error assign to 0, (white color is a default color))
		axis->color = 0xFFFFFF; //default color (white)
		axis->opacity = 100;
		axis->length = arr_len;
	}
	return (axis);
}

t_details *get_data(char *str, int y_val, int x_val, int arr_len, int max_y)
{
	t_details *axis;
	char **arr;
	int	len;

	len = 0;
	arr = ft_split_space(str, " ,", &len);
	if (arr && len)
	{
		axis = create_data(y_val, x_val, arr_len, max_y);
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

t_details **extract_axis(char *ligne, int min_width, int y, int max_y)
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
			cpy[x] = get_data(arr[x], y, x, len, max_y);
			if (!cpy[x])
				return (free_arr(arr, len), free_axis(&cpy, len), NULL);
			x++;
		}
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

int count_lignes(char *file, int *y_map)
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
	return (*y_map = len, len);
}

t_details	***valid_axis(char *file, int *x_map, int *y_map)
{
	int		fd;
	int		min_width;
	char	*ligne;
	int		i;
	t_details ***cpy;

	i = 0;
	cpy = (t_details ***) malloc (sizeof(t_details **) * count_lignes(file, y_map));
	if (!cpy)
		return (NULL);
	fd = open(file, O_RDONLY);
	ligne = get_next_line(fd);
	min_width = words_count(ligne, " \t\n");
	while (ligne && *ligne)
	{
		cpy[i] = extract_axis(ligne, min_width, i, *y_map);
		if (!cpy[i])
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

// void	bershnam_draw2(t_mlx_data mlx, double x0, double y0, double x1, double y1, int color)
// {
// 	double dx = fabs(y1 - y0);
// 	double dy = -fabs(x1 - x0);
// 	int sx = x0 < x1 ? 1 : -1;
// 	int sy = y0 < y1 ? 1 : -1;
// 	double err = dx + dy;
// 	double er2;
	
// 	while ((int)(x0 - x1) && (int)(y0 - y1))
// 	{
// 		mlx_pixel_put(mlx.mlx_ptr, mlx.mlx_window, x0, y0, color);
// 		er2 = 2 * err;
// 		if (er2 >= dy)
// 		{
// 			err += dy;
// 			x0 += sx;
// 		}
// 		if (er2 <= dx)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }

// void    draw_line_bresenham(t_mlx_data mlx, double x0, double y0, double x1, double y1, int color)
// {
// 	float	dxy[4];
// 	int		fraction;
// 	t_details	dup;

// 	int plus = 100;

// 	x0 += plus;
// 	y0 += plus;
// 	x1 += plus;
// 	y1 += plus;

// 	dxy[0] = fabs(x1 - x0);
// 	dxy[1] = fabs(y1 - y0);
// 	dxy[2] = x0 < x1 ? 1 : -1;
// 	dxy[3] = y0 < y1 ? 1 : -1;
// 	fraction = dxy[0] - dxy[1];
// 	dup.x = x0;
// 	dup.y = y0;
// 	dup.color = color;
// 	// the while need to stop at the point where it is achieved , and that would be in all case
// 	// while (steps-- && dup.x != x1)
// 	while (dup.x != x1 && dup.y != y1)
// 	{
// 		// process_color(&dup, from, to, dxy);
// 		mlx_pixel_put(mlx.mlx_ptr, mlx.mlx_window, dup.x, dup.y, dup.color);
// 		if (fraction * 2 > -dxy[1])
// 		{
// 			fraction -= dxy[1];
// 			dup.x += dxy[2];
// 		}
// 		else if (fraction * 2 < dxy[0])
// 		{
// 			fraction += dxy[0];
// 			dup.y += dxy[3];
// 		}
// 	}

// }
// void	slope_bigger_than_one(t_mlx_data mlx, double dx, double dy, double x0, double y0, int color)
// {
// 	int p;
// 	int i;

// 	i = 0;
// 	p = 2 * dx - dy;
// 	mlx_pixel_put(mlx.mlx_ptr, mlx.mlx_window, x0, y0, color);
// 	while (i < dy)
// 	{
// 		y0 += 1;
// 		if (p < 0)
// 			p += 2 * dx;
// 		else
// 		{
// 			x0 += 1;
// 			p += 2 * dx - dy;
// 		}
// 		mlx_pixel_put(mlx.mlx_ptr, mlx.mlx_window, x0, y0, color);
// 		i++;
// 	}
// }



// void	slope_less_than_one(t_mlx_data mlx, double dx, double dy, double x0, double y0, int color)
// {
// 	int p;
// 	int i;

// 	i = 0;
// 	p = 2 * dy - dx;
// 	mlx_pixel_put(mlx.mlx_ptr, mlx.mlx_window, x0, y0, color);
// 	while (i < dx)
// 	{
// 		x0 += 1;
// 		if (p < 0)
// 			p += 2 * dy;
// 		else
// 		{
// 			y0 += 1;
// 			p += 2 * dy - 2 * dx;
// 		}
// 		mlx_pixel_put(mlx.mlx_ptr, mlx.mlx_window, x0, y0, color);
// 		i++;
// 	}
// }

// void    berseham_draw(t_mlx_data mlx, double x0, double y0, double x1, double y1, int color)
// {
// 	float	dxy[4];
// 	int plus = 100;

// 	x0 += plus;
// 	y0 += plus;
// 	x1 += plus;
// 	y1 += plus;
//  	dxy[0] = fabs(x1 - x0);
// 	dxy[1] = fabs(y1 - y0);
// 	if ((double)(dxy[1] / dxy[0]) < 1)
// 		slope_less_than_one(mlx, dxy[0], dxy[1], x0, y0, color);
// 	else
// 		slope_bigger_than_one(mlx, dxy[0], dxy[1], x0, y0, color);
// }


void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	printf("addr:%s\n", data->addr);
	dst = data->addr + (y * data->x_map + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int draw_line_dda(t_mlx_data data, t_details p1, t_details p2, t_mlx_data map_dimension)
{
	t_details	printable;
	double 		steps;
	double		coloring;
	

	p1.x *= map_dimension.scale_x;
	p1.x += (map_dimension.x_min * map_dimension.scale_x) + 50;
	p1.y *= map_dimension.scale_y;
	p1.y += (map_dimension.y_min * map_dimension.scale_y) + 100;
	
	p2.x *= map_dimension.scale_x;
	p2.x += (map_dimension.x_min * map_dimension.scale_x) + 50;
	p2.y *= map_dimension.scale_y;
	p2.y += (map_dimension.y_min * map_dimension.scale_y) + 100;
	
 	printable.y = fabs(p2.y - p1.y);
	printable.x = fabs(p2.x - p1.x);
	steps = sqrt(pow(printable.y, 2) + pow(printable.x, 2));
	printable.x /= steps;
	printable.x *= p1.x < p2.x ? 1 : -1;
	printable.y /= steps;
	printable.y *= p1.y < p2.y ? 1 : -1;
	
	// color is more of red100%0%----50%+50%----0%100%black and not this
	coloring =  abs(p1.color - p2.color) / steps;
	coloring *= p1.color < p2.color ? 1 : -1;
	while (steps-- >= 0)
	{
		mlx_pixel_put(data.mlx_ptr, data.mlx_window, p1.x, p1.y, p1.color);
		// my_mlx_pixel_put(&data, p1.x, p1.y, p1.color);
		p1.color += (int)coloring;
		if (p1.x != p2.x)
			p1.x += printable.x;
		if (p1.y != p2.y)
			p1.y += printable.y;
	}
	return (1);
}

void rotate_by_z(t_details **map, double raduis)
{
	int cpy_x;	
	int cpy_y;	
	int cpy_z;
	
	cpy_x = (*map)->x;
	cpy_y = (*map)->y;
	cpy_z = (*map)->z;
		
	(*map)->x = cos(raduis) * cpy_x + -sin(raduis) * cpy_y + 0 * cpy_z;
	(*map)->y = sin(raduis) * cpy_x + cos(raduis) * cpy_y + 0 * cpy_z;
	(*map)->z = 0 * cpy_z + 0 * cpy_y + 1 * cpy_z;
}

void rotate_by_x(t_details **map, double raduis)
{
	int cpy_x;	
	int cpy_y;	
	int cpy_z;
	
	cpy_x = (*map)->x;
	cpy_y = (*map)->y;
	cpy_z = (*map)->z;
		
	(*map)->x = 1 * cpy_x + 0 * cpy_y + 0 * cpy_z;
	(*map)->y = 0 * cpy_x + cos(raduis) * cpy_y + -sin(raduis) * cpy_z;
	(*map)->z = 0 * cpy_z + sin(raduis) * cpy_y + cos(raduis) * cpy_z;
}

void rotate_by_y(t_details **map, double raduis)
{
	int cpy_x;	
	int cpy_y;	
	int cpy_z;
	
	cpy_x = (*map)->x;
	cpy_y = (*map)->y;
	cpy_z = (*map)->z;
		
	(*map)->x = cos(raduis) * cpy_x + 0 * cpy_y + sin(raduis) * cpy_z;
	(*map)->y = 0 * cpy_x + 1 * cpy_y + 0 * cpy_z;
	(*map)->z = -sin(raduis) * cpy_z + 0 * cpy_y + cos(raduis) * cpy_z;
}


double ft_raduis(double angle)
{
	return (angle * (3.14159265358979 / 180));
}

void	rotation_matrices(t_details ***map, int width, int length, double raduis)
{
	int i;
	int j;

	i = 0;
	raduis++;//this one have to be removeed
	while (i < length)
	{
		j = 0;
		while (j < width)
		{
			rotate_by_z(&map[i][j], M_PI_4);
			rotate_by_x(&map[i][j], atan(sqrt(2)));
			// rotate_by_y(&map[i][j], 0);
			j++;
		}
		i++;
	}
}

void	isometric(t_details ***map, int width, int length, double raduis)
{
	int i;
	int j;
	double tmp;

	i = 0;
	while (i < length)
	{
		j = 0;
		while (j < width)
		{
			tmp = map[i][j]->x;
			map[i][j]->x = (tmp - map[i][j]->y) * cos(raduis);
			map[i][j]->y = (tmp + map[i][j]->y) * sin(raduis) - map[i][j]->z;
			j++;
		}
		i++;
	}
}


int	return_y(t_details ***map, int x_width, int y_width, int *y_min)
{
	int	i;
	int	j;
	int min;
	int max;

	i = 0;
	min = map[i][i]->y;
	max = map[i][i]->y;
	while (i < y_width)
	{
		j = 0;
		while (j < x_width)
		{
			if (min > map[i][j]->y)
				min = map[i][j]->y;
			if (max < map[i][j]->y)
				max = map[i][j]->y;
			j++;
		}
		i++;
	}
	*y_min = abs(min);
	return (abs(max - min));
}

int return_x(t_details ***map, int x_width, int y_width, int *x_min)
{
	int	i;
	int	j;
	int min;
	int max;

	i = 0;
	min = map[i][i]->x;
	max = map[i][i]->x;
	while (i < y_width)
	{
		j = 0;
		while (j < x_width)
		{
			if (min > map[i][j]->x)
				min = map[i][j]->x;
			if (max < map[i][j]->x)
				max = map[i][j]->x;
			j++;
		}
		i++;
	}
	*x_min = abs(min);
	return (abs(max - min));
}

t_mlx_data calculate_dimension(t_details ***map, int x_width, int y_height)
{
	t_mlx_data res;

	res.x_map = return_x(map, x_width, y_height, &res.x_min);
	res.y_map = return_y(map, x_width, y_height, &res.y_min);
	
	res.scale_x = (double)1000 / res.x_map ;
	res.scale_y = (double)1000 / res.y_map ;

	if (res.scale_y > 1)
		res.scale_y = (double)500 / res.y_map ;
	if (res.scale_x > 1)
		res.scale_x = (double)500 / res.x_map ;
	res.x_map *= res.scale_x;
	res.x_map += 100;
	res.y_map *= res.scale_y;
	// res.y_map *= 1;
	res.scale_y /= 2;

	// if (res.scale_x > 10 || res.scale_y > 10)
	// {
	// 	if (res.scale_x > 10)
	// 		res.x_map /= 2;
		
	// 	if (res.scale_y > 10)
	// 		res.y_map /= 2;
	// 	res.scale_x /= 2;
	// 	res.scale_y /= 2;
	// }
	return (res);
}


int draw_map(t_mlx_data mlx, t_details ***map, char *title)
{
	int i;
	int j;
	t_mlx_data map_dimension;
	
	i = 0;
	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		ft_errno();
	// isometric(map, mlx.x_map, mlx.y_map, ft_raduis(45));
	rotation_matrices(map, mlx.x_map, mlx.y_map, ft_raduis(45));
	map_dimension = calculate_dimension(map, mlx.x_map, mlx.y_map);
	mlx.mlx_window = mlx_new_window(mlx.mlx_ptr, map_dimension.x_map, map_dimension.y_map, title);
	// mlx.img = mlx_new_image(mlx.mlx_ptr, map_dimension.x_map, map_dimension.y_map);
	// mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.x_map,&mlx.endian);
	while(i < mlx.y_map)
    {
        j = 0;
        while(j < mlx.x_map)
        {
			// to draw a perfect map , it needs to  grading color
            if(j + 1 < mlx.x_map)
                draw_line_dda(mlx, *map[i][j], *map[i][j + 1], map_dimension);
            if(i + 1 < mlx.y_map)
				draw_line_dda(mlx, *map[i][j], *map[i + 1][j], map_dimension);
			j++;
        }
		i++;
    }
	// mlx_put_image_to_window(mlx.mlx_ptr, mlx.mlx_window, mlx.img, 0, 0);
	clear_map(map, mlx.y_map);
	mlx_loop(mlx.mlx_ptr);
	mlx_destroy_window(mlx.mlx_ptr, mlx.mlx_window);
	free(mlx.mlx_ptr);
	free(mlx.mlx_window);
	return (1);
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
			// 4 - draw the points inside the mlx while connecting every point with its (x - 1) (x + 1) (y + 1) (y - 1) VALID
			// 5 - rending colors with every points
	
	if (argc == 2)
	{
		if (valid_file(argv[1], ".fdf", ft_strlen(argv[1])))
		{
			map = valid_axis(argv[1], &mlx.x_map, &mlx.y_map);
			if (map)
			{
				printf("map achieved :\n");
				draw_map(mlx, map, argv[1]);
				clear_map(map, mlx.y_map);
			}
		}
		else
			printf("error : file error\n");
	}



	//adding valgrind to my linux ! to rememeber


	// knowledge : https://github.com/VBrazhnik/FdF/wiki


	//about map :
			//min width must be in first line
			//only digits can make the highness or will get z'0
			//colors can take hexa or decimal
			//if planning for bonus must add opacity

}