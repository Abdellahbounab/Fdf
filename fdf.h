/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:43:35 by abounab           #+#    #+#             */
/*   Updated: 2024/03/13 17:55:03 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdio.h>
#include <mlx.h>
#include "get_next_line.h"

typedef struct s_details{
	int	x;
	int	y;
	int	z;
	int	color;
	int opacity;
	int length;
}	t_details;

typedef struct s_mlx_data{
	void *mlx_ptr;
	void *mlx_window;
	int	x_map;
	int	y_map;
} t_mlx_data;

int	valid_file(char *name, char *fdf, int len);

void	free_arr(char **arr, int len);
void free_axis(t_details ***map, int len);
void clear_map(t_details ***map, int len);


void ft_errno(void);

int	ft_strncmp(char *str, char *cmp, int len);

int	ft_strchr(char *str, unsigned char c);

int	ft_atox(char *str);

int	ft_atoi(char *str);

int	get_value(char *str);

t_details *get_data(char *str, int x_val, int y_val, int len);

int	words_count(char *str, char *charset);

char	*ft_strdups(char **str, int len);

char	**ft_split_space(char *str, char *charset, int *len);

t_details **extract_axis(char *ligne, int min_width, int x);

t_details	***valid_axis(char *file, int *x_map, int *y_map);


#endif