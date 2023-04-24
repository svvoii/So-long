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

void	ft_validating_map(t_mlx *ptrs);
int		ft_invalid_elements(char *raw_map);
void	ft_map_elements_check(t_mlx *ptrs, int h, int w);

void	ft_validating_map(t_mlx *ptrs)
{
	int	h;
	int	w;

	ptrs->w = 0;
	ptrs->h = 0;
	if (ft_invalid_elements(ptrs->raw))
		ft_free_and_destroy(ptrs, 1, "Error: Invalid map elements.\n");
	h = -1;
	ptrs->key = 0;
	ptrs->p = 0;
	ptrs->e = 0;
	ptrs->c_count = 0;
	ft_map_elements_check(ptrs, h, w);
	if (ptrs->p != 1)
		ft_free_and_destroy(ptrs, 1, "Error: Single player required.\n");
	if (ptrs->e != 1)
		ft_free_and_destroy(ptrs, 1, "Error: Single exit required.\n");
	if (!ptrs->c_count)
		ft_free_and_destroy(ptrs, 1, "Error: At least one collectable required.\n");
	ptrs->pos.x = ptrs->player_x * ptrs->tile;
	ptrs->pos.y = ptrs->player_y * ptrs->tile;
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

void	ft_map_elements_check(t_mlx *ptrs, int h, int w)
{
	while (++h < ptrs->height)
	{
		w = -1;
		while (++w < ptrs->width)
		{
			if ((h == 0 || h == ptrs->height - 1) && ptrs->map[h][w] != '1')
				ft_free_and_destroy(ptrs, 1, "Error: Make sure the map wals are complete.\n");
			else if ((w == 0 || w == ptrs->width - 1) && ptrs->map[h][w] != '1')
				ft_free_and_destroy(ptrs, 1, "Error: Make sure the map wals are complete.\n");
			if (ptrs->map[h][w] == 'P')
			{
				ptrs->player_y = h;
				ptrs->player_x = w;
				ptrs->p++;
			}
			else if (ptrs->map[h][w] == 'E')
			{
				ptrs->e_y = h;
				ptrs->e_x = w;
				ptrs->e++;
			}
			else if (ptrs->map[h][w] == 'C')
				ptrs->c_count++;
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
