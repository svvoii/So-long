/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/03/30 14:54:27by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/so_long.h"
//#include "../includes/mlx/mlx.h"

#include <stdio.h>
#include "../includes/libft.h"
#include "../includes/mlx/mlx.h"
#include "../includes/mlx/mlx_int.h"

#define BUFF_SIZE 1024
#define PIX 32

typedef struct s_map
{
	char	*raw;
	char	**map;
	int		height;
	int		width;
	int		tile;
}	t_map;

typedef struct s_mlx_ptr
{
	void	*mlx;
	void	*win;
	void	*img;
	t_map	*m;
}	t_mlx;

typedef struct s_game
{
	t_mlx	*ptr;
	t_map	*m;
	int		c_count;
	int		p_x;
	int		p_y;
}	t_game;

void	*ft_map_to_array(t_map *m, char *file_path);
char	*ft_copy_to_buf(int fd);
int		draw_map(t_mlx *ptrs);
void	ft_file_to_image(t_mlx *ptrs, char *xpm_path, int w_tile, int h_tile);
void	ft_init_game_elements(t_game *game);
int		handle_input(int key, t_game *game);

int	main(int ac, char **av)
{
	t_mlx	ptrs;
	t_game	game;
	t_map	m;

	if (ac != 2)
		return(0);
	game.ptr = &ptrs;
	game.m = &m;
	ptrs.m = &m;
	ft_map_to_array(&m, av[ac - 1]);

	printf("%s\n", ptrs.m->raw);
	int i = -1;
	while (ptrs.m->map[++i])
		printf("'%s'\t'%d'\twidth:'%d'\theight:'%d'\ttile:'%d'\n", ptrs.m->map[i], i, ptrs.m->width, ptrs.m->height, ptrs.m->tile);

	ptrs.mlx = mlx_init();
	ptrs.win = mlx_new_window(ptrs.mlx, (m.tile * m.width), (m.tile * m.height), "Game");
	ft_init_game_elements(&game);
	mlx_hook(ptrs.win, KeyPress, KeyPressMask, handle_input, &game);
	mlx_loop_hook(ptrs.mlx, draw_map, &ptrs);
	mlx_loop(ptrs.mlx);

	mlx_destroy_window(ptrs.mlx, ptrs.win);
	mlx_destroy_display(ptrs.mlx);
	free(ptrs.mlx);

	return (0);
}

void	*ft_map_to_array(t_map *m, char *file_path)
{
	int		fd;
	int		i;
	int		tmp;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	m->raw = ft_copy_to_buf(fd);
	close(fd);
	m->map = ft_split(m->raw, '\n');
	i = 0;
	m->width = (int)ft_strlen(m->map[i]);
	while (m->map[++i])
	{
		tmp = (int)ft_strlen(m->map[i]);
		if (tmp != m->width)
		{
			// throw map error, free and exit
		}
	}
	m->height = i;
	m->tile = PIX;
}

char	*ft_copy_to_buf(int fd)
{
	char	buff[BUFF_SIZE + 1];
	char 	*map_str;
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
	return(map_str);
}

void	ft_init_game_elements(t_game *game)
{
	int	h;
	int	w;

	h = -1;
	while (++h < game->m->height)
	{
		w = -1;
		while (++w < game->m->width)
		{
			if (game->m->map[h][w] == 'p')
			{
				game->p_y = h;
				game->p_x = w;
			}
			if (game->m->map[h][w] == 'c')
				game->c_count++;
		}
	}
}

int	draw_map(t_mlx *ptrs)
{
	int	h;
	int	w;
	int	w_tile;
	int	h_tile;

	h = -1;
	while (++h < ptrs->m->height)
	{
		w = -1;
		while (++w < ptrs->m->width)
		{
			w_tile = w * ptrs->m->tile;
			h_tile = h * ptrs->m->tile;
			if (ptrs->m->map[h][w] == '1')
				ft_file_to_image(ptrs, "./xpm/1wall.xpm", w_tile, h_tile);
			else if (ptrs->m->map[h][w] == '0')
				ft_file_to_image(ptrs, "./xpm/1ground.xpm", w_tile, h_tile);
			else if (ptrs->m->map[h][w] == 'p')
				ft_file_to_image(ptrs, "./xpm/1player.xpm", w_tile, h_tile);
			else if (ptrs->m->map[h][w] == 'c')
				ft_file_to_image(ptrs, "./xpm/1collectable.xpm", w_tile, h_tile);
			else if (ptrs->m->map[h][w] == 'e')
				ft_file_to_image(ptrs, "./xpm/1exit.xpm", w_tile, h_tile);
		}
	}
	return (0);
}

void	ft_file_to_image(t_mlx *ptrs, char *xpm_path, int w_tile, int h_tile)
{
	void	*img_ptr;
	int		img_width = 0;
	int		img_height = 0;

	img_ptr = mlx_xpm_file_to_image(ptrs->mlx, xpm_path, &img_width, &img_height);
	if (img_ptr == NULL)
	{
		ft_putstr_fd("Error: Could not load .xpm file\n", 2);
		exit(EXIT_FAILURE);
	}
	mlx_put_image_to_window(ptrs->mlx, ptrs->win, img_ptr, w_tile, h_tile);
	free(img_ptr);
}

int	handle_input(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	printf("key:'%d'\n", key);
	if (key == 65307)
		exit(0);
	new_x = game->p_x;
	new_y = game->p_y;
	if (key == 65362 || key == 119) /* up */
		new_y--;
	else if (key == 65364 || key == 115) /* down */
		new_y++;
	else if (key == 65361 || key == 97) /* left */
		new_x--;
	else if (key == 65363 || key == 100) /* right */
		new_x++;
	if (new_x >= 0 && new_x < game->m->width && new_y >= 0 && new_y < game->m->height && game->m->map[new_y][new_x] != '1')
	{
		game->m->map[game->p_y][game->p_x] = '0';
		game->p_x = new_x;
		game->p_y = new_y;
		if (game->m->map[new_y][new_x] == 'c')
			game->m->map[new_y][new_x] = '0';
		else if (game->m->map[new_y][new_x] == 'e')
			exit(0);
		game->m->map[game->p_y][game->p_x] = 'p';
		//mlx_clear_window(game->ptr->mlx, game->ptr->win);
		//draw_map(game->ptr);
	}
	return (0);
}
