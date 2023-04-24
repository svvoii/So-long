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

void	ft_validating_map(t_mlx *p);
int		ft_invalid_elements(char *raw_map);
void	ft_map_elements_check(t_mlx *p, int h, int w);

void	ft_validating_map(t_mlx *p)
{
	int	h;
	int	w;

	p->w = 0;
	p->h = 0;
	if (ft_invalid_elements(p->raw))
		ft_free_and_destroy(p, 1, "Error: Invalid map elements.\n");
	h = -1;
	p->key = 0;
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
	p->pos.x = p->pos.cur_x * p->tile;
	p->pos.y = p->pos.cur_y * p->tile;
	p->pos.prev_x = p->pos.cur_x;
	p->pos.prev_y = p->pos.cur_y;
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
