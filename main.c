/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:19:24 by abounab           #+#    #+#             */
/*   Updated: 2024/03/07 21:28:49 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>	

int handle_input(int key)
{
	 key = 0;
     return (key);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "Abounab");
	mlx_loop(mlx);
	mlx_key_hook(mlx_win, handle_input, NULL);
	//graphical work
	mlx_destroy_display(mlx);
    free(mlx);
}
