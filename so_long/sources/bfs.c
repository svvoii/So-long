/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:37:29 by sbocanci          #+#    #+#             */
/*   Updated: 2023/04/26 14:56:55 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* BFS */
bool	ft_bfs(t_mlx *p, t_bfs *bfs);
bool	ft_bfs_search(t_mlx *p, t_bfs *bfs);
bool	valid(t_mlx *p, int x, int y);
void	*ft_malloc_bfs(t_mlx *p, t_bfs *bfs);
void	ft_free_bfs(t_mlx *p, t_bfs *bfs);

/*					lt, dn, rt, up
	int	vect_x[] = { -1, 0, 1, 0 };
	int	vect_y[] = { 0, -1, 0, 1 };
*/
bool	ft_bfs(t_mlx *p, t_bfs *bfs)
{
	bfs->vect_x[0] = -1;
	bfs->vect_x[1] = 0;
	bfs->vect_x[2] = 1;
	bfs->vect_x[3] = 0;
	bfs->vect_y[0] = 0;
	bfs->vect_y[1] = -1;
	bfs->vect_y[2] = 0;
	bfs->vect_y[3] = 1;
	bfs->x = 0;
	bfs->y = 0;
	bfs->nxt_x = 0;
	bfs->nxt_y = 0;
	bfs->fr = 0;
	bfs->rr = 0;
	if (!ft_malloc_bfs(p, bfs))
	{
		ft_free_bfs(p, bfs);
		ft_free_and_destroy(p, 1, "Error allocating memory for BFS.\n");
	}
	bfs->visited[p->pos.cur_y][p->pos.cur_x] = true;
	bfs->queue_x[bfs->rr] = p->pos.cur_x;
	bfs->queue_y[bfs->rr] = p->pos.cur_y;
	bfs->rr++;
	return (ft_bfs_search(p, bfs));
}

bool	ft_bfs_search(t_mlx *p, t_bfs *b)
{
	int		i;

	while (b->fr < b->rr)
	{
		b->x = b->queue_x[b->fr];
		b->y = b->queue_y[b->fr];
		b->fr++;
		if (b->x == p->pos.ex_x && b->y == p->pos.ex_y)
			return (true);
		i = -1;
		while (++i < 4)
		{
			b->nxt_x = b->x + b->vect_x[i];
			b->nxt_y = b->y + b->vect_y[i];
			if (valid(p, b->nxt_x, b->nxt_y) && !b->visited[b->nxt_y][b->nxt_x])
			{
				b->visited[b->nxt_y][b->nxt_x] = true;
				b->queue_x[b->rr] = b->nxt_x;
				b->queue_y[b->rr] = b->nxt_y;
				b->rr++;
			}
		}
	}
	return (false);
}

bool	valid(t_mlx *p, int x, int y)
{
	if (x < 0 || y < 0 || x >= p->width || y >= p->height
		|| p->map[y][x] == '1')
		return (false);
	return (true);
}

void	*ft_malloc_bfs(t_mlx *p, t_bfs *bfs)
{
	int	i;
	int	j;

	bfs->visited = (bool **)malloc(sizeof(bool *) * (p->height));
	if (bfs->visited == NULL)
		return (NULL);
	i = -1;
	while (++i < p->height)
	{
		bfs->visited[i] = malloc(sizeof(bool) * p->width);
		if (bfs->visited[i] == NULL)
			return (NULL);
	}
	i = -1;
	while (++i < p->height)
	{
		j = -1;
		while (++j < p->width)
			bfs->visited[i][j] = false;
	}
	bfs->queue_x = malloc(sizeof(int) * (p->height * p->width));
	bfs->queue_y = malloc(sizeof(int) * (p->height * p->width));
	if (bfs->queue_x == NULL || bfs->queue_y == NULL)
		return (NULL);
}

void	ft_free_bfs(t_mlx *p, t_bfs *bfs)
{
	int	i;

	i = -1;
	if (bfs->visited)
	{
		while (++i < p->height)
			if (bfs->visited[i])
				free(bfs->visited[i]);
		free(bfs->visited);
	}
	if (bfs->queue_y)
		free(bfs->queue_y);
	if (bfs->queue_x)
		free(bfs->queue_x);
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
			printf("[%d]", b->visited[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("fr:'%d', rr:'%d'\t x:'%d', y:'%d'\tnxt_x:'%d', nxt_y:'%d'\n", 
		b->fr, b->rr, b->x, b->y, b->nxt_x, b->nxt_y);
}
*/