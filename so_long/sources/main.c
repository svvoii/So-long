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

//void	load_map(char *filename);
//int		ft_fgetc(FILE *stream);
void	ft_load_textures(t_mlx *ptr);
int		draw_map(t_mlx *ptrs);
void	ft_free_textures(t_mlx *ptrs);
void	ft_init_game_elements(t_game *game);
int		handle_input(int key, t_game *game);
void	ft_free_map(t_map *m);

int	main(int ac, char **av)
{
	t_mlx		ptrs;
	t_game		game;
	t_map		m;
	t_textures	tiles;

	if (ac != 2)
		return(0);
	game.ptr = &ptrs;
	game.m = &m;
	ptrs.m = &m;
	ptrs.t = &tiles;
	ft_map_to_array(&m, av[ac - 1]);

	//printf("%s\n", ptrs.m->raw);
	int i = -1;
	while (ptrs.m->map[++i])
		printf("'%s'\t'%d'\twidth:'%d'\theight:'%d'\ttile:'%d'\n", ptrs.m->map[i], i, ptrs.m->width, ptrs.m->height, ptrs.m->tile);

	ptrs.mlx = mlx_init();
	ptrs.win = mlx_new_window(ptrs.mlx, (m.tile * m.width), (m.tile * m.height), "Game");
	ft_init_game_elements(&game);

	printf("w:'%p'\tg:'%p'\tp:'%p'\tc:'%p'\te:'%p'\n", tiles.wall, tiles.path, tiles.player, tiles.collectable, tiles.exit);
	ft_load_textures(&ptrs);
	printf("w:'%p'\tg:'%p'\tp:'%p'\tc:'%p'\te:'%p'\n", tiles.wall, tiles.path, tiles.player, tiles.collectable, tiles.exit);

	mlx_hook(ptrs.win, KeyPress, KeyPressMask, handle_input, &game);
	mlx_loop_hook(ptrs.mlx, draw_map, &ptrs);
	mlx_loop(ptrs.mlx);

	//ft_free_textures(&ptrs);
	//mlx_destroy_window(ptrs.mlx, ptrs.win);
	//mlx_destroy_display(ptrs.mlx);
	//free(ptrs.mlx);
	ft_free_map(&m);

	return (0);
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

void	ft_load_textures(t_mlx *ptr)
{
	ptr->t->wall = mlx_xpm_file_to_image(ptr->mlx, "./xpm/1wall.xpm", &ptr->m->tile, &ptr->m->tile);
	ptr->t->path = mlx_xpm_file_to_image(ptr->mlx, "./xpm/1ground.xpm", &ptr->m->tile, &ptr->m->tile);
	ptr->t->player = mlx_xpm_file_to_image(ptr->mlx, "./xpm/1player.xpm", &ptr->m->tile, &ptr->m->tile);
	ptr->t->collectable = mlx_xpm_file_to_image(ptr->mlx, "./xpm/1collectable.xpm", &ptr->m->tile, &ptr->m->tile);
	ptr->t->exit = mlx_xpm_file_to_image(ptr->mlx, "./xpm/1exit.xpm", &ptr->m->tile, &ptr->m->tile);
}

void	ft_free_textures(t_mlx *ptrs)
{
	mlx_destroy_image(ptrs->mlx, ptrs->t->wall);
	mlx_destroy_image(ptrs->mlx, ptrs->t->path);
	mlx_destroy_image(ptrs->mlx, ptrs->t->player);
	mlx_destroy_image(ptrs->mlx, ptrs->t->collectable);
	mlx_destroy_image(ptrs->mlx, ptrs->t->exit);
}

int	draw_map(t_mlx *ptrs)
{
	int			h;
	int			w;
	int			w_tile;
	int			h_tile;

	//printf("w:'%p'\tg:'%p'\tp:'%p'\tc:'%p'\te:'%p'\n", ptrs->t->wall, ptrs->t->path, ptrs->t->player, ptrs->t->collectable, ptrs->t->exit);
	h = -1;
	while (++h < ptrs->m->height)
	{
		w = -1;
		while (++w < ptrs->m->width)
		{
			w_tile = w * ptrs->m->tile;
			h_tile = h * ptrs->m->tile;
			if (ptrs->m->map[h][w] == '1')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->t->wall, w_tile, h_tile);
			else if (ptrs->m->map[h][w] == '0')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->t->path, w_tile, h_tile);
			else if (ptrs->m->map[h][w] == 'p')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->t->player, w_tile, h_tile);
			else if (ptrs->m->map[h][w] == 'c')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->t->collectable, w_tile, h_tile);
			else if (ptrs->m->map[h][w] == 'e')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->t->exit, w_tile, h_tile);
		}
	}
	//ft_free_textures(ptrs);
	return (0);
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

void	ft_free_map(t_map *m)
{
	int	i;

	free(m->raw);
	i = -1;
	while (m->map[++i])
		free(m->map[i]);
	free(m->map[i]);
	m->raw = NULL;
	m->map = NULL;
}
