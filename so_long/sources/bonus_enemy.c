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

int		insert_enemy(t_mlx *p);
void	place_enemy(t_mlx *p, int i);
int		valid_tile(t_mlx *p, int x, int y);
void	set_enemy_direction(t_mlx *p, int i, char axis);
int		valid_direction(t_mlx *p, int x, int y);
void	set_vertical(t_mlx *p, int i, int x, int y, char dir);
void	set_horizontal(t_mlx *p, int i, int x, int y, char dir);
void	set_target(t_mlx *p, int i, int x, int y);
void	set_start(t_mlx *p, int i, int x, int y);

/* render_enemy.c */
void	render_enemy(t_mlx *p);
void	reset_direction(t_mlx *p, int i);
void	chase_player(t_mlx *p, int i);
void	update_enemy_pos(t_mlx *p, int i, char dir);
void	drawing_enemy(t_mlx *p, int w_tile, int h_tile);
void	move_enemy(t_mlx *p, int i);
int	up(t_mlx *p, int x, int y, int rt);
int	down(t_mlx *p, int x, int dn, int rt);
int	left(t_mlx *p, int x, int y, int dn);
int	right(t_mlx *p, int rt, int y, int dn);

void	game_over(t_mlx *p);
void	game_stat(t_mlx *p);

int	insert_enemy(t_mlx *p)
{
	int		i;
	int		tiles[3];
	int		speed[5] = {16, 16, 8, 8, 4};
	
	p->en_count = EN_COUNT;
	i = -1;
	while (++i < EN_COUNT)
	{
		place_enemy(p, i);
		printf("Unseen horror x:'%d', y:'%d'\n", p->en[i].x, p->en[i].y);
		p->map[p->en[i].y][p->en[i].x] = 'U';
	}

	tiles[0] = p->height / 2;
	tiles[1] = p->height / 3;
	tiles[2] = p->height / 4;
	i = -1;
	while (++i < p->en_count)
	{
		p->en[i].step = speed[rand() % 5];
		printf("rand_speed: '%d'\n", p->en[i].step);
		p->en[i].depth = tiles[rand() % 3];
		if (i % 2 == 0)
			set_enemy_direction(p, i, 'x');
		else
			set_enemy_direction(p, i, 'y');
	}

	return (0);
}

void	place_enemy(t_mlx *p, int i)
{
	int	tile_count;
	int	path_tiles[p->height * p->width][2];
	int rand_tile;
	int	y;
	int	x;

	tile_count = -1;
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
	if (tile_count <= 0)
		return ;
	srand(time(NULL));
	rand_tile = rand() % tile_count;
	p->en[i].x = path_tiles[rand_tile][0];
	p->en[i].y = path_tiles[rand_tile][1];
	p->en[i].pix_x = p->en[i].x * PIX;
	p->en[i].pix_y = p->en[i].y * PIX;
	printf("tile_count:'%d', rand_tile:'%d'\n", tile_count, rand_tile);
}

int	valid_tile(t_mlx *p, int x, int y)
{
	return ((p->map[y][x] == '0' || p->map[y][x] == 'C')
		&& p->map[y - 1][x] != '1'
		&& p->map[y + 1][x] != '1'
		&& p->map[y][x - 1] != '1'
		&& p->map[y][x + 1] != '1'
		&& p->map[y - 1][x] != 'P'
		&& p->map[y + 1][x] != 'P'
		&& p->map[y][x - 1] != 'P'
		&& p->map[y][x + 1] != 'P'
		);
}

int	valid_direction(t_mlx *p, int x, int y)
{
	return (y > 0 && y < p->height && x > 0 && x < p->width && p->map[y][x] != '1');
}

void	set_enemy_direction(t_mlx *p, int i, char axis)
{
	int	tiles;
	int	x;
	int	y;

	tiles = p->en[i].depth;
	x = p->en[i].x;
	y = p->en[i].y;
	p->en[i].st_x = x;
	p->en[i].st_y = y;
	if (axis == 'y')
	{
		if (valid_direction(p, x, y - tiles))
			set_vertical(p, i, x, y - tiles, 'N');
		else if (valid_direction(p, x, y + tiles))
			set_vertical(p, i, x, y + tiles, 'S');
		else
		{
			if (valid_direction(p, x - tiles, y))
				set_horizontal(p, i, x - tiles, y, 'W');
			else if (valid_direction(p, x + tiles, y))
				set_horizontal(p, i, x + tiles, y, 'E');
		}
	}
	else if (axis == 'x')
	{
		if (valid_direction(p, x - tiles, y))
			set_horizontal(p, i, x - tiles, y, 'W');
		else if (valid_direction(p, x + tiles, y))
			set_horizontal(p, i, x + tiles, y, 'E');
		else
		{
			if (valid_direction(p, x, y - tiles))
				set_vertical(p, i, x, y - tiles, 'N');
			else if (valid_direction(p, x, y + tiles))
				set_vertical(p, i, x, y + tiles, 'S');
		}
	}
	printf("SET: en[%d] dir:'%c', x:'%d'--tg_x:'%d'\ty:'%d'--tg_y:'%d'\tst_x:'%d'--st_y:'%d'\n", i, p->en[i].direction, p->en[i].x, p->en[i].tg_x, p->en[i].y, p->en[i].tg_y, p->en[i].st_x, p->en[i].st_y);
}

void	set_vertical(t_mlx *p, int i, int x, int y, char dir)
{
	if (dir == 'N')
		p->en[i].direction = 'N';
	else
		p->en[i].direction = 'S';
	set_target(p, i, x, y);
}

void	set_horizontal(t_mlx *p, int i, int x, int y, char dir)
{
	if (dir == 'W')
		p->en[i].direction = 'W';
	else
		p->en[i].direction = 'E';
	set_target(p, i, x, y);
}

void	set_target(t_mlx *p, int i, int x, int y)
{
	p->en[i].tg_x = x;
	p->en[i].tg_y = y;
}

void	set_start(t_mlx *p, int i, int x, int y)
{
	p->en[i].st_x = x;
	p->en[i].st_y = y;
}

/* render_enemy.c */
void	render_enemy(t_mlx *p)
{
	int	i;

	i = 0;
	chase_player(p, i);
	while (++i < p->en_count)
		reset_direction(p, i);
	i = 0;
	while (++i < p->en_count)
		move_enemy(p, i);
	i = -1;
	while (++i < p->en_count)
		drawing_enemy(p, p->en[i].pix_x, p->en[i].pix_y);
	game_over(p);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	game_stat(t_mlx *p)
{
	char	*moves;
	char	*count;

	moves = ft_itoa(p->moves);
	count = ft_itoa(p->c_count);
	mlx_string_put(p->mlx, p->win, 1 * PIX, ((p->height - 1) * PIX), 0xFFFFFF, moves);
	mlx_string_put(p->mlx, p->win, 2 * PIX, ((p->height - 1) * PIX), 0xFFFFFF, count);
}

void	game_over(t_mlx *p)
{
	char	msg[] = "GAME OVER";
	int	i;

	//printf("trgb:'%d'\n", create_trgb(0, 255, 255, 255));
	i = -1;
	while (++i < EN_COUNT)
	{
		if (p->pos.cur_y == p->en[i].y && p->pos.cur_x == p->en[i].x)
		{
			//mlx_string_put(p->mlx, p->win, PIX, PIX, 0xFFFFFF, msg);
			mlx_string_put(p->mlx, p->win, ((p->width - 1) / 2) * PIX, ((p->height) / 2) * PIX, create_trgb(0, 255, 255, 255), msg);
			printf("\t\tGAME OVER\n");
		}
	}
}

void	reset_direction(t_mlx *p, int i)
{
	int	x;
	int	y;

	//printf(" reset en[%d] dir:'%c', x:'%d'--tg_x:'%d'\ty:'%d'--tg_y:'%d'\tst_x:'%d'--st_y:'%d'\n", i, p->en[i].direction, p->en[i].x, p->en[i].tg_x, p->en[i].y, p->en[i].tg_y, p->en[i].st_x, p->en[i].st_y);
	if ((p->en[i].direction == 'N' || p->en[i].direction == 'S') && p->en[i].y == p->en[i].tg_y)
	{
		if (p->en[i].direction == 'N')
			p->en[i].direction = 'S';
		else
			p->en[i].direction = 'N';
		set_target(p, i, p->en[i].st_x, p->en[i].st_y);
		set_start(p, i, p->en[i].x, p->en[i].y);
	}
	else if ((p->en[i].direction == 'W' || p->en[i].direction == 'E') && p->en[i].x == p->en[i].tg_x)
	{
		if (p->en[i].direction == 'W')
			p->en[i].direction = 'E';
		else
			p->en[i].direction = 'W';
		set_target(p, i, p->en[i].st_x, p->en[i].st_y);
		set_start(p, i, p->en[i].x, p->en[i].y);
	}
	//printf(" reset en[%d] dir:'%c', x:'%d'--tg_x:'%d'\ty:'%d'--tg_y:'%d'\tst_x:'%d'--st_y:'%d'\n", i, p->en[i].direction, p->en[i].x, p->en[i].tg_x, p->en[i].y, p->en[i].tg_y, p->en[i].st_x, p->en[i].st_y);
	//printf("OK so far\n");
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
	printf("chase en[%d] uh_y:'%d'->'%d'\tuh_x:'%d'->'%d'\n", i, uh_y, player_y, uh_x, player_x);
	if (uh_y > player_y) // uh bellow
		update_enemy_pos(p, i, 'N');
	else if (uh_y < player_y) // uh above
		update_enemy_pos(p, i, 'S');
	else if (uh_x > player_x) // uh to the right
		update_enemy_pos(p, i, 'W');
	else if (uh_x < player_x) // uh to the left
		update_enemy_pos(p, i, 'E');
}

/* */
void	update_enemy_pos(t_mlx *p, int i, char dir)
{
	int	rt;
	int	dn;
	//int	step;

	//step = 4;
	rt = p->en[i].pix_x + PIX - 1;
	dn = p->en[i].pix_y + PIX - 1;
	//printf("\ten. x:'%d', y:'%d'\n", p->en[i].x, p->en[i].y);
	if (dir == 'N')
	{
		p->en[i].y = dn / PIX;
		p->en[i].pix_y -= p->en[i].step;
	}
	else if (dir == 'S')
	{
		p->en[i].y = p->en[i].pix_y / PIX;
		p->en[i].pix_y += p->en[i].step;
	}
	else if (dir == 'W')
	{
		p->en[i].x = rt / PIX;
		p->en[i].pix_x -= p->en[i].step;
	}
	else if (dir == 'E')
	{
		p->en[i].x = p->en[i].pix_x / PIX;
		p->en[i].pix_x += p->en[i].step;
	}
}


void	drawing_enemy(t_mlx *p, int w_tile, int h_tile)
{
	ft_put_sprite_to_buff(p->sp.uh[0], w_tile, h_tile, &p->bf);
}

void	move_enemy(t_mlx *p, int i)
{
	int	rt;
	int	dn;

	rt = p->en[i].pix_x + PIX - 1;
	dn = p->en[i].pix_y + PIX - 1;
	if (p->en[i].direction == 'N' && up(p, p->en[i].pix_x, p->en[i].pix_y, rt))
		p->en[i].pix_y -= p->en[i].step;
	else if (p->en[i].direction == 'S' && down(p, p->en[i].pix_x, dn, rt))
		p->en[i].pix_y += p->en[i].step;
	else if (p->en[i].direction == 'W' && left(p, p->en[i].pix_x, p->en[i].pix_y, dn))
		p->en[i].pix_x -= p->en[i].step;
	else if (p->en[i].direction == 'E' && right(p, rt, p->en[i].pix_y, dn))
		p->en[i].pix_x += p->en[i].step;
	// I might update these enemies positions in update_enemy_pos as well
	if (p->en[i].direction == 'N')
		p->en[i].y = dn / PIX;
	else if (p->en[i].direction == 'S')
		p->en[i].y = p->en[i].pix_y / PIX;
	else if (p->en[i].direction == 'W')
		p->en[i].x = rt / PIX;
	else if (p->en[i].direction == 'E')
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
