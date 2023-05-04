/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_set_enemy_direction.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/04 16:52:35 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	set_enemy_direction(t_mlx *p, int i, char axis);
void	set_y_axis_direction(t_mlx *p, int i, int x, int y);
void	set_x_axis_direction(t_mlx *p, int i, int x, int y);
void	set_target(t_mlx *p, int i, int x, int y);
int		valid_direction(t_mlx *p, int x, int y);

/* this sets initial direction for enemies when initialized from insert_enemy */
void	set_enemy_direction(t_mlx *p, int i, char axis)
{
	int	x;
	int	y;

	x = p->en[i].x;
	y = p->en[i].y;
	p->en[i].st_x = x;
	p->en[i].st_y = y;
	if (axis == 'y')
		set_y_axis_direction(p, i, x, y);
	else if (axis == 'x')
		set_y_axis_direction(p, i, x, y);
}

void	set_y_axis_direction(t_mlx *p, int i, int x, int y)
{
	if (valid_direction(p, x, y - p->en[i].depth))
	{
		set_target(p, i, x, y - p->en[i].depth);
		p->en[i].direction = 'N';
	}
	else if (valid_direction(p, x, y + p->en[i].depth))
	{
		set_target(p, i, x, y + p->en[i].depth);
		p->en[i].direction = 'S';
	}
	else
	{
		if (valid_direction(p, x - p->en[i].depth, y))
		{
			set_target(p, i, x - p->en[i].depth, y);
			p->en[i].direction = 'W';
		}
		else if (valid_direction(p, x + p->en[i].depth, y))
		{
			set_target(p, i, x + p->en[i].depth, y);
			p->en[i].direction = 'E';
		}
	}
}

void	set_x_axis_direction(t_mlx *p, int i, int x, int y)
{
	if (valid_direction(p, x - p->en[i].depth, y))
	{
		set_target(p, i, x - p->en[i].depth, y);
		p->en[i].direction = 'W';
	}
	else if (valid_direction(p, x + p->en[i].depth, y))
	{
		set_target(p, i, x + p->en[i].depth, y);
		p->en[i].direction = 'E';
	}
	else
	{
		if (valid_direction(p, x, y - p->en[i].depth))
		{
			set_target(p, i, x, y - p->en[i].depth);
			p->en[i].direction = 'N';
		}
		else if (valid_direction(p, x, y + p->en[i].depth))
		{
			set_target(p, i, x, y + p->en[i].depth);
			p->en[i].direction = 'S';
		}
	}
}

void	set_target(t_mlx *p, int i, int x, int y)
{
	p->en[i].tg_x = x;
	p->en[i].tg_y = y;
}

int	valid_direction(t_mlx *p, int x, int y)
{
	return (
		y > 0 && y < p->height && x > 0 && x < p->width && p->map[y][x] != '1');
}
