/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/04/26 16:26:00 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdlib.h>
#include <time.h>

void	place_enemy(t_mlx *p, t_enemy *enemy);
int		valid_tile(t_mlx *p, int x, int y);
int		insert_enemy(t_mlx *p);
void	render_enemy(t_mlx *p);
void	drawing_enemy(t_mlx *p, int w_tile, int h_tile);

void	place_enemy(t_mlx *p, t_enemy *enemy)
{
	int	tile_count = 0;
	int	path_tiles[p->height * p->width][2];
	int rand_tile;
	int	y;
	int	x;

	tile_count = 0;
	y = -1;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
		{
			if (valid_tile(p, x, y))
			{
				path_tiles[tile_count][0] = x;
				path_tiles[tile_count][1] = y;
				tile_count++;
			}
		}
	}
	if (tile_count == 0)
		return ;
	srand(time(NULL));
	rand_tile = rand() % tile_count;
	enemy->x = path_tiles[rand_tile][0];
	enemy->y = path_tiles[rand_tile][1];
}

int	valid_tile(t_mlx *p, int x, int y)
{
	return (p->map[y][x] == '0');
}

int	insert_enemy(t_mlx *p)
{
	t_enemy	enemy;
	place_enemy(p, &enemy);
	printf("Unseen horror x:'%d', y:'%d'\n", enemy.x, enemy.y);
	p->map[enemy.y][enemy.x] = 'U';

	return (0);
}

void	render_enemy(t_mlx *p)
{
	int	h;
	int	w;

	h = -1;
	while (++h < p->height)
	{
		w = -1;
		while (++w < p->width)
		{
			if (p->map[h][w] == 'U')
				drawing_enemy(p, w * PIX, h * PIX);
		}
	}
}

void	drawing_enemy(t_mlx *p, int w_tile, int h_tile)
{
	ft_put_sprite_to_buff(p->sp.uh[0], w_tile, h_tile, &p->bf);
}
