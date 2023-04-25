/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/03/30 14:54:27by sbocanci         ###   ########.fr       */
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
	int	y;
	int	x;
	static int	frame;

	ft_bzero(p->buff.addr, p->buff.line_len * p->height);
	y = -1;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
		{
			if (p->map[y][x] == '0' || p->map[y][x] == 'P')
				ft_put_sprite_to_buff(p->sp.path[0], x * PIX, y * PIX, &p->buff);
			else if (p->map[y][x] == '1')
				ft_put_sprite_to_buff(p->sp.wall[0], x * PIX, y * PIX, &p->buff);
			else if (p->map[y][x] == 'E')
				ft_put_sprite_to_buff(p->sp.exit[0], x * PIX, y * PIX, &p->buff);
			else if (p->map[y][x] == 'C')
				ft_put_sprite_to_buff(p->sp.collectable[frame], x * PIX, y * PIX, &p->buff);
		}
	}
	frame = (frame + 1) % FRAMES;
}

void	ft_render_player(t_mlx *p)
{
	static int	frame;

	ft_set_direction(p);
	ft_drawing_movement(p, &frame, p->pos.x, p->pos.y);
/*
	printf("x:'%d'\ty:'%d'\t", p->pos.x, p->pos.y);
	printf("p_x:'%d'\tp_y:'%d'\t", p->pos.cur_x, p->pos.cur_y);
	printf("collectables:'%d'\t", p->c_count);
	printf("moves:'%d'\n", p->moves);
*/
	ft_collect_and_exit(p);

	frame = (frame + 1) % FRAMES;
}

void	ft_set_direction(t_mlx *p)
{
	int	x = p->pos.x;
	int	y = p->pos.y;
	int	x_rt = p->pos.x + PIX - 1;
	int	y_dn = p->pos.y + PIX - 1;
	int	step = 8;

	if ((p->key == 65362 || p->key == 119) 
		&& (p->pix_map[y - 1][x] != '1' && p->pix_map[y - 1][x_rt] != '1'))
		p->pos.y -= step;
	else if ((p->key == 65364 || p->key == 115) && (p->pix_map[y_dn + 1][x] != '1' && p->pix_map[y_dn + 1][x_rt] != '1'))
		p->pos.y += step;
	else if ((p->key == 65361 || p->key == 97) && (p->pix_map[y][x - 1] != '1' && p->pix_map[y_dn][x - 1] != '1')) 
		p->pos.x -= step;
	else if ((p->key == 65363 || p->key == 100) && (p->pix_map[y][x_rt + 1] != '1' && p->pix_map[y_dn][x_rt + 1] != '1'))
		p->pos.x += step;
	p->pos.cur_x = p->pos.x / PIX;
	p->pos.cur_y = p->pos.y / PIX;
}

void	ft_drawing_movement(t_mlx *p, int *frame, int w_tile, int h_tile)
{
	if (p->key == 65362 || p->key == 119) // up
		ft_put_sprite_to_buff(p->sp.p_up[*frame], w_tile, h_tile, &p->buff);
	else if (p->key == 65364 || p->key == 115) // down
		ft_put_sprite_to_buff(p->sp.p_down[*frame], w_tile, h_tile, &p->buff);
	else if (p->key == 65361 || p->key == 97) // left 
		ft_put_sprite_to_buff(p->sp.p_left[*frame], w_tile, h_tile, &p->buff);
	else if (p->key == 65363 || p->key == 100) // right 
		ft_put_sprite_to_buff(p->sp.p_right[*frame], w_tile, h_tile, &p->buff);
	else
		ft_put_sprite_to_buff(p->sp.p_down[0], w_tile, h_tile, &p->buff);
}

void	ft_put_sprite_to_buff(void *spr, int x, int y, t_image *back_buff)
{
	int		pix_x;
	int		pix_y;
	int		pix_offset;
	int		spr_offset;
	int		h;
	int		w;
	t_image	sprite;

	sprite.img = mlx_get_data_addr(spr, &sprite.bpp, &sprite.line_len, &sprite.endian);

	h = -1;
	while (++h < PIX)
	{
		w = -1;
		while (++w < PIX)
		{
			pix_y = y + h;
			pix_x = x + w;
			pix_offset = (pix_y * back_buff->line_len) + (pix_x * (back_buff->bpp / 8));
			spr_offset = (h * sprite.line_len) + (w * (sprite.bpp / 8));
			ft_memcpy(back_buff->addr + pix_offset, sprite.img + spr_offset, back_buff->bpp / 8);
		}
	}
}
