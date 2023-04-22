/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/04/22 14:22:41 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_free_and_destroy(t_mlx *ptrs, int status, char *msg);
void	ft_free_textures(t_mlx *ptrs);
void	ft_destroy_img(t_mlx *p, void **img);
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
	ft_destroy_img(ptrs, ptrs->collectable);
	ft_destroy_img(ptrs, ptrs->p_up);
	ft_destroy_img(ptrs, ptrs->p_down);
	ft_destroy_img(ptrs, ptrs->p_left);
	ft_destroy_img(ptrs, ptrs->p_right);
	mlx_destroy_image(ptrs->mlx, ptrs->wall[0]);
	mlx_destroy_image(ptrs->mlx, ptrs->path[0]);
	mlx_destroy_image(ptrs->mlx, ptrs->exit[0]);
	//mlx_destroy_image(ptrs->mlx, ptrs->p_up[0]);
	//mlx_destroy_image(ptrs->mlx, ptrs->p_down[0]);
	//mlx_destroy_image(ptrs->mlx, ptrs->p_left[0]);
	//mlx_destroy_image(ptrs->mlx, ptrs->p_right[0]);
	//mlx_destroy_image(ptrs->mlx, ptrs->collectable[0]);
	mlx_destroy_image(ptrs->mlx, ptrs->buff.img);
}

void	ft_destroy_img(t_mlx *p, void **img)
{
	int	i;

	i = -1;
	while (++i < FRAMES)
		mlx_destroy_image(p->mlx, img[i]);
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
	i = -1;
	while (++i < ptrs->height * PIX)
		free(ptrs->pix_map[i]);
	//free(ptrs->pix_map[i]);
	free(ptrs->pix_map);
}
