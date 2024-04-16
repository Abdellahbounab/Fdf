/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:19:24 by abounab           #+#    #+#             */
/*   Updated: 2024/04/15 22:25:12 by abounab          ###   ########.fr       */
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
		axis->z = plus;
		axis->color = 0xFFFFFF;
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
			axis->z *= get_value(arr[0]);
			if (len > 1)
				axis->color = get_value(arr[1]);
			return (free_arr(arr, len), axis);
		}
		return (free_arr(arr, len), NULL);
	}
	return (free_arr(arr, len), NULL);
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

int	put_color(int color1, int color2, int steps, int px)
{
	double	colors[3];
	
	colors[0] = ((((color2 >> 16) & 0xFF) - ((color1 >> 16) & 0xFF))) /  (double) steps;
	colors[1] = ((((color2 >> 8) & 0xFF) - ((color1 >> 8) & 0xFF)) / (double) steps);
	colors[2] = ((((color2) & 0xFF) - ((color1) & 0xFF)) / (double) steps);

	colors[0] = ((color1 >> 16) & 0xFF) + (int)round(px * (colors[0]));
	colors[1] = ((color1 >> 8) & 0xFF) + (int)round(px * colors[1]);
	colors[2] = ((color1) & 0xFF) + (int)round(px * colors[2]);
	

	return ((int)colors[0] << 16 | (int)colors[1] << 8 | (int)colors[2]);
}


void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->image.addr + (y * data->image.line_length + x * (data->image.bits_per_pixel / 8)); 
	*(unsigned int*)dst = color;
}

int draw_line_dda(t_mlx_data data, t_details p1, t_details p2)
{
	t_details	printable;
	double 		steps;
	

	p1.x *= data.scale_x;
	p1.x += (data.x_min * data.scale_x) + 50;
	p1.y *= data.scale_y;
	p1.y += (data.y_min * data.scale_y) + 100;
	
	p2.x *= data.scale_x;
	p2.x += (data.x_min * data.scale_x) + 50;
	p2.y *= data.scale_y;
	p2.y += (data.y_min * data.scale_y) + 100;
	
 	printable.y = fabs(p2.y - p1.y);
	printable.x = fabs(p2.x - p1.x);
	steps = sqrt(pow(printable.y, 2) + pow(printable.x, 2));
	printable.x /= steps;
	printable.x *= p1.x < p2.x ? 1 : -1;
	printable.y /= steps;
	printable.y *= p1.y < p2.y ? 1 : -1;
	
	int cpy_steps = steps;
	int anc_color = p1.color;

	while (cpy_steps-- >= 0)
	{
		if (p1.x < data.width_dimension && p1.y < data.height_dimension)
			my_mlx_pixel_put(&data, p1.x, p1.y, p1.color);
		p1.color = put_color(anc_color, p2.color, steps, steps - cpy_steps);
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


//this function have to be handlede for errors
t_details	***get_mlx_cpy(t_mlx_data *mlx)
{
	t_details	***cpy;
	int	i;
	int	j;

	cpy = (t_details ***) malloc (sizeof(t_details **) * mlx->y_map);
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < mlx->y_map)
	{
		j = 0;
		cpy[i] = (t_details **) malloc (sizeof(t_details *) * mlx->x_map);
		while (j < mlx->x_map)
		{
			cpy[i][j] = create_data(i + mlx->events.vertical, j + mlx->events.horizone, mlx->x_map, mlx->y_map);
			cpy[i][j]->z = mlx->mlx_map[i][j]->z;
			cpy[i][j]->color = mlx->mlx_map[i][j]->color;
			j++;
		}
		i++;
	}
	return (cpy);

}

int	rotation_matrices(t_mlx_data *mlx)
{
	int i;
	int j;

	i = 0;
	mlx->mlx_map_cpy = get_mlx_cpy(mlx);
	while (i < mlx->y_map)
	{
		j = 0;
		while (j < mlx->x_map)
		{
			// rotate_by_z(&mlx->mlx_map[i][j], -(M_PI_4));
			rotate_by_z(&mlx->mlx_map_cpy[i][j], mlx->events.z_rotation);
			// rotate_by_x(&mlx->mlx_map_cpy[i][j], atan(sqrt(2)));
			rotate_by_x(&mlx->mlx_map_cpy[i][j], mlx->events.x_rotation);
			if (mlx->events.y_rotation)
				rotate_by_y(&mlx->mlx_map_cpy[i][j], mlx->events.y_rotation);
			j++;
		}
		i++;
	}
	return (1);
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


int	create_image(t_mlx_data *mlx)
{
	int i;
	int j;
	
	i = 0;
	mlx->image.img = mlx_new_image(mlx->mlx_ptr, mlx->width_dimension, mlx->height_dimension);
	mlx->image.addr = mlx_get_data_addr(mlx->image.img, &mlx->image.bits_per_pixel, &mlx->image.line_length, &mlx->image.endian);
	while(i < mlx->y_map)
    {
        j = 0;
        while(j < mlx->x_map)
        {
            if(j + 1 < mlx->x_map)
                draw_line_dda(*mlx, *mlx->mlx_map_cpy[i][j], *mlx->mlx_map_cpy[i][j + 1]);
            if(i + 1 < mlx->y_map)
				draw_line_dda(*mlx, *mlx->mlx_map_cpy[i][j], *mlx->mlx_map_cpy[i + 1][j]);
			j++;
        }
		i++;
    }
	free_axis(mlx->mlx_map_cpy, i);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, mlx->image.img, 0, 0);
	return (1);
}

int	get_key(int key, t_mlx_data *mlx)
{
	// x11 keycode / x11.keysyms
	mlx_destroy_image(mlx->mlx_ptr, mlx->image.img);
	
	//ihave to hold all the keys and then update the values of mlx->events(positions) depending on each key hook
	// ihave to look after the keywords macros to get them right
	if (key == XK_Up || key == XK_Down || key == XK_Right || key == XK_Left)
	{
		if (key == XK_Up)
			mlx->events.vertical--;
		if (key == XK_Down)
			mlx->events.vertical++;
		if (key == XK_Right)
			mlx->events.horizone++;
		if (key == XK_Left)
			mlx->events.horizone--;
		rotation_matrices(mlx);
		create_image(mlx);
	}
	else if (key == XK_z || key == XK_x || key == XK_y)
	{
		if (key == XK_z)
			mlx->events.z_rotation -= 0.05;
		if (key == XK_x)
			mlx->events.x_rotation += 0.5;
		if (key == XK_y)
			mlx->events.y_rotation += 0.5;
		rotation_matrices(mlx);
		create_image(mlx);
	}
	else
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_window);
		free_axis(mlx->mlx_map, mlx->y_map);
		exit(0);
	}
	printf("key pressed : %d\n", key);
	return (1);
}

int calculate_dimension(t_mlx_data *mlx)
{
	rotation_matrices(mlx);
	mlx->width_dimension = return_x(mlx->mlx_map_cpy, mlx->x_map, mlx->y_map, &mlx->x_min);
	mlx->height_dimension = return_y(mlx->mlx_map_cpy, mlx->x_map, mlx->y_map, &mlx->y_min);
	
	mlx->scale_x = (double)1000 / mlx->width_dimension ;
	mlx->scale_y = (double)1000 / mlx->height_dimension ;

	if (mlx->scale_x > 1)
		mlx->scale_x = (double)500 / mlx->width_dimension ;
	if (mlx->scale_y > 5)
		mlx->scale_y = (double)500 / mlx->height_dimension ;

	mlx->width_dimension *= mlx->scale_x;
	mlx->width_dimension += 100;
	mlx->height_dimension *= mlx->scale_y;
	mlx->scale_y /= 1.5;
	return (1);
}

int	add_events(t_hook *events)
{
	events->z_rotation = -(M_PI_4);
	events->y_rotation = 0;
	events->x_rotation = atan(sqrt(2));
	events->horizone = 0;
	events->vertical = 0;
	events->zoom_in = 0;
	events->zoom_out = 0;
	return (1);
}

int create_mlx(t_mlx_data mlx, t_details ***map, char *title)
{
	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		ft_errno();
	mlx.mlx_map = map;
	add_events(&mlx.events);

	calculate_dimension(&mlx);

	mlx.mlx_window = mlx_new_window(mlx.mlx_ptr, mlx.width_dimension, mlx.height_dimension, title);
	
	create_image(&mlx);

	mlx_key_hook(mlx.mlx_window, get_key, &mlx);
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
	
	if (argc == 2)
	{
		if (valid_file(argv[1], ".fdf", ft_strlen(argv[1])))
		{
			map = valid_axis(argv[1], &mlx.x_map, &mlx.y_map);
			if (map)
				create_mlx(mlx, map, argv[1]);
				// draw_map(mlx, map, argv[1]);
		}
		else
			printf("Error : file error\n");//edit the ft_errno to excute the error
	}



	//adding valgrind to my linux ! to rememeber


	// knowledge : https://github.com/VBrazhnik/FdF/wiki


	//about map :
			//min width must be in first line
			//only digits can make the highness or will get z'0
			//colors can take hexa or decimal
			//if planning for bonus must add opacity

}