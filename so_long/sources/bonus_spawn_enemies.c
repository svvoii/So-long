/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spawn_enemies.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/04 17:42:32 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <time.h>

void	insert_enemy(t_mlx *p);
void	spawn_enemy(t_mlx *p);
void	save_valid_tiles(int tile[2], int x, int y, int *count);
int		valid_tile(t_mlx *p, int x, int y);
void	render_enemy(t_mlx *p);

void	insert_enemy(t_mlx *p)
{
	int		i;
	int		deep[3];
	int		speed[3];

	deep[0] = p->height / 2;
	deep[1] = p->height / 3;
	deep[2] = p->height / 4;
	speed[0] = 16;
	speed[1] = 8;
	speed[2] = 4;
	spawn_enemy(p);
	i = -1;
	while (++i < ENEMIES_COUNT)
	{
		p->en[i].step = speed[rand() % 3];
		p->en[i].depth = deep[rand() % 3];
		p->en[i].pix_x = p->en[i].x * PIX;
		p->en[i].pix_y = p->en[i].y * PIX;
		if (i % 2 == 0)
			set_enemy_direction(p, i, 'x');
		else
			set_enemy_direction(p, i, 'y');
	}
}

void	spawn_enemy(t_mlx *p)
{
	int	tiles[TMP_BUF][2];
	int	count;
	int	i;
	int	y;
	int	x;

	count = 0;
	y = -1;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
			if (valid_tile(p, x, y) && count < TMP_BUF)
				save_valid_tiles(tiles[count], x, y, &count);
	}
	i = -1;
	srand(time(NULL) * getpid());
	while (++i < ENEMIES_COUNT)
	{
		y = rand() % count;
		p->en[i].x = tiles[y][0];
		p->en[i].y = tiles[y][1];
		p->map[p->en[i].y][p->en[i].x] = 'U';
	}
}

void	save_valid_tiles(int tile[2], int x, int y, int *count)
{
	tile[0] = x;
	tile[1] = y;
	*count += 1;
}

int	valid_tile(t_mlx *p, int x, int y)
{
	if ((p->map[y][x] == '0' || p->map[y][x] == 'C')
		&& p->map[y - 1][x] != '1' && p->map[y + 1][x] != '1'
		&& p->map[y][x - 1] != '1' && p->map[y][x + 1] != '1'
		&& p->map[y - 1][x] != 'P' && p->map[y + 1][x] != 'P'
		&& p->map[y][x - 1] != 'P' && p->map[y][x + 1] != 'P')
		return (1);
	return (0);
}

void	render_enemy(t_mlx *p)
{
	int	i;

	i = 0;
	chase_player(p, i);
	while (++i < ENEMIES_COUNT)
		reset_direction(p, i);
	i = 0;
	while (++i < ENEMIES_COUNT)
		move_enemy(p, i);
	i = -1;
	while (++i < ENEMIES_COUNT)
		ft_put_sprite_to_buff(p->sp.uh, p->en[i].pix_x, p->en[i].pix_y, &p->bf);
}
