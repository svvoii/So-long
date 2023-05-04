/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/04 21:18:45 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

//void	ft_error_bfs(t_mlx *p, t_bfs * bfs, char *str);
void	ft_free_and_destroy(t_mlx *p, int status, char *msg);
void	ft_free_textures(t_mlx *p);
void	ft_destroy_img(t_mlx *p, void **img, int frames);
void	ft_free_map(t_mlx *m);
int		ft_handle_on_destroy(t_mlx *p);

void	ft_free_and_destroy(t_mlx *p, int status, char *msg)
{
	ft_free_bfs(p);
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
	ft_destroy_img(p, p->sp.c, FRAMES);
	ft_destroy_img(p, p->sp.up, FRAMES);
	ft_destroy_img(p, p->sp.dn, FRAMES);
	ft_destroy_img(p, p->sp.lt, FRAMES);
	ft_destroy_img(p, p->sp.rt, FRAMES);
	ft_destroy_img(p, p->sp.num, DIGITS);
	ft_destroy_img(p, p->sp.win, END_FRAMES);
	mlx_destroy_image(p->mlx, p->sp.w);
	mlx_destroy_image(p->mlx, p->sp.p);
	mlx_destroy_image(p->mlx, p->sp.e);
	mlx_destroy_image(p->mlx, p->sp.uh);
	mlx_destroy_image(p->mlx, p->sp.ov);
	mlx_destroy_image(p->mlx, p->bf.img);
}

void	ft_destroy_img(t_mlx *p, void **img, int frames)
{
	int	i;

	i = -1;
	while (++i < frames)
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

int	ft_handle_on_destroy(t_mlx *p)
{
	ft_free_and_destroy(p, 0, NULL);
	return (0);
}
