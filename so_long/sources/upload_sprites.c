/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/03 18:59:06 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_load_textures(t_mlx *p);
void	ft_load_player_frames(t_mlx *p);
void	ft_load_coin_frames(t_mlx *p);
void	ft_load_numbers(t_mlx *p);
void	ft_load_you_win(t_mlx *p);

void	ft_load_textures(t_mlx *p)
{
	int	c_h;
	int	c_w;

	p->sp.w = mlx_xpm_file_to_image(p->mlx, "./xpm/W.xpm", &p->t, &p->t);
	p->sp.p = mlx_xpm_file_to_image(p->mlx, "./xpm/_0.xpm", &p->t, &p->t);
	p->sp.e = mlx_xpm_file_to_image(p->mlx, "./xpm/E.xpm", &p->t, &p->t);
	p->sp.uh = mlx_xpm_file_to_image(p->mlx, "./xpm/UH.xpm", &p->t, &p->t);
	p->sp.ov = mlx_xpm_file_to_image(
			p->mlx, "./xpm/o.xpm", &p->sp.wd, &p->sp.ht);
	ft_load_player_frames(p);
	ft_load_coin_frames(p);
	ft_load_numbers(p);
	ft_load_you_win(p);
	c_h = p->height * PIX / 2;
	c_w = p->width * PIX / 2;
	if (p->height * PIX > c_h + p->sp.ht && p->width * PIX > c_w + p->sp.wd)
	{
		p->cent_h = c_h - (p->sp.ht / 2);
		p->cent_w = c_w - (p->sp.wd / 2);
	}
	else
	{
		p->cent_h = 0;
		p->cent_w = 0;
	}
}

void	ft_load_player_frames(t_mlx *p)
{
	p->sp.up[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/up00.xpm", &p->t, &p->t);
	p->sp.up[1] = mlx_xpm_file_to_image(p->mlx, "./xpm/up01.xpm", &p->t, &p->t);
	p->sp.up[2] = mlx_xpm_file_to_image(p->mlx, "./xpm/up02.xpm", &p->t, &p->t);
	p->sp.up[3] = mlx_xpm_file_to_image(p->mlx, "./xpm/up03.xpm", &p->t, &p->t);
	p->sp.up[4] = mlx_xpm_file_to_image(p->mlx, "./xpm/up04.xpm", &p->t, &p->t);
	p->sp.up[5] = mlx_xpm_file_to_image(p->mlx, "./xpm/up05.xpm", &p->t, &p->t);
	p->sp.dn[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/dn00.xpm", &p->t, &p->t);
	p->sp.dn[1] = mlx_xpm_file_to_image(p->mlx, "./xpm/dn01.xpm", &p->t, &p->t);
	p->sp.dn[2] = mlx_xpm_file_to_image(p->mlx, "./xpm/dn02.xpm", &p->t, &p->t);
	p->sp.dn[3] = mlx_xpm_file_to_image(p->mlx, "./xpm/dn03.xpm", &p->t, &p->t);
	p->sp.dn[4] = mlx_xpm_file_to_image(p->mlx, "./xpm/dn04.xpm", &p->t, &p->t);
	p->sp.dn[5] = mlx_xpm_file_to_image(p->mlx, "./xpm/dn05.xpm", &p->t, &p->t);
	p->sp.lt[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/lt00.xpm", &p->t, &p->t);
	p->sp.lt[1] = mlx_xpm_file_to_image(p->mlx, "./xpm/lt01.xpm", &p->t, &p->t);
	p->sp.lt[2] = mlx_xpm_file_to_image(p->mlx, "./xpm/lt02.xpm", &p->t, &p->t);
	p->sp.lt[3] = mlx_xpm_file_to_image(p->mlx, "./xpm/lt03.xpm", &p->t, &p->t);
	p->sp.lt[4] = mlx_xpm_file_to_image(p->mlx, "./xpm/lt04.xpm", &p->t, &p->t);
	p->sp.lt[5] = mlx_xpm_file_to_image(p->mlx, "./xpm/lt05.xpm", &p->t, &p->t);
	p->sp.rt[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/rt00.xpm", &p->t, &p->t);
	p->sp.rt[1] = mlx_xpm_file_to_image(p->mlx, "./xpm/rt01.xpm", &p->t, &p->t);
	p->sp.rt[2] = mlx_xpm_file_to_image(p->mlx, "./xpm/rt02.xpm", &p->t, &p->t);
	p->sp.rt[3] = mlx_xpm_file_to_image(p->mlx, "./xpm/rt03.xpm", &p->t, &p->t);
	p->sp.rt[4] = mlx_xpm_file_to_image(p->mlx, "./xpm/rt04.xpm", &p->t, &p->t);
	p->sp.rt[5] = mlx_xpm_file_to_image(p->mlx, "./xpm/rt05.xpm", &p->t, &p->t);
}

void	ft_load_coin_frames(t_mlx *p)
{
	p->sp.c[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/c00.xpm", &p->t, &p->t);
	p->sp.c[1] = mlx_xpm_file_to_image(p->mlx, "./xpm/c01.xpm", &p->t, &p->t);
	p->sp.c[2] = mlx_xpm_file_to_image(p->mlx, "./xpm/c02.xpm", &p->t, &p->t);
	p->sp.c[3] = mlx_xpm_file_to_image(p->mlx, "./xpm/c03.xpm", &p->t, &p->t);
	p->sp.c[4] = mlx_xpm_file_to_image(p->mlx, "./xpm/c04.xpm", &p->t, &p->t);
	p->sp.c[5] = mlx_xpm_file_to_image(p->mlx, "./xpm/c05.xpm", &p->t, &p->t);
}

void	ft_load_numbers(t_mlx *p)
{
	p->sp.num[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/0.xpm", &p->t, &p->t);
	p->sp.num[1] = mlx_xpm_file_to_image(p->mlx, "./xpm/1.xpm", &p->t, &p->t);
	p->sp.num[2] = mlx_xpm_file_to_image(p->mlx, "./xpm/2.xpm", &p->t, &p->t);
	p->sp.num[3] = mlx_xpm_file_to_image(p->mlx, "./xpm/3.xpm", &p->t, &p->t);
	p->sp.num[4] = mlx_xpm_file_to_image(p->mlx, "./xpm/4.xpm", &p->t, &p->t);
	p->sp.num[5] = mlx_xpm_file_to_image(p->mlx, "./xpm/5.xpm", &p->t, &p->t);
	p->sp.num[6] = mlx_xpm_file_to_image(p->mlx, "./xpm/6.xpm", &p->t, &p->t);
	p->sp.num[7] = mlx_xpm_file_to_image(p->mlx, "./xpm/7.xpm", &p->t, &p->t);
	p->sp.num[8] = mlx_xpm_file_to_image(p->mlx, "./xpm/8.xpm", &p->t, &p->t);
	p->sp.num[9] = mlx_xpm_file_to_image(p->mlx, "./xpm/9.xpm", &p->t, &p->t);
}

void	ft_load_you_win(t_mlx *p)
{
	p->sp.win[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/w0.xpm", &p->t, &p->t);
	p->sp.win[1] = mlx_xpm_file_to_image(p->mlx, "./xpm/w0.xpm", &p->t, &p->t);
	p->sp.win[2] = mlx_xpm_file_to_image(p->mlx, "./xpm/w0.xpm", &p->t, &p->t);
	p->sp.win[3] = mlx_xpm_file_to_image(p->mlx, "./xpm/w0.xpm", &p->t, &p->t);
	p->sp.win[4] = mlx_xpm_file_to_image(p->mlx, "./xpm/w1.xpm", &p->t, &p->t);
	p->sp.win[5] = mlx_xpm_file_to_image(p->mlx, "./xpm/w1.xpm", &p->t, &p->t);
	p->sp.win[6] = mlx_xpm_file_to_image(p->mlx, "./xpm/w0.xpm", &p->t, &p->t);
	p->sp.win[7] = mlx_xpm_file_to_image(p->mlx, "./xpm/w0.xpm", &p->t, &p->t);
	p->sp.win[8] = mlx_xpm_file_to_image(p->mlx, "./xpm/w0.xpm", &p->t, &p->t);
	p->sp.win[9] = mlx_xpm_file_to_image(p->mlx, "./xpm/w0.xpm", &p->t, &p->t);
	p->sp.win[10] = mlx_xpm_file_to_image(p->mlx, "./xpm/w0.xpm", &p->t, &p->t);
	p->sp.win[11] = mlx_xpm_file_to_image(p->mlx, "./xpm/w0.xpm", &p->t, &p->t);
	p->sp.win[12] = mlx_xpm_file_to_image(p->mlx, "./xpm/w0.xpm", &p->t, &p->t);
	p->sp.win[13] = mlx_xpm_file_to_image(p->mlx, "./xpm/w2.xpm", &p->t, &p->t);
	p->sp.win[14] = mlx_xpm_file_to_image(p->mlx, "./xpm/w2.xpm", &p->t, &p->t);
	p->sp.win[15] = mlx_xpm_file_to_image(p->mlx, "./xpm/w2.xpm", &p->t, &p->t);
	p->sp.win[16] = mlx_xpm_file_to_image(p->mlx, "./xpm/w2.xpm", &p->t, &p->t);
	p->sp.win[17] = mlx_xpm_file_to_image(p->mlx, "./xpm/w3.xpm", &p->t, &p->t);
	p->sp.win[18] = mlx_xpm_file_to_image(p->mlx, "./xpm/w3.xpm", &p->t, &p->t);
	p->sp.win[19] = mlx_xpm_file_to_image(p->mlx, "./xpm/w3.xpm", &p->t, &p->t);
	p->sp.win[20] = mlx_xpm_file_to_image(p->mlx, "./xpm/w3.xpm", &p->t, &p->t);
	p->sp.win[21] = mlx_xpm_file_to_image(p->mlx, "./xpm/w2.xpm", &p->t, &p->t);
	p->sp.win[22] = mlx_xpm_file_to_image(p->mlx, "./xpm/w2.xpm", &p->t, &p->t);
	p->sp.win[23] = mlx_xpm_file_to_image(p->mlx, "./xpm/w2.xpm", &p->t, &p->t);
}
