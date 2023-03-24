/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/03/22 16:17:57 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/mlx/mlx.h"

int	deal_key(int key, void *param);
void	ft_putchar(char	c);

int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 700, 400, "test_window");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFAA00);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	// The following will allow to handle events
	mlx_loop(mlx_ptr);
}

int	deal_key(int key, void *param)
{
	ft_putchar('x');
}

void	ft_putchar(char	c)
{
	write(1, &c, 1);
}
