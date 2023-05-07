/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:37:29 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/07 17:50:38 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* BFS */
int		ft_bfs(t_mlx *p);
int		ft_bfs_search(t_mlx *p);
int		valid(t_mlx *p, int x, int y);
char	**ft_malloc_bfs(t_mlx *p);
void	ft_free_bfs(t_mlx *p);

/*					lt, dn, rt, up
	int	vect_x[] = { -1, 0, 1, 0 };
	int	vect_y[] = { 0, -1, 0, 1 };
*/
int	ft_bfs(t_mlx *p)
{
	p->bfs.vect_x[0] = -1;
	p->bfs.vect_x[1] = 0;
	p->bfs.vect_x[2] = 1;
	p->bfs.vect_x[3] = 0;
	p->bfs.vect_y[0] = 0;
	p->bfs.vect_y[1] = -1;
	p->bfs.vect_y[2] = 0;
	p->bfs.vect_y[3] = 1;
	p->bfs.x = 0;
	p->bfs.y = 0;
	p->bfs.nxt_x = 0;
	p->bfs.nxt_y = 0;
	p->bfs.fr = 0;
	p->bfs.rr = 0;
	if (ft_malloc_bfs(p) == NULL)
		ft_free_and_destroy(p, 1, "Error allocating memory for BFS.\n");
	p->bfs.visited[p->pos.cur_y][p->pos.cur_x] = 'v';
	p->bfs.queue_x[p->bfs.rr] = p->pos.cur_x;
	p->bfs.queue_y[p->bfs.rr] = p->pos.cur_y;
	p->bfs.rr++;
	return (ft_bfs_search(p));
}

int	ft_bfs_search(t_mlx *p)
{
	int		i;

	while (p->bfs.fr < p->bfs.rr)
	{
		p->bfs.x = p->bfs.queue_x[p->bfs.fr];
		p->bfs.y = p->bfs.queue_y[p->bfs.fr];
		p->bfs.fr++;
		if (p->bfs.x == p->pos.ex_x && p->bfs.y == p->pos.ex_y)
			return (1);
		i = -1;
		while (++i < 4)
		{
			p->bfs.nxt_x = p->bfs.x + p->bfs.vect_x[i];
			p->bfs.nxt_y = p->bfs.y + p->bfs.vect_y[i];
			if (valid(p, p->bfs.nxt_x, p->bfs.nxt_y) == 1
				&& p->bfs.visited[p->bfs.nxt_y][p->bfs.nxt_x] != 'v')
			{
				p->bfs.visited[p->bfs.nxt_y][p->bfs.nxt_x] = 'v';
				p->bfs.queue_x[p->bfs.rr] = p->bfs.nxt_x;
				p->bfs.queue_y[p->bfs.rr] = p->bfs.nxt_y;
				p->bfs.rr++;
			}
		}
	}
	return (0);
}

int	valid(t_mlx *p, int x, int y)
{
	if (x < 0 || y < 0 || x >= p->width || y >= p->height
		|| p->map[y][x] == '1')
		return (0);
	return (1);
}

char	**ft_malloc_bfs(t_mlx *p)
{
	int	i;
	int	j;

	p->bfs.visited = (char **)malloc(sizeof(char *) * (p->height));
	if (p->bfs.visited == NULL)
		return (NULL);
	i = -1;
	while (++i < p->height)
	{
		p->bfs.visited[i] = malloc(sizeof(char) * p->width);
		if (p->bfs.visited[i] == NULL)
			return (NULL);
	}
	i = -1;
	while (++i < p->height)
	{
		j = -1;
		while (++j < p->width)
			p->bfs.visited[i][j] = 'f';
	}
	p->bfs.queue_x = malloc(sizeof(int) * (p->height * p->width));
	p->bfs.queue_y = malloc(sizeof(int) * (p->height * p->width));
	if (p->bfs.queue_x == NULL || p->bfs.queue_y == NULL)
		return (NULL);
	return (p->bfs.visited);
}

void	ft_free_bfs(t_mlx *p)
{
	int	i;

	i = -1;
	if (p->bfs.visited)
	{
		while (++i < p->height)
			if (p->bfs.visited[i])
				free(p->bfs.visited[i]);
		free(p->bfs.visited);
	}
	if (p->bfs.queue_y)
		free(p->bfs.queue_y);
	if (p->bfs.queue_x)
		free(p->bfs.queue_x);
}

/*
void	print_bfs(t_mlx *p, t_bfs *b)
{
	int	j = -1;
	int	i = -1;
	while (++i < p->height)
	{
		j = -1;
		while (++j < p->width)
			printf("[%d]", p->bfs.visited[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("fr:'%d', rr:'%d'\t x:'%d', y:'%d'\tnxt_x:'%d', nxt_y:'%d'\n", 
		p->bfs.fr, p->bfs.rr, p->bfs.x, p->bfs.y, p->bfs.nxt_x, p->bfs.nxt_y);
}
*/