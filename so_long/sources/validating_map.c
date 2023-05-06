/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:43:40 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/06 14:58:27 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
void	ft_set_values(t_mlx *p);
void	ft_validating_map(t_mlx *p);
int		ft_invalid_elements(char *raw_map);
void	ft_map_elements_check(t_mlx *p, int h, int w);
void	calculate_map_elements(t_mlx *p, char c);
*/
void	ft_set_values(t_mlx *p)
{
	int	i;

	p->moves = 0;
	p->key = 0;
	p->pos.x = p->pos.cur_x * PIX;
	p->pos.y = p->pos.cur_y * PIX;
	p->pos.prev_x = p->pos.cur_x;
	p->pos.prev_y = p->pos.cur_y;
	p->pos.step = PLAYER_SPEED;
	p->game_over = 0;
	i = -1;
	while (++i < ENEMIES_COUNT)
	{
		p->en[i].x = 0;
		p->en[i].y = 0;
		p->en[i].st_x = 0;
		p->en[i].st_y = 0;
		p->en[i].tg_x = 0;
		p->en[i].tg_y = 0;
		p->en[i].pix_x = 0;
		p->en[i].pix_y = 0;
		p->en[i].depth = 0;
		p->en[i].step = 0;
	}
}

void	ft_validating_map(t_mlx *p)
{
	if (ft_invalid_elements(p->raw))
		ft_free_and_destroy(p, 1, "Error: Invalid map elements.\n");
	ft_map_elements_check(p);
	calculate_map_elements(p, '0');
	calculate_map_elements(p, 'P');
	calculate_map_elements(p, 'E');
	printf("coins:'%d', ground:'%d', exit:'%d'\n", p->c_count, p->ground, p->exit);
	if (p->player != 1)
		ft_free_and_destroy(p, 1, "Error: Single player required.\n");
	if (p->exit != 1)
		ft_free_and_destroy(p, 1, "Error: Single exit required.\n");
	if (!p->c_count)
		ft_free_and_destroy(p, 1, "Error: At least one collectable required.\n");
	if (ft_bfs(p) == 0)
		ft_free_and_destroy(p, 1, "Error: No valid path from Player to Exit.\n");
	ft_set_values(p);
}

int	ft_invalid_elements(char *raw_map)
{
	int	i;

	printf("raw map\n");
	if (raw_map[0] != '1' && raw_map[0] != '0')
		return (1);
	i = -1;
	while (raw_map[++i])
	{
		printf("%d ", raw_map[i]);
		if (i > 0 && raw_map[i] == '\n' && raw_map[i - 1] == '\n')
			return (1);
		if (raw_map[i] != '1' && raw_map[i] != '0'
			&& raw_map[i] != 'P' && raw_map[i] != 'E'
			&& raw_map[i] != 'C' && raw_map[i] != '\n')
			return (1);
	}
	printf("\n");
	return (0);
}

void	ft_map_elements_check(t_mlx *p)
{
	int		y;
	int		x;

	y = -1;
	x = -1;
	p->player = 0;
	p->exit = 0;
	p->c_count = 0;
	p->ground = 0;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
		{
			if (p->map[y][x] == 'C')
				p->c_count++;
			if ((y == 0 || y == p->height - 1) && p->map[y][x] != '1')
				ft_free_and_destroy(p, 1, "Error: Map wals must be complete.\n");
			if ((x == 0 || x == p->width - 1) && p->map[y][x] != '1')
				ft_free_and_destroy(p, 1, "Error: Map wals must be complete.\n");
		}
	}
}

void	calculate_map_elements(t_mlx *p, char c)
{
	int	x;
	int	y;

	y = -1;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
		{
			if ((y > 0 && y < p->height - 1) && c == '0' && p->map[y][x] == c)
				p->ground++;
			else if (c == 'E' && p->map[y][x] == c)
			{
				p->pos.ex_y = y;
				p->pos.ex_x = x;
				p->exit++;
			}
			else if (c == 'P' && p->map[y][x] == c)
			{
				p->pos.cur_y = y;
				p->pos.cur_x = x;
				p->player++;
			}
		}
	}
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
