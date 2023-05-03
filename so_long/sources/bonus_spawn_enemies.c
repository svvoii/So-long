/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spawn_enemies.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/03 18:48:28 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <time.h>

void	insert_enemy(t_mlx *p);
void	spawn_enemy(t_mlx *p, int i);
int		valid_tile(t_mlx *p, int x, int y, int *t_x, int *t_y);
void	render_enemy(t_mlx *p);
int		valid_direction(t_mlx *p, int x, int y);

void	insert_enemy(t_mlx *p)
{
	int		i;
	int		tiles[3];
	int		speed[5] = {16, 8, 8, 8, 4};

	i = -1;
	while (++i < ENEMIES_COUNT)
	{
		spawn_enemy(p, i);
		p->map[p->en[i].y][p->en[i].x] = 'U';
	}
	tiles[0] = p->height / 2;
	tiles[1] = p->height / 3;
	tiles[2] = p->height / 4;
	i = -1;
	while (++i < ENEMIES_COUNT)
	{
		p->en[i].step = speed[rand() % 5];
		p->en[i].depth = tiles[rand() % 3];
		if (i % 2 == 0)
			set_enemy_direction(p, i, 'x');
		else
			set_enemy_direction(p, i, 'y');
	}
}

void	spawn_enemy(t_mlx *p, int i)
{
	int	count;
	int	tiles_x[p->height * p->width];
	int	tiles_y[p->height * p->width];
	int	y;
	int	x;

	count = 0;
	y = -1;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
			if (valid_tile(p, x, y, &tiles_x[count], &tiles_y[count]))
				count++;
	}
	srand(time(NULL));
	p->en[i].x = tiles_x[rand() % count];
	p->en[i].y = tiles_y[rand() % count];
	p->en[i].pix_x = p->en[i].x * PIX;
	p->en[i].pix_y = p->en[i].y * PIX;
}

int	valid_tile(t_mlx *p, int x, int y, int *t_x, int *t_y)
{
	if ((p->map[y][x] == '0' || p->map[y][x] == 'C')
		&& p->map[y - 1][x] != '1' && p->map[y + 1][x] != '1'
		&& p->map[y][x - 1] != '1' && p->map[y][x + 1] != '1'
		&& p->map[y - 1][x] != 'P' && p->map[y + 1][x] != 'P'
		&& p->map[y][x - 1] != 'P' && p->map[y][x + 1] != 'P')
	{
		*t_x = x;
		*t_y = y;
		return (1);
	}
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

int	valid_direction(t_mlx *p, int x, int y)
{
	return (
		y > 0 && y < p->height && x > 0 && x < p->width && p->map[y][x] != '1');
}
