/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:43:40 by sbocanci          #+#    #+#             */
/*   Updated: 2023/04/03 18:29:08by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_set_values(t_mlx *p);
void	ft_validating_map(t_mlx *p);
int		ft_invalid_elements(char *raw_map);
void	ft_map_elements_check(t_mlx *p, int h, int w);

bool	ft_bfs(t_mlx *p, t_bfs *bfs);
void	ft_free_bfs(t_mlx *p, t_bfs *bfs);

void	ft_set_values(t_mlx *p)
{
	p->key = 0;
	p->pos.x = p->pos.cur_x * p->tile;
	p->pos.y = p->pos.cur_y * p->tile;
	p->pos.prev_x = p->pos.cur_x;
	p->pos.prev_y = p->pos.cur_y;
}

void	ft_validating_map(t_mlx *p)
{
	int		h;
	int		w;
	t_bfs	bfs;
	bool	bfs_ret;

	bfs_ret = true;
	if (ft_invalid_elements(p->raw))
		ft_free_and_destroy(p, 1, "Error: Invalid map elements.\n");
	h = -1;
	p->player = 0;
	p->exit = 0;
	p->c_count = 0;
	ft_map_elements_check(p, h, w);
	if (p->player != 1)
		ft_free_and_destroy(p, 1, "Error: Single player required.\n");
	if (p->exit != 1)
		ft_free_and_destroy(p, 1, "Error: Single exit required.\n");
	if (!p->c_count)
		ft_free_and_destroy(p, 1, "Error: At least one collectable required.\n");
	bfs_ret = ft_bfs(p, &bfs);
	ft_free_bfs(p, &bfs);
	printf("bfs:'%d'\n", bfs_ret);
	if (!bfs_ret)
		ft_free_and_destroy(p, 1, "Error: No valid path from Player to Exit.\n");
	ft_set_values(p);
}

int	ft_invalid_elements(char *raw_map)
{
	int	i;

	i = -1;
	while(raw_map[++i])
	{
		if (raw_map[i] != W
			&& raw_map[i] != G
			&& raw_map[i] != P
			&& raw_map[i] != E
			&& raw_map[i] != C
			&& raw_map[i] != '\n')
			return (1);
	}
	return (0);
}

void	ft_map_elements_check(t_mlx *p, int h, int w)
{
	while (++h < p->height)
	{
		w = -1;
		while (++w < p->width)
		{
			if ((h == 0 || h == p->height - 1) && p->map[h][w] != '1')
				ft_free_and_destroy(p, 1, "Error: Make sure the map wals are complete.\n");
			else if ((w == 0 || w == p->width - 1) && p->map[h][w] != '1')
				ft_free_and_destroy(p, 1, "Error: Make sure the map wals are complete.\n");
			if (p->map[h][w] == 'P')
			{
				p->pos.cur_y = h;
				p->pos.cur_x = w;
				p->player++;
			}
			else if (p->map[h][w] == 'E')
			{
				p->pos.ex_y = h;
				p->pos.ex_x = w;
				p->exit++;
			}
			else if (p->map[h][w] == 'C')
				p->c_count++;
		}
	}
}

/* BFS */
void	print_bfs(t_mlx *p, t_bfs *bfs);
int		ft_malloc_bfs(t_mlx *p, t_bfs *bfs);
bool	ft_is_valid(t_mlx *p, int x, int y);

bool	ft_bfs(t_mlx *p, t_bfs *bfs)
{
	int		i;
	int		j;

	bfs->x = 0;
	bfs->y = 0;
	bfs->next_x = 0;
	bfs->next_y = 0;
	bfs->fr = 0;
	bfs->rr = 0;

	i = ft_malloc_bfs(p, bfs);
	printf("ret i:'%d'\n", i);
	//if (ft_malloc_bfs(p, bfs) == 0);
	if (i != 1)
	{
		ft_free_bfs(p, bfs);
		ft_free_and_destroy(p, 1, "Error allocating memory for BFS.\n");
	}
	printf("BFS check\tp_x: '%d', p_y: '%d'\te_x: '%d', e_y:'%d'\n", p->pos.cur_x, p->pos.cur_y, p->pos.ex_x, p->pos.ex_y);

	i = -1;
	while (++i < p->height)
	{
		j = -1;
		while (++j < p->width)
			bfs->visited[i][j] = false;
	}

	bfs->visited[p->pos.cur_y][p->pos.cur_x] = true;

	bfs->queue_x[bfs->rr] = p->pos.cur_x;
	bfs->queue_y[bfs->rr] = p->pos.cur_y;
	bfs->rr++;

	print_bfs(p, bfs);

	while (bfs->fr < bfs->rr)
	{
		bfs->x = bfs->queue_x[bfs->fr];
		bfs->y = bfs->queue_y[bfs->fr];
		bfs->fr++;

		if (bfs->x == p->pos.ex_x && bfs->y == p->pos.ex_y)
			return (true);
		//				lt, up, rt, dn
		int	vect_x[] = { -1, 0, 1, 0 };
		int	vect_y[] = { 0, -1, 0, 1 };
		i = -1;
		while (++i < 4)
		{
			int	next_x = bfs->x + vect_x[i];
			int	next_y = bfs->y + vect_y[i];

			if (ft_is_valid(p, next_x, next_y) && !bfs->visited[next_y][next_x])
			{
				bfs->visited[next_y][next_x] = true;
				bfs->queue_x[bfs->rr] = next_x;
				bfs->queue_y[bfs->rr] = next_y;
				bfs->rr++;
			}
		}
		print_bfs(p, bfs);
	}
	return (false);
}

int	ft_malloc_bfs(t_mlx *p, t_bfs *bfs)
{
	int	i;

	bfs->visited = (bool **)malloc(sizeof(bool *) * (p->height));
	if (bfs->visited == NULL)
	{
		printf("visited @ '%p'\n", bfs->visited);
		return (0);
	}
	i = -1;
	while (++i < p->height)
	{
		bfs->visited[i] = malloc(sizeof(bool) * p->width);
		if (bfs->visited[i] == NULL)
		{
			printf("vis[%d] @ '%p'\n", i, bfs->visited[i]);
			return (0);
		}
	}
	bfs->queue_x = malloc(sizeof(int) * (p->height * p->width));
	bfs->queue_y = malloc(sizeof(int) * (p->height * p->width));
	if (bfs->queue_x == NULL || bfs->queue_y == NULL)
	{
		printf("queue_x @ '%p'\n", bfs->queue_x);
		printf("queue_y @ '%p'\n", bfs->queue_y);
		return (0);
	}
	return (1);
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

bool	ft_is_valid(t_mlx *p, int x, int y)
{
	if (x < 0 || y < 0 || x >= p->width || y >= p->height || p->map[y][x] == '1')
		return (false);
	return (true);
}

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

	printf("fr:'%d', rr:'%d'\t x:'%d', y:'%d'\tnext_x:'%d', next_y:'%d'\n", b->fr, b->rr, b->x, b->y, b->next_x, b->next_y);
}
 
/*
char	*load_map(char *file_path)
{
	char	*buff;
	int		fd;
	int		ret;
	int		i;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buff)
	{
		close(fd);
		return (NULL);
	}
	ret = read(fd, buff, BUFF_SIZE);
	if (ret == -1)
	{
		close(fd);
		free(buff);
		return (NULL);
	}
	buff[ret] = '\0';
	close(fd);
	return (buff);
}

// this will return the file size in bytes
off_t	ft_get_file_size(char *file_name)
{
	char	buf[4096];
	ssize_t	nread;
	off_t	size;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_file_error("Error. Could not open the file", file_name);
		return (-1);
	}
	size = 0;
	while (1)
	{
		nread = read(fd, buf, sizeof(buf));
		if (nread <= 0)
			break;
		size += nread;
	}
	close(fd);
	return (size);
}
*/
