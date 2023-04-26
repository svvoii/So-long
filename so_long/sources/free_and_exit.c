/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/04/26 13:20:24 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_free_and_destroy(t_mlx *p, int status, char *msg);
void	ft_free_textures(t_mlx *p);
void	ft_destroy_img(t_mlx *p, void **img);
void	ft_free_map(t_mlx *m);

void	ft_free_and_destroy(t_mlx *p, int status, char *msg)
{
	if (p->mlx)
	{
		ft_free_textures(p);
		mlx_destroy_window(p->mlx, p->win);
		mlx_destroy_display(p->mlx);
		free(p->mlx);
	}
	ft_free_map(p);
	if (msg)
		ft_putstr_fd(msg, 2);
	exit(status);
}

void	ft_free_textures(t_mlx *p)
{
	ft_destroy_img(p, p->sp.c);
	ft_destroy_img(p, p->sp.up);
	ft_destroy_img(p, p->sp.dn);
	ft_destroy_img(p, p->sp.lt);
	ft_destroy_img(p, p->sp.rt);
	mlx_destroy_image(p->mlx, p->sp.w[0]);
	mlx_destroy_image(p->mlx, p->sp.p[0]);
	mlx_destroy_image(p->mlx, p->sp.e[0]);
	mlx_destroy_image(p->mlx, p->sp.uh[0]);
	mlx_destroy_image(p->mlx, p->bf.img);
}

void	ft_destroy_img(t_mlx *p, void **img)
{
	int	i;

	i = -1;
	while (++i < FRAMES)
		mlx_destroy_image(p->mlx, img[i]);
}

void	ft_free_map(t_mlx *p)
{
	int	i;

	free(p->raw);
	i = 0;
	while (p->map[i])
		free(p->map[i++]);
	free(p->map[i]);
	free(p->map);
	if (p->pix_map)
	{
		i = -1;
		while (++i < p->height * PIX)
			if (p->pix_map[i])
				free(p->pix_map[i]);
		free(p->pix_map);
	}
}
