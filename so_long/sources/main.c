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
#define MAP_WIDTH 41 // x
#define MAP_HEIGHT 14 // y

typedef struct s_mlx_ptr
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_game
{
	t_mlx	*ptr;
	int		c_count;
	int		p_x;
	int		p_y;
}	t_game;

// using MAX_HEIGHT + 1 because the drawing of the top row wont show in the game window
char	map[MAP_HEIGHT][MAP_WIDTH] = {0};

void	load_map(char *filename);
int		ft_fgetc(FILE *stream);
int		draw_map(t_mlx *ptrs);
void	ft_file_to_image(t_mlx *ptrs, char *xpm_path, int w_tile, int h_tile);
void	ft_init_game_elements(t_game *game);
int		handle_input(int key, t_game *game);

int	main(int ac, char **av)
{
	t_mlx	ptrs;
	t_game	game;

	if (ac != 2)
		return(0);
	game.ptr = &ptrs;
	load_map(av[ac - 1]);
	ptrs.mlx = mlx_init();
	ptrs.win = mlx_new_window(ptrs.mlx, TILE_SIZE * MAP_WIDTH, TILE_SIZE * MAP_HEIGHT, "Game");
	ft_init_game_elements(&game);
	mlx_hook(ptrs.win, 2, 0, handle_input, &game);
	mlx_loop_hook(ptrs.mlx, draw_map, &ptrs);

	// The following loop allows to process 'events'
	mlx_loop(ptrs.mlx);

	return (0);
}

void	ft_init_game_elements(t_game *game)
{
	int	h;
	int	w;

	h = -1;
	while (++h < MAP_HEIGHT)
	{
		w = -1;
		while (++w < MAP_WIDTH)
		{
			if (map[h][w] == 'p')
			{
				game->p_y = h;
				game->p_x = w;
			}
			if (map[h][w] == 'c')
				game->c_count++;
		}
	}
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
	int	h;
	int	w;
	int	w_tile;
	int	h_tile;

	h = -1;
	while (++h < MAP_HEIGHT)
	{
		w = -1;
		while (++w < MAP_WIDTH)
		{
			w_tile = w * TILE_SIZE;
			h_tile = h * TILE_SIZE;
			if (map[h][w] == '1')
				ft_file_to_image(ptrs, "./xpm/1wall.xpm", w_tile, h_tile);
			else if (map[h][w] == '0')
				ft_file_to_image(ptrs, "./xpm/1ground.xpm", w_tile, h_tile);
			else if (map[h][w] == 'p')
				ft_file_to_image(ptrs, "./xpm/1player.xpm", w_tile, h_tile);
			else if (map[h][w] == 'c')
				ft_file_to_image(ptrs, "./xpm/1collectable.xpm", w_tile, h_tile);
			else if (map[h][w] == 'e')
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
}

int	handle_input(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	if (key == 65307)
		exit(0);
	new_x = game->p_x;
	new_y = game->p_y;
	if (key == 65361)
		new_x--;
	else if (key == 65363)
		new_x++;
	else if (key == 65362)
		new_y++;
	else if (key == 65364)
		new_y--;
	if (new_x >= 0 && new_x < MAP_WIDTH && new_y >= 0 && new_y < MAP_HEIGHT && map[new_y][new_x] != '1')
	{
		map[game->p_y][game->p_x] = '0';
		game->p_x = new_x;
		game->p_y = new_y;
		if (map[new_y][new_x] == 'c')
			map[new_y][new_x] = '0';
		else if (map[new_y][new_x] == 'e')
			exit(0);
		map[game->p_y][game->p_x] = 'p';
	}
	return (0);
}
/* This draw the letters on the map instead of images
int	draw_map(t_mlx *ptrs)
{
	void	*mlx;
	void	*win;
	int	h;
	int	w;
	int	w_tile;
	int	h_tile;

	mlx = ptrs->mlx;
	win = ptrs->win;
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