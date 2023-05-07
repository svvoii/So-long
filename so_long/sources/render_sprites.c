/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/07 12:51:36 by svoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_render_back_buff_img(t_mlx *p);
void	ft_set_direction(t_mlx *p);
void	ft_update_player_pos(t_mlx *p);
void	ft_drawing_movement(t_mlx *p, int *frame, int w_tile, int h_tile);
void	ft_put_sprite_to_buff(void *spr, int x, int y, t_image *back_buff);

void	ft_render_back_buff_img(t_mlx *p)
{
	int			y;
	int			x;
	static int	frame;

	ft_bzero(p->bf.addr, p->bf.line_len * p->height);
	y = -1;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
		{
			if (p->map[y][x] == '0' || p->map[y][x] == 'P'
			|| p->map[y][x] == 'U' || p->map[y][x] == 'C'
			|| p->map[y][x] == 'E')
				ft_put_sprite_to_buff(p->sp.p, x * PIX, y * PIX, &p->bf);
			else if (p->map[y][x] == '1')
				ft_put_sprite_to_buff(p->sp.w, x * PIX, y * PIX, &p->bf);
			if (p->map[y][x] == 'E')
				ft_put_sprite_to_buff(p->sp.e, x * PIX, y * PIX, &p->bf);
			if (p->map[y][x] == 'C')
				ft_put_sprite_to_buff(p->sp.c[frame], x * PIX, y * PIX, &p->bf);
		}
	}
	frame = (frame + 1) % FRAMES;
}

void	ft_set_direction(t_mlx *p)
{
	int	x;
	int	y;
	int	rt;
	int	dn;
	int	stp;

	x = p->pos.x;
	y = p->pos.y;
	rt = p->pos.x + PIX - 1;
	dn = p->pos.y + PIX - 1;
	stp = p->pos.step;
	if ((p->key == 65362 || p->key == 119)
		&& (p->pix_map[y - stp][x] != '1' && p->pix_map[y - stp][rt] != '1'))
		p->pos.y -= stp;
	else if ((p->key == 65364 || p->key == 115)
		&& (p->pix_map[dn + stp][x] != '1' && p->pix_map[dn + stp][rt] != '1'))
		p->pos.y += stp;
	else if ((p->key == 65361 || p->key == 97)
		&& (p->pix_map[y][x - stp] != '1' && p->pix_map[dn][x - stp] != '1'))
		p->pos.x -= stp;
	else if ((p->key == 65363 || p->key == 100)
		&& (p->pix_map[y][rt + stp] != '1' && p->pix_map[dn][rt + stp] != '1'))
		p->pos.x += stp;
	ft_update_player_pos(p);
}

void	ft_update_player_pos(t_mlx *p)
{
	int	rt;
	int	dn;

	rt = p->pos.x + PIX - 1;
	dn = p->pos.y + PIX - 1;
	if (p->key == 65362 || p->key == 119)
		p->pos.cur_y = dn / PIX;
	else if (p->key == 65364 || p->key == 115)
		p->pos.cur_y = p->pos.y / PIX;
	else if (p->key == 65361 || p->key == 97)
		p->pos.cur_x = rt / PIX;
	else if (p->key == 65363 || p->key == 100)
		p->pos.cur_x = p->pos.x / PIX;
}

void	ft_drawing_movement(t_mlx *p, int *frame, int w_tile, int h_tile)
{
	if (p->key == 65362 || p->key == 119)
		ft_put_sprite_to_buff(p->sp.up[*frame], w_tile, h_tile, &p->bf);
	else if (p->key == 65364 || p->key == 115)
		ft_put_sprite_to_buff(p->sp.dn[*frame], w_tile, h_tile, &p->bf);
	else if (p->key == 65361 || p->key == 97)
		ft_put_sprite_to_buff(p->sp.lt[*frame], w_tile, h_tile, &p->bf);
	else if (p->key == 65363 || p->key == 100)
		ft_put_sprite_to_buff(p->sp.rt[*frame], w_tile, h_tile, &p->bf);
	else
		ft_put_sprite_to_buff(p->sp.dn[0], w_tile, h_tile, &p->bf);
}

void	ft_put_sprite_to_buff(void *sprite, int x, int y, t_image *bf)
{
	int		pix_off;
	int		spr_off;
	int		h;
	int		w;
	t_image	spr;

	spr.addr = mlx_get_data_addr(sprite, &spr.bpp, &spr.line_len, &spr.endian);
	spr.img = (void *)spr.addr;
	h = -1;
	while (++h < PIX)
	{
		w = -1;
		while (++w < PIX)
		{
			pix_off = (y + h) * bf->line_len + (x + w) * (bf->bpp / 8);
			spr_off = (h * spr.line_len) + (w * (spr.bpp / 8));
			if ((unsigned char)spr.addr[spr_off + 3] != 0xFF)
				ft_memcpy(bf->addr + pix_off, spr.img + spr_off, bf->bpp / 8);
		}
	}
}
/*
void	ft_put_sprite_to_buff(void *sprite, int x, int y, t_image *bf)
{
	int		pix_off;
	int		spr_off;
	int		h;
	int		w;
	t_image	spr;

	spr.img = mlx_get_data_addr(sprite, &spr.bpp, &spr.line_len, &spr.endian);
	h = -1;
	while (++h < PIX)
	{
		w = -1;
		while (++w < PIX)
		{
			pix_off = (y + h) * bf->line_len + (x + w) * (bf->bpp / 8);
			spr_off = (h * spr.line_len) + (w * (spr.bpp / 8));
			ft_memcpy(bf->addr + pix_off, spr.img + spr_off, bf->bpp / 8);
		}
	}
}
*/