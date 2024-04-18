/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:32:02 by abounab           #+#    #+#             */
/*   Updated: 2024/04/18 16:32:20 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	put_color(int color1, int color2, int steps, int px)
{
	double	colors[3];

	colors[0] = (((((color2 >> 16) & 0xFF) - ((color1 >> 16) & 0xFF)))
			/ (double)steps);
	colors[1] = ((((color2 >> 8) & 0xFF) - ((color1 >> 8) & 0xFF))
			/ (double)steps);
	colors[2] = ((((color2) & 0xFF) - ((color1) & 0xFF)) / (double)steps);
	colors[0] = ((color1 >> 16) & 0xFF) + (int)round(px * (colors[0]));
	colors[1] = ((color1 >> 8) & 0xFF) + (int)round(px * colors[1]);
	colors[2] = ((color1) & 0xFF) + (int)round(px * colors[2]);
	return ((int)colors[0] << 16 | (int)colors[1] << 8 | (int)colors[2]);
}

static void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->image.addr + (y * data->image.line_length + x
			* (data->image.bit_px / 8));
	*(unsigned int *)dst = color;
}

static int	dda_add(t_mlx_data data, t_details *p1, t_details *p2)
{
	p1->x *= data.scale_x;
	if (data.events.projection)
		p1->x += (data.x_min * data.scale_x) + 50;
	p1->y *= data.scale_y;
	if (data.events.projection)
		p1->y += (data.y_min * data.scale_y) + 100;
	p2->x *= data.scale_x;
	if (data.events.projection)
		p2->x += (data.x_min * data.scale_x) + 50;
	p2->y *= data.scale_y;
	if (data.events.projection)
		p2->y += (data.y_min * data.scale_y) + 100;
	return (1);
}

static int	dda_details(t_details *printable, t_details p1,
	t_details p2, double *steps)
{
	printable->y = fabs(p2.y - p1.y);
	printable->x = fabs(p2.x - p1.x);
	*steps = sqrt(pow(printable->y, 2) + pow(printable->x, 2));
	printable->x /= *steps;
	if (p1.x >= p2.x)
		printable->x *= -1;
	printable->y /= *steps;
	if (p1.y >= p2.y)
		printable->y *= -1;
	return (1);
}

void	dda(t_mlx_data data, t_details p1, t_details p2)
{
	t_details	printable;
	double		steps;
	int			cpy_steps;
	int			anc_color;

	dda_add(data, &p1, &p2);
	dda_details(&printable, p1, p2, &steps);
	cpy_steps = steps;
	anc_color = p1.color;
	while (cpy_steps-- >= 0)
	{
		if (p1.x < data.width_dimension && p1.y < data.height_dimension
			&& p1.x > 0 && p1.y > 0)
			my_mlx_pixel_put(&data, p1.x, p1.y, p1.color);
		p1.color = put_color(anc_color, p2.color, steps, steps - cpy_steps);
		if (p1.x != p2.x)
			p1.x += printable.x;
		if (p1.y != p2.y)
			p1.y += printable.y;
	}
}
