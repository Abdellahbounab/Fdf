/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:43:35 by abounab           #+#    #+#             */
/*   Updated: 2024/03/10 16:25:19 by abounab          ###   ########.fr       */
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
}	t_details;

int	valid_file(char *name, char *fdf, int len);

void	free_arr(char **arr, int len);
void free_axis(t_details ***map);
void clear_map(t_details ***map, int len);


void ft_errno(void);

int	ft_strncmp(char *str, char *cmp, int len);

int	ft_strchr(char *str, unsigned char c);

int	ft_atox(char *str ,int *i);

int	ft_atoi(char *str ,int *i);

int	get_value(char *str, int *i); //have to implements the hexa part

t_details *get_data(char *str, int x_val, int y_val);

int	words_count(char *str);

char	*ft_strdups(char *str, int len);

char	**ft_split_space(char *str, int *len);

int extract_axis(char *ligne, t_details ***map, int min_width, int x);

int   valid_axis(char *file, t_details ****map);


#endif