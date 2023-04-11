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

void	ft_init_map_and_window(t_mlx *ptrs, char *str);
void	ft_load_textures(t_mlx *ptr);
int		ft_draw_map(t_mlx *ptrs);
void	ft_init_game_elements(t_mlx *ptrs);
int		ft_handle_input(int key, t_mlx *ptrs);

int	main(int ac, char **av)
{
	t_mlx		ptrs;

	if (ac != 2)
		return(0);
	ft_init_map_and_window(&ptrs, av[ac - 1]);

	int i = -1;
	while (ptrs.map[++i])
		printf("'%s'\t'%d'\twidth:'%d'\theight:'%d'\ttile:'%d'\n", ptrs.map[i], i, ptrs.width, ptrs.height, ptrs.tile);

	mlx_hook(ptrs.win, KeyPress, KeyPressMask, ft_handle_input, &ptrs);
	mlx_loop_hook(ptrs.mlx, ft_draw_map, &ptrs);
	mlx_loop(ptrs.mlx);

	//ft_free_and_destroy(&ptrs, 0);
	//return (0);
}

void	ft_init_map_and_window(t_mlx *ptrs, char *str)
{
	ft_map_to_array(ptrs, str); // opening file and storing the map data both in str and 2d arr.
	ft_validating_map(ptrs);
	ptrs->mlx = mlx_init();
	ptrs->win = mlx_new_window(ptrs->mlx, (ptrs->tile * ptrs->width), (ptrs->tile * ptrs->height), "Game");
	ft_load_textures(ptrs); // assign each sprite handle to its respective pointer
}

void	ft_load_textures(t_mlx *ptr)
{
	ptr->wall = mlx_xpm_file_to_image(ptr->mlx, "./xpm/wall_vines.xpm", &ptr->tile, &ptr->tile);
	ptr->path = mlx_xpm_file_to_image(ptr->mlx, "./xpm/ground.xpm", &ptr->tile, &ptr->tile);
	ptr->player = mlx_xpm_file_to_image(ptr->mlx, "./xpm/human.xpm", &ptr->tile, &ptr->tile);
	ptr->collectable = mlx_xpm_file_to_image(ptr->mlx, "./xpm/coin_01.xpm", &ptr->tile, &ptr->tile);
	ptr->exit = mlx_xpm_file_to_image(ptr->mlx, "./xpm/stone_arch.xpm", &ptr->tile, &ptr->tile);
}

int	ft_draw_map(t_mlx *ptrs)
{
	int			h;
	int			w;
	int			w_tile;
	int			h_tile;

	h = -1;
	while (++h < ptrs->height)
	{
		w = -1;
		while (++w < ptrs->width)
		{
			w_tile = w * ptrs->tile;
			h_tile = h * ptrs->tile;
			if (ptrs->map[h][w] == '1')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->wall, w_tile, h_tile);
			else if (ptrs->map[h][w] == '0')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->path, w_tile, h_tile);
			else if (ptrs->map[h][w] == 'P')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->player, w_tile, h_tile);
			else if (ptrs->map[h][w] == 'C')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->collectable, w_tile, h_tile);
			else if (ptrs->map[h][w] == 'E')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->exit, w_tile, h_tile);
		}
	}
	return (0);
}

int	ft_handle_input(int key, t_mlx *ptrs)
{
	int	new_x;
	int	new_y;

	printf("key:'%d'\n", key);
	if (key == 65307)
		ft_free_and_destroy(ptrs, 0, NULL);
	new_x = ptrs->p_x;
	new_y = ptrs->p_y;
	if (key == 65362 || key == 119) /* up */
		new_y--;
	else if (key == 65364 || key == 115) /* down */
		new_y++;
	else if (key == 65361 || key == 97) /* left */
		new_x--;
	else if (key == 65363 || key == 100) /* right */
		new_x++;
	if (new_x >= 0 && new_x < ptrs->width && new_y >= 0 && new_y < ptrs->height && ptrs->map[new_y][new_x] != '1')
	{
		ptrs->map[ptrs->p_y][ptrs->p_x] = '0';
		ptrs->p_x = new_x;
		ptrs->p_y = new_y;
		if (ptrs->map[new_y][new_x] == 'C')
			ptrs->map[new_y][new_x] = '0';
		else if (ptrs->map[new_y][new_x] == 'E')
			ft_free_and_destroy(ptrs, 0, NULL);
		ptrs->map[ptrs->p_y][ptrs->p_x] = 'P';
		//mlx_clear_window(game->ptr->mlx, game->ptr->win);
		//ft_draw_map(game->ptr);
	}
	return (0);
}
