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

#include "../includes/so_long.h"
//#include "../includes/mlx/mlx.h"

#define TILE_SIZE 32
#define MAP_WIDTH 8 // x
#define MAP_HEIGHT 4 // y

typedef struct s_mlx_ptr
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

// using MAX_HEIGHT + 1 because the drawing of the top row wont show in the game window
char	map[MAP_HEIGHT][MAP_WIDTH] = {0};
int		player_x = 1;
int		player_y = 1;

void	load_map(char *filename);
int		ft_fgetc(FILE *stream);
int		draw_map(t_mlx *ptrs);
void	ft_file_to_image(t_mlx *ptrs, char *xpm_path, int w_tile, int h_tile);
void	ft_tile_w_h(int w, int h, int *w_tile, int *h_tile);
int		handle_input(int key, void *user_data); /* cann add user_data structure to show collectables count, for example */

int	main(int ac, char **av)
{
	t_mlx	ptrs;

	if (ac != 2)
		return(0);
	//load_map("../maps/map.ber");
	load_map(av[ac - 1]);
	// printing out the raw map inside terminat to verify it is okay
	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			printf("%c ", map[h][w]);
		}
		printf("\n");
	}
	ptrs.mlx_ptr = mlx_init();
	ptrs.win_ptr = mlx_new_window(ptrs.mlx_ptr, TILE_SIZE * MAP_WIDTH, TILE_SIZE * MAP_HEIGHT, "Game");
	mlx_hook(ptrs.win_ptr, 2, 0, handle_input, NULL);
	mlx_loop_hook(ptrs.mlx_ptr, draw_map, &ptrs);

	// The following loop allows to process 'events'
	mlx_loop(ptrs.mlx_ptr);

	return (0);
}

void	load_map(char *filename)
{
	int		row;
	int		col;
	char	c;

	FILE *fp = fopen(filename, "r");
	if (!fp)
	{
		ft_putstr_fd("Error: Could not open the file\n", 2);
		exit(EXIT_FAILURE);
	}
	row = 0;
	col = 0;
	while ((c = ft_fgetc(fp)) != EOF)
	{
		if (c == '\n')
		{
			row++;
			col = 0;
			continue;
		}
		map[row][col] = c;
		col++;
	}
	fclose(fp);
}

int	ft_fgetc(FILE *stream)
{
	unsigned char	c;

	if (fread(&c, 1, 1, stream) != 1)
		return (EOF);
	return ((int)c);
}

int	draw_map(t_mlx *ptrs)
{
	void	*mlx;
	void	*win;
	int	h;
	int	w;
	int	w_tile;
	int	h_tile;

	mlx = ptrs->mlx_ptr;
	win = ptrs->win_ptr;
	h = -1;
	while (++h < MAP_HEIGHT)
	{
		w = -1;
		while (++w < MAP_WIDTH)
		{
			ft_tile_w_h(w, h, &w_tile, &h_tile);
			if (map[h][w] == '1')
				ft_file_to_image(ptrs, "../xpm/wall.xpm", w_tile, h_tile);
			else if (map[h][w] == '0')
				ft_file_to_image(ptrs, "../xpm/ground.xpm", w_tile, h_tile);
			else if (map[h][w] == 'p')
				ft_file_to_image(ptrs, "../xpm/player.xpm", w_tile, h_tile);
			else if (map[h][w] == 'c')
				ft_file_to_image(ptrs, "../xpm/collectable.xpm", w_tile, h_tile);
			else if (map[h][w] == 'e')
				ft_file_to_image(ptrs, "../xpm/exit.xpm", w_tile, h_tile);
		}
	}
	return (0);
}

void	ft_file_to_image(t_mlx *ptrs, char *xpm_path, int w_tile, int h_tile)
{
	void	*img_ptr;
	int		img_width;
	int		img_height;
	int		x_pos;
	int		y_pos;

	img_ptr = mlx_xpm_file_to_image(ptrs->mlx_ptr, xpm_path, &img_width, &img_height);
	if (img_ptr == NULL)
	{
		ft_putstr_fd("Error: Could not load .xpm file\n", 2);
		exit(EXIT_FAILURE);
	}
	x_pos = w_tile * TILE_SIZE / img_width;
	y_pos = h_tile * TILE_SIZE / img_height;
	mlx_put_image_to_window(ptrs->mlx_ptr, ptrs->win_ptr, img_ptr, x_pos, y_pos);
}

void	ft_tile_w_h(int w, int h, int *w_tile, int *h_tile)
{
	if (w == 0)
		*w_tile = TILE_SIZE;
	else
		*w_tile = w * TILE_SIZE;
	if (h == 0)
		*h_tile = TILE_SIZE;
	else
		*h_tile = h * TILE_SIZE;
}

int	handle_input(int key, void *user_data)
{
	int	new_x;
	int	new_y;

	if (key == 53)
		exit(0);
	new_x = player_x;
	new_y = player_y;
	if (key == 123)
		new_x--;
	else if (key == 124)
		new_x++;
	else if (key == 125)
		new_y++;
	else if (key == 126)
		new_y--;
	if (new_x >= 0 && new_x < MAP_WIDTH && new_y >= 0 && new_y < MAP_HEIGHT && map[new_y][new_x] != '1')
	{
		map[player_y][player_x] = '0';
		player_x = new_x;
		player_y = new_y;
		if (map[new_y][new_x] == 'c')
			map[new_y][new_x] = '0';
		else if (map[new_y][new_x] == 'e')
			exit(0);
		map[player_y][player_x] = 'p';
	}
	return (0);
}
/*
int	draw_map(t_mlx *ptrs)
{
	void	*mlx;
	void	*win;
	int	h;
	int	w;
	int	w_tile;
	int	h_tile;

	mlx = ptrs->mlx_ptr;
	win = ptrs->win_ptr;
	h = -1;
	while (++h <= MAP_HEIGHT)
	{
		w = -1;
		while (++w < MAP_WIDTH)
		{
			w_tile = w * TILE_SIZE;
			h_tile = h * TILE_SIZE;
			if (map[h][w] == '1')
				mlx_string_put(mlx, win, w_tile, h_tile, 0xFFFFFF, "w");
			else if (map[h][w] == '0')
				mlx_string_put(mlx, win, w_tile, h_tile, 0xCCCCCC, " ");
			else if (map[h][w] == 'p')
				mlx_string_put(mlx, win, w_tile, h_tile, 0x00FF00, "p");
			else if (map[h][w] == 'c')
				mlx_string_put(mlx, win, w_tile, h_tile, 0xFFDD00, "c");
			else if (map[h][w] == 'e')
				mlx_string_put(mlx, win, w_tile, h_tile, 0xFF0000, "e");
		}
	}
	return (0);
}
*/