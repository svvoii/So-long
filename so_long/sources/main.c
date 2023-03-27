/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/03/27 17:44:48 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
//#include "../includes/mlx/mlx.h"

#define TILE_SIZE 32
#define MAP_WIDTH 20 // x
#define MAP_HEIGHT 15 // y

char	map[MAP_HEIGHT][MAP_WIDTH] = {0};
int		player_x = 1;
int		player_y = 4;

void	load_map(char *filename);
int		ft_fgetc(FILE *stream);
int		draw_map(void *mlx, void *win);
int		handle_input(int key, void *user_data); /* cann add user_data structure to show collectables count, for example */

int	main(int ac, char **av)
{
	void	*mlx_ptr;
	void	*win_ptr;

	//load_map("../maps/map.ber");
	load_map(av[ac - 1]);
	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			printf("%c ", map[h][w]);
		}
		printf("\n");
	}
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, TILE_SIZE * MAP_HEIGHT, TILE_SIZE * MAP_WIDTH, "Game");
	mlx_hook(win_ptr, 2, 0, handle_input, NULL);
	mlx_loop_hook(mlx_ptr, draw_map, mlx_ptr);

	// The following loop allows to process 'events'
	//mlx_loop(mlx_ptr);

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
		//printf("c: '%c'\t", c);
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

int	draw_map(void *mlx, void *win)
{
	int	h;
	int	w;
	int	w_tile;
	int	h_tile;

	mlx_clear_window(mlx, win);
	h = -1;
	w = -1;
	while (++h < MAP_HEIGHT)
	{
		while (++w < MAP_WIDTH)
		{
			w_tile = w * TILE_SIZE;
			h_tile = h * TILE_SIZE;
			if (map[h][w] == '1')
				mlx_string_put(mlx, win, w_tile, h_tile, 0xFFFFFF, "X");
			else if (map[h][w] == '0')
				mlx_string_put(mlx, win, w_tile, h_tile, 0xCCCCCC, ".");
			else if (map[h][w] == 'p')
				mlx_string_put(mlx, win, w_tile, h_tile, 0x00FF00, "P");
			else if (map[h][w] == 'c')
				mlx_string_put(mlx, win, w_tile, h_tile, 0xFFDD00, "C");
			else if (map[h][w] == 'e')
				mlx_string_put(mlx, win, w_tile, h_tile, 0xFF0000, "E");
		}
	}
	return (0);
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
