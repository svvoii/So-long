/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/04/27 10:51:23y sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdlib.h>
#include <time.h>

void	place_enemy(t_mlx *p, int i);
int		valid_tile(t_mlx *p, int x, int y);
int		insert_enemy(t_mlx *p);
void	render_enemy(t_mlx *p);
void	drawing_enemy(t_mlx *p, int w_tile, int h_tile);

void	set_enemy_direction(t_mlx *p, int i);
void	reset_direction(t_mlx *p, int i);
void	set_target(t_mlx *p, int i, int x, int y);
void	move_enemy(t_mlx *p, int i);
int		up(t_mlx *p, int x, int y, int rt);
int		down(t_mlx *p, int x, int dn, int rt);
int		left(t_mlx *p, int x, int y, int dn);
int		right(t_mlx *p, int rt, int y, int dn);

void	place_enemy(t_mlx *p, int i)
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
	p->en[i].x = path_tiles[rand_tile][0];
	p->en[i].y = path_tiles[rand_tile][1];
	p->en[i].pix_x = p->en[i].x * PIX;
	p->en[i].pix_y = p->en[i].y * PIX;
}

int	valid_tile(t_mlx *p, int x, int y)
{
	return (p->map[y][x] == '0');
}

int	insert_enemy(t_mlx *p)
{
	int		i;
	
	p->en_count = EN_COUNT;
	i = -1;
	while (++i < EN_COUNT)
	{
		place_enemy(p, i);
		printf("Unseen horror x:'%d', y:'%d'\n", p->en[i].x, p->en[i].y);
		p->map[p->en[i].y][p->en[i].x] = 'U';
	}

	i = -1;
	while (++i < p->en_count)
		set_enemy_direction(p, i);

	return (0);
}

void	render_enemy(t_mlx *p)
{
	int			i;

	printf("en_count: '%d'\n", p->en_count);
	i = -1;
	while (++i < p->en_count)
		printf("en. x:'%d', y:'%d'\tpix_x:'%d', pix_y:'%d'\n", p->en[i].x, p->en[i].y, p->en[i].pix_x, p->en[i].pix_y);
	i = -1;
	while (++i < p->en_count)
		reset_direction(p, i);
	i = -1;
	while (++i < p->en_count)
		move_enemy(p, i);
	i = -1;
	while (++i < p->en_count)
		drawing_enemy(p, p->en[i].pix_x, p->en[i].pix_y);
}

/*
void	set_enemy_position(t_mlx *p, t_enemy en[p->en_count])
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = -1;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
			if (p->map[y][x] == 'U')
			{
				en[i].x = x;
				en[i].y = y;
				en[i].pix_x = x * PIX;
				en[i].pix_y = y * PIX;
				i++;
			}
	}
}*/

void	drawing_enemy(t_mlx *p, int w_tile, int h_tile)
{
	ft_put_sprite_to_buff(p->sp.uh[0], w_tile, h_tile, &p->bf);
}

int	valid_direction(t_mlx *p, int x, int y)
{
	return (y > 0 && y < p->height && x > 0 && x < p->width && p->map[y][x] != '1');
}

void	set_enemy_direction(t_mlx *p, int i)
{
	int	tiles;
	int	x;
	int	y;

	tiles = 3;
	p->en[i].st_x = p->en[i].x;
	p->en[i].st_y = p->en[i].y;
	x = p->en[i].x;
	y = p->en[i].y;
	while (--tiles >= 0)
	{
		if (valid_direction(p, x, y - tiles))
		{
			p->en[i].direction = NORTH;
			set_target(p, i, x, y - tiles);
		}
		else if (valid_direction(p, x, y + tiles))
		{
			p->en[i].direction = SOUTH;
			set_target(p, i, x, y - tiles);
		}
		else if (valid_direction(p, x - tiles, y))
		{
			p->en[i].direction = WEST;
			set_target(p, i, x, y - tiles);
		}
		else if (valid_direction(p, x + tiles, y))
		{
			p->en[i].direction = EAST;
			set_target(p, i, x, y - tiles);
		}
	}
}

void	set_target(t_mlx *p, int i, int x, int y)
{
	p->en[i].tg_x = x;
	p->en[i].tg_y = y;
}

void	reset_direction(t_mlx *p, int i)
{
	int	x;
	int	y;

 /* adding the logic of enemy movement 
 ** if x and y equal target_x and target_y swap direction */
	if ((p->en[i].direction == NORTH || p->en[i].direction == SOUTH) && p->en[i].y == p->en[i].tg_y)
	{
		if (p->en[i].direction == NORTH)
			p->en[i].direction = SOUTH;
		else if (p->en[i].direction == SOUTH);
			p->en[i].direction = NORTH;
		set_target(p, i, p->en[i].st_x, p->en[i].st_y);
		p->en[i].st_x = p->en[i].x;
		p->en[i].st_y = p->en[i].y;
	}
	else if ((p->en[i].direction == WEST || p->en[i].direction == EAST) && p->en[i].x == p->en[i].tg_x)
	{
		if (p->en[i].direction == WEST)
			p->en[i].direction = EAST;
		else if (p->en[i].direction == EAST);
			p->en[i].direction = EAST;
		set_target(p, i, p->en[i].st_x, p->en[i].st_y);
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

	x = p->en[i].x;
	y = p->en[i].y;
	rt = p->en[i].pix_x + PIX - 1;
	dn = p->en[i].pix_y + PIX - 1;
	step = 2;
	if (p->en[i].direction == NORTH && up(p, p->en[i].pix_x, p->en[i].pix_y, rt))
		p->en[i].pix_y -= step;
	else if (p->en[i].direction == SOUTH && down(p, p->en[i].pix_x, dn, rt))
		p->en[i].pix_y += step;
	else if (p->en[i].direction == WEST && left(p, p->en[i].pix_x, p->en[i].pix_y, dn))
		p->en[i].pix_x -= step;
	else if (p->en[i].direction == EAST && right(p, rt, p->en[i].pix_y, dn))
		p->en[i].pix_x += step;
	//printf("\ten. x:'%d', y:'%d'\tdirection:'%c'\n", p->en[i].x, p->en[i].y, p->en[i].direction);
	if (p->en[i].direction == NORTH)
		p->en[i].y = dn / PIX;
	else if (p->en[i].direction == SOUTH)
		p->en[i].y = p->en[i].pix_y / PIX;
	else if (p->en[i].direction == WEST)
		p->en[i].x = rt / PIX;
	else if (p->en[i].direction == EAST)
		p->en[i].x = p->en[i].pix_x / PIX;
}

int	up(t_mlx *p, int x, int y, int rt)
{
	if (p->pix_map[y - 1][x] != '1' && p->pix_map[y - 1][rt] != '1')
		return (1);
	return (0);
}

int	down(t_mlx *p, int x, int dn, int rt)
{
	if (p->pix_map[dn + 1][x] != '1' && p->pix_map[dn + 1][rt] != '1')
		return (1);
	return (0);
}

int	left(t_mlx *p, int x, int y, int dn)
{
	if (p->pix_map[y][x - 1] != '1' && p->pix_map[dn][x - 1] != '1')
		return (1);
	return (0);
}

int	right(t_mlx *p, int rt, int y, int dn)
{
	if (p->pix_map[y][rt + 1] != '1' && p->pix_map[dn][rt + 1] != '1')
		return (1);
	return (0);
}
