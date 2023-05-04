/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:43:40 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/04 17:06:38 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_map_to_array(t_mlx *p, char *file_path);
char	*ft_copy_to_buf(int fd);
void	ft_make_pix_map(t_mlx *p);
void	ft_set_mem_for_pixmap(t_mlx *p);
void	ft_fill_in_map(t_mlx *p, int w_pix, int h_pix, char c);

void	ft_map_to_array(t_mlx *p, char *file_path)
{
	int		fd;
	int		i;
	int		tmp;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return ;
	p->raw = ft_copy_to_buf(fd);
	close(fd);
	p->pix_map = NULL;
	p->map = ft_split(p->raw, '\n');
	i = 0;
	p->width = (int)ft_strlen(p->map[i]);
	while (p->map[++i])
	{
		tmp = (int)ft_strlen(p->map[i]);
		if (tmp != p->width)
			ft_free_and_destroy(p, 1, "Map rows length error.\n");
	}
	p->height = i;
	if (p->width == p->height)
		ft_free_and_destroy(p, 1, "Error: Map has to be rectangular.\n");
}

char	*ft_copy_to_buf(int fd)
{
	char	buff[BUFF_SIZE + 1];
	char	*map_str;
	char	*tmp;
	ssize_t	ret;

	map_str = ft_strdup("");
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buff, BUFF_SIZE);
		buff[ret] = '\0';
		tmp = ft_strjoin(map_str, buff);
		free(map_str);
		map_str = tmp;
	}
	if (ret == -1)
	{
		free(map_str);
		return (NULL);
	}
	return (map_str);
}

void	ft_make_pix_map(t_mlx *p)
{
	int	h;
	int	w;

	ft_set_mem_for_pixmap(p);
	h = -1;
	while (++h < p->height)
	{
		w = -1;
		while (++w < p->width)
		{
			if (p->map[h][w] == '0' || p->map[h][w] == 'P')
				ft_fill_in_map(p, w * PIX, h * PIX, '0');
			else if (p->map[h][w] == 'E')
				ft_fill_in_map(p, w * PIX, h * PIX, 'E');
			else if (p->map[h][w] == 'C')
				ft_fill_in_map(p, w * PIX, h * PIX, 'C');
		}
	}
}

void	ft_set_mem_for_pixmap(t_mlx *p)
{
	int	i;
	int	j;
	int	height;
	int	width;

	height = (p->height * PIX);
	width = (p->width * PIX);
	p->pix_map = (char **)malloc(sizeof(char *) * height);
	if (!p->pix_map)
		ft_free_and_destroy(p, 1, "Malloc error.\n");
	i = -1;
	while (++i < height)
	{
		p->pix_map[i] = (char *)malloc(sizeof(char) * width);
		if (!p->pix_map[i])
			ft_free_and_destroy(p, 1, "Malloc error.\n");
		j = -1;
		while (++j < width - 1)
			p->pix_map[i][j] = '1';
		p->pix_map[i][j] = '\0';
	}
}

void	ft_fill_in_map(t_mlx *p, int w_pix, int h_pix, char c)
{
	int	y;
	int	x;

	y = -1;
	while (++y < PIX)
	{
		x = -1;
		while (++x < PIX)
			p->pix_map[h_pix + y][w_pix + x] = c;
	}
}
