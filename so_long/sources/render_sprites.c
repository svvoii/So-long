/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/01 12:45:17 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_render_back_buff_img(t_mlx *p);
void	ft_render_player(t_mlx *p);
void	ft_set_direction(t_mlx *p);
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
			if (p->map[y][x] == '0' || p->map[y][x] == 'P' || p->map[y][x] == 'U')
				ft_put_sprite_to_buff(p->sp.p[0], x * PIX, y * PIX, &p->bf);
			else if (p->map[y][x] == '1')
				ft_put_sprite_to_buff(p->sp.w[0], x * PIX, y * PIX, &p->bf);
			else if (p->map[y][x] == 'E')
				ft_put_sprite_to_buff(p->sp.e[0], x * PIX, y * PIX, &p->bf);
			else if (p->map[y][x] == 'C')
				ft_put_sprite_to_buff(p->sp.c[frame], x * PIX, y * PIX, &p->bf);
		}
	}
	frame = (frame + 1) % FRAMES;
}

void	ft_render_player(t_mlx *p)
{
	static int	frame;

	ft_set_direction(p);
	ft_drawing_movement(p, &frame, p->pos.x, p->pos.y);
	ft_collect_and_exit(p);
	frame = (frame + 1) % FRAMES;
}

void	ft_set_direction(t_mlx *p)
{
	int	x;
	int	y;
	int	rt;
	int	dn;
	int	step;

	x = p->pos.x;
	y = p->pos.y;
	rt = p->pos.x + PIX - 1;
	dn = p->pos.y + PIX - 1;
	step = 16;
	if ((p->key == 65362 || p->key == 119)
		&& (p->pix_map[y - 1][x] != '1' && p->pix_map[y - 1][rt] != '1'))
		p->pos.y -= step;
	else if ((p->key == 65364 || p->key == 115)
		&& (p->pix_map[dn + 1][x] != '1' && p->pix_map[dn + 1][rt] != '1'))
		p->pos.y += step;
	else if ((p->key == 65361 || p->key == 97)
		&& (p->pix_map[y][x - 1] != '1' && p->pix_map[dn][x - 1] != '1'))
		p->pos.x -= step;
	else if ((p->key == 65363 || p->key == 100)
		&& (p->pix_map[y][rt + 1] != '1' && p->pix_map[dn][rt + 1] != '1'))
		p->pos.x += step;
	p->pos.cur_x = p->pos.x / PIX;
	p->pos.cur_y = p->pos.y / PIX;
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
