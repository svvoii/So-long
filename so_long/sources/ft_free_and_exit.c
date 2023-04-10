/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/04/08 12:22:35 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_free_textures(t_mlx *ptrs);
void	ft_free_and_destroy(t_mlx *ptrs, int status, char *msg);
void	ft_free_map(t_mlx *m);

void	ft_free_and_destroy(t_mlx *ptrs, int status, char *msg)
{
	if (ptrs->mlx)
	{
		ft_free_textures(ptrs);
		mlx_destroy_window(ptrs->mlx, ptrs->win);
		mlx_destroy_display(ptrs->mlx);
		free(ptrs->mlx);
	}
	ft_free_map(ptrs);
	if (msg)
		ft_putstr_fd(msg, 2);	
	exit(status);
}

void	ft_free_textures(t_mlx *ptrs)
{
	mlx_destroy_image(ptrs->mlx, ptrs->wall);
	mlx_destroy_image(ptrs->mlx, ptrs->path);
	mlx_destroy_image(ptrs->mlx, ptrs->player);
	mlx_destroy_image(ptrs->mlx, ptrs->collectable);
	mlx_destroy_image(ptrs->mlx, ptrs->exit);
}

void	ft_free_map(t_mlx *ptrs)
{
	int	i;

	free(ptrs->raw);
	i = 0;
	while (ptrs->map[i])
		free(ptrs->map[i++]);
	free(ptrs->map[i]);
	free(ptrs->map);
}
