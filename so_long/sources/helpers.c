/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/03 19:38:00 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	game_statistics(t_mlx *p);
void	moves_count(t_mlx *p);
void	collectables_count(t_mlx *p);
void	calculate_coins(t_mlx *p);
void	ft_collectables(t_mlx *p);

/* game statistics */
void	game_statistics(t_mlx *p)
{
	int	i;

	if (!p->game_over)
	{
		moves_count(p);
		collectables_count(p);
		if (p->c_count == 0 && p->map[p->pos.cur_y][p->pos.cur_x] == 'E')
			p->game_over = 1;
	}
	i = -1;
	while (++i < ENEMIES_COUNT)
		if (!p->game_over && p->pos.cur_y == p->en[i].y
			&& p->pos.cur_x == p->en[i].x)
			p->game_over = -1;
}

void	moves_count(t_mlx *p)
{
	static int		tmp;
	int				i;
	int				num[3];

	num[0] = p->moves / 100;
	num[1] = (p->moves / 10) % 10;
	num[2] = p->moves % 10;
	if (p->pos.cur_x != p->pos.prev_x || p->pos.cur_y != p->pos.prev_y)
	{
		p->pos.prev_x = p->pos.cur_x;
		p->pos.prev_y = p->pos.cur_y;
		p->moves++;
	}
	if (tmp != p->moves)
	{
		ft_putstr_fd("moves: ", 1);
		ft_putnbr_fd(num[0], 1);
		ft_putnbr_fd(num[1], 1);
		ft_putnbr_fd(num[2], 1);
		write(1, "\n", 1);
		tmp = p->moves;
	}
	i = -1;
	while (++i < 3)
		ft_put_sprite_to_buff(p->sp.num[num[i]], PIX * (i + 1), 1, &p->bf);
}

void	collectables_count(t_mlx *p)
{
	int	c[2];

	calculate_coins(p);
	c[0] = p->c_count / 10;
	c[1] = p->c_count % 10;
	ft_put_sprite_to_buff(p->sp.num[c[0]], (p->width - 3) * PIX, 0, &p->bf);
	ft_put_sprite_to_buff(p->sp.num[c[1]], (p->width - 2) * PIX, 0, &p->bf);
}

void	calculate_coins(t_mlx *p)
{
	int	x;
	int	y;

	p->c_count = 0;
	y = -1;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
			if (p->map[y][x] == 'C')
				p->c_count++;
	}
}

void	ft_collectables(t_mlx *p)
{
	int	x;
	int	y;
	int	rt;
	int	dn;

	x = p->pos.x;
	y = p->pos.y;
	rt = p->pos.x + PIX - 1;
	dn = p->pos.y + PIX - 1;
	if (p->pix_map[y][x] == 'C' || p->pix_map[y][rt] == 'C'
		|| p->pix_map[dn][x] == 'C' || p->pix_map[dn][rt] == 'C')
	{
		p->map[y / PIX][x / PIX] = '0';
		p->map[y / PIX][rt / PIX] = '0';
		p->map[dn / PIX][x / PIX] = '0';
		p->map[dn / PIX][rt / PIX] = '0';
	}
}
