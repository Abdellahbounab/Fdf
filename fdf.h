/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:43:35 by abounab           #+#    #+#             */
/*   Updated: 2024/04/16 15:30:47 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdio.h>
#include <mlx.h>
#include <math.h>
// #include <X11/keysym.h>
#include "get_next_line.h"

typedef struct s_details{
	double	x;
	double	y;
	int	z;
	int	color;
	int length;
}	t_details;

typedef struct s_image{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_image;

typedef struct s_hook{
	double	z_rotation;
	double	x_rotation;
	double	y_rotation;

	double	horizone;
	double	vertical;

	int		projection;

	double	zoom;

	int		parallel;
	int		conic;
}	t_hook;

typedef struct s_mlx_data{
	void *mlx_ptr;
	void *mlx_window;

	int	x_map;
	int	y_map;

	double scale_x;
	double scale_y;

	int x_min;
	int y_min;

	int width_dimension;
	int height_dimension;

	t_image	image;

	t_details ***mlx_map;
	t_details ***mlx_map_cpy;

	t_hook	events;
} t_mlx_data;

#ifndef XK_Up
#define XK_Up 126
#endif

#ifndef XK_Down
#define XK_Down 125
#endif

#ifndef XK_Right
#define XK_Right 124
#endif

#ifndef XK_Left
#define XK_Left 123
#endif

#ifndef XK_z
#define XK_z 6
#endif

#ifndef XK_x
#define XK_x 7
#endif

#ifndef XK_y
#define XK_y 16
#endif

#ifndef XK_p
#define XK_p 46
#endif


#ifndef XK_m
#define XK_m 35
#endif

#ifndef XK_0
#define XK_0 82
#endif

#ifndef XK_1
#define XK_1 83
#endif

#ifndef XK_space
#define XK_space 49
#endif

int	valid_file(char *name, char *fdf, int len);

void	free_arr(char **arr, int len);
void 	free_axis(t_details ***map, int len);
void clear_map(t_details ***map, int len);


void ft_errno(void);

int	ft_strncmp(char *str, char *cmp, int len);

int	ft_strchr(char *str, unsigned char c);

int	ft_atox(char *str);

int	ft_atoi(char *str);

int	get_value(char *str);

t_details *get_data(char *str, int x_val, int y_val, int len, int y_max);

int	words_count(char *str, char *charset);

char	*ft_strdups(char **str, int len);

char	**ft_split_space(char *str, char *charset, int *len);

t_details **extract_axis(char *ligne, int min_width, int x, int y_max);

t_details	***valid_axis(char *file, int *x_map, int *y_map);


#endif