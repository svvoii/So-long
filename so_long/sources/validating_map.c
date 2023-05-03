/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:43:40 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/03 19:27:24 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_set_values(t_mlx *p);
void	ft_validating_map(t_mlx *p);
int		ft_invalid_elements(char *raw_map);
void	ft_map_elements_check(t_mlx *p, int h, int w);

void	ft_set_values(t_mlx *p)
{
	int	i;

	p->moves = 0;
	p->key = 0;
	p->pos.x = p->pos.cur_x * p->t;
	p->pos.y = p->pos.cur_y * p->t;
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
	int		h;
	int		w;
	t_bfs	bfs;

	if (ft_invalid_elements(p->raw))
		ft_free_and_destroy(p, 1, "Error: Invalid map elements.\n");
	h = -1;
	w = -1;
	p->player = 0;
	p->exit = 0;
	p->c_count = 0;
	p->ground = 0;
	ft_map_elements_check(p, h, w);
	calculate_coins(p);
	if (p->player != 1)
		ft_free_and_destroy(p, 1, "Error: Single player required.\n");
	if (p->exit != 1)
		ft_free_and_destroy(p, 1, "Error: Single exit required.\n");
	if (!p->c_count)
		ft_free_and_destroy(p, 1, "Error: At least one collectable required.\n");
	if (ft_bfs(p, &bfs) == 0)
		ft_free_bfs(p, &bfs, "Error: No valid path from Player to Exit.\n");
	ft_set_values(p);
}

int	ft_invalid_elements(char *raw_map)
{
	int	i;

	i = -1;
	while (raw_map[++i])
	{
		if (raw_map[i] != '1'
			&& raw_map[i] != '0'
			&& raw_map[i] != 'P'
			&& raw_map[i] != 'E'
			&& raw_map[i] != 'C'
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
				ft_free_and_destroy(p, 1, "Error: Map wals must be complete.\n");
			else if ((w == 0 || w == p->width - 1) && p->map[h][w] != '1')
				ft_free_and_destroy(p, 1, "Error: Map wals must be complete.\n");
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
			else if (p->map[h][w] == '0')
				p->ground++;
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
