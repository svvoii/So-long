/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_update_enemy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/03 18:54:26 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	reset_direction(t_mlx *p, int i);
void	move_enemy(t_mlx *p, int i);
void	chase_player(t_mlx *p, int i);
void	move_chasing_enemy(t_mlx *p, int i, char dir);
void	update_enemy_pos(t_mlx *p, int i, char dir);

void	reset_direction(t_mlx *p, int i)
{
	if ((p->en[i].direction == 'N' || p->en[i].direction == 'S')
		&& p->en[i].y == p->en[i].tg_y)
	{
		if (p->en[i].direction == 'N')
			p->en[i].direction = 'S';
		else
			p->en[i].direction = 'N';
		p->en[i].tg_x = p->en[i].st_x;
		p->en[i].tg_y = p->en[i].st_y;
		p->en[i].st_x = p->en[i].x;
		p->en[i].st_y = p->en[i].y;
	}
	else if ((p->en[i].direction == 'W' || p->en[i].direction == 'E')
		&& p->en[i].x == p->en[i].tg_x)
	{
		if (p->en[i].direction == 'W')
			p->en[i].direction = 'E';
		else
			p->en[i].direction = 'W';
		p->en[i].tg_x = p->en[i].st_x;
		p->en[i].tg_y = p->en[i].st_y;
		p->en[i].st_x = p->en[i].x;
		p->en[i].st_y = p->en[i].y;
	}
}

void	move_enemy(t_mlx *p, int i)
{
	int	x;
	int	y;
	int	rt;
	int	dn;
	int	step;

	step = p->en[i].step;
	x = p->en[i].pix_x;
	y = p->en[i].pix_y;
	rt = p->en[i].pix_x + PIX - 1;
	dn = p->en[i].pix_y + PIX - 1;
	if (p->en[i].direction == 'N'
		&& (p->pix_map[y - step][x] != '1' && p->pix_map[y - step][rt] != '1'))
		p->en[i].pix_y -= p->en[i].step;
	else if (p->en[i].direction == 'S' && (p->pix_map[dn + step][x] != '1'
		&& p->pix_map[dn + step][rt] != '1'))
		p->en[i].pix_y += p->en[i].step;
	else if (p->en[i].direction == 'W' && (p->pix_map[y][x - step] != '1'
		&& p->pix_map[dn][x - step] != '1'))
		p->en[i].pix_x -= p->en[i].step;
	else if (p->en[i].direction == 'E' && (p->pix_map[y][rt + step] != '1'
		&& p->pix_map[dn][rt + step] != '1'))
		p->en[i].pix_x += p->en[i].step;
	update_enemy_pos(p, i, p->en[i].direction);
}

void	chase_player(t_mlx *p, int i)
{
	int	player_x;
	int	player_y;
	int	uh_x;
	int	uh_y;

	player_x = p->pos.cur_x;
	player_y = p->pos.cur_y;
	uh_x = p->en[i].x;
	uh_y = p->en[i].y;
	if (uh_y > player_y && p->map[uh_y - 1][uh_x] != '1')
		move_chasing_enemy(p, i, 'N');
	else if (uh_y < player_y && p->map[uh_y + 1][uh_x] != '1')
		move_chasing_enemy(p, i, 'S');
	else if (uh_x > player_x && p->map[uh_y][uh_x - 1] != '1')
		move_chasing_enemy(p, i, 'W');
	else if (uh_x < player_x && p->map[uh_y][uh_x + 1] != '1')
		move_chasing_enemy(p, i, 'E');
}

void	move_chasing_enemy(t_mlx *p, int i, char dir)
{
	int	x;
	int	y;
	int	rt;
	int	dn;

	x = p->en[i].pix_x;
	y = p->en[i].pix_y;
	rt = p->en[i].pix_x + PIX - 1;
	dn = p->en[i].pix_y + PIX - 1;
	if ((dir == 'N') && (p->pix_map[y - 1][x] != '1'
		&& p->pix_map[y - 1][rt] != '1'))
		p->en[i].pix_y -= p->en[i].step;
	else if ((dir == 'S') && (p->pix_map[dn + 1][x] != '1'
		&& p->pix_map[dn + 1][rt] != '1'))
		p->en[i].pix_y += p->en[i].step;
	else if ((dir == 'W') && (p->pix_map[y][x - 1] != '1'
		&& p->pix_map[dn][x - 1] != '1'))
		p->en[i].pix_x -= p->en[i].step;
	else if ((dir == 'E') && (p->pix_map[y][rt + 1] != '1'
		&& p->pix_map[dn][rt + 1] != '1'))
		p->en[i].pix_x += p->en[i].step;
	update_enemy_pos(p, i, dir);
}

void	update_enemy_pos(t_mlx *p, int i, char dir)
{
	int	rt;
	int	dn;

	rt = p->en[i].pix_x + PIX - 1;
	dn = p->en[i].pix_y + PIX - 1;
	if (dir == 'N')
		p->en[i].y = dn / PIX;
	else if (dir == 'S')
		p->en[i].y = p->en[i].pix_y / PIX;
	else if (dir == 'W')
		p->en[i].x = rt / PIX;
	else if (dir == 'E')
		p->en[i].x = p->en[i].pix_x / PIX;
}
