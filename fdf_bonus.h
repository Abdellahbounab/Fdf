/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:26:31 by abounab           #+#    #+#             */
/*   Updated: 2024/04/18 17:41:18 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <mlx.h>
# include <math.h>
# include "get_next_line.h"

typedef struct s_details{
	double	x;
	double	y;
	int		z;
	int		color;
	int		length;
}	t_details;

typedef struct s_image{
	void	*img;
	char	*addr;
	int		bit_px;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_hook{
	double	z_rotation;
	double	x_rotation;
	double	y_rotation;

	double	horizone;
	double	vertical;

	int		projection;
	int		coloring;

	double	zoom;

	int		parallel;
}	t_hook;

typedef struct s_mlx_data{
	void		*mlx_ptr;
	void		*mlx_window;
	int			x_map;
	int			y_map;

	double		scale_x;
	double		scale_y;

	int			x_min;
	int			y_min;

	int			width_dimension;
	int			height_dimension;

	t_image		image;

	t_details	***mlx_map;
	t_details	***map_cpy;

	t_hook		events;
}	t_mlx_data;

# define UP 126

# define DOWN 125

# define RIGHT 124

# define LEFT 123

# define Z_BTN 6

# define X_BTN 7

# define Y_BTN 16

# define ZOOM_IN 35

# define ZOOM_OUT 46

# define BTN_0 82

# define COLORING 51

# define EXTRA 49

# define ESC 53

void		dda(t_mlx_data data, t_details p1, t_details p2);

int			esc_button(t_mlx_data *mlx);

int			calculate_dimension(t_mlx_data *mlx);

int			get_key(int key, t_mlx_data *mlx);

int			ft_strncmp(char *str, char *cmp, int len);

int			ft_strchr(char *str, unsigned char c);

int			get_value(char *str);

int			exit_program(t_mlx_data *mlx);

void		clear_map(t_details ***map, int len);

void		free_axis(t_details ***map, int len);

void		free_arr(char **arr, int len);

int			ft_errno(char *str, int sign);

int			exit_program(t_mlx_data *mlx);

t_details	**extract_axis(char **ligne, int min_width, int y, int max_y);

t_details	***get_mlx_cpy(t_mlx_data *mlx);

void		create_image(t_mlx_data *mlx);

int			rotation_matrices(t_mlx_data *mlx);

int			increase(t_details **data, int zoom);

int			words_count(char *str, char *charset);

char		*ft_strdups(char **str, int len);

char		**ft_split_space(char *str, char *charset, int *len);

int			add_events(t_hook *events);

int			mlx_instruction_put(t_mlx_data mlx);

int			extra_coloring(t_mlx_data *mlx);

int			extra_2d_projection(t_mlx_data *mlx);

#endif