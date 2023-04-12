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

void	ft_load_player_frames(t_mlx *ptr)
{
	ptr->p_up[0] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_up_00.xpm", &ptr->tile, &ptr->tile);
	ptr->p_up[1] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_up_01.xpm", &ptr->tile, &ptr->tile);
	ptr->p_up[2] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_up_02.xpm", &ptr->tile, &ptr->tile);
	ptr->p_up[3] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_up_03.xpm", &ptr->tile, &ptr->tile);
	ptr->p_up[4] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_up_04.xpm", &ptr->tile, &ptr->tile);
	ptr->p_up[5] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_up_05.xpm", &ptr->tile, &ptr->tile);
	ptr->p_down[0] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_down_00.xpm", &ptr->tile, &ptr->tile);
	ptr->p_down[1] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_down_01.xpm", &ptr->tile, &ptr->tile);
	ptr->p_down[2] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_down_02.xpm", &ptr->tile, &ptr->tile);
	ptr->p_down[3] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_down_03.xpm", &ptr->tile, &ptr->tile);
	ptr->p_down[4] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_down_04.xpm", &ptr->tile, &ptr->tile);
	ptr->p_down[5] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_down_05.xpm", &ptr->tile, &ptr->tile);
	ptr->p_left[0] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_left_00.xpm", &ptr->tile, &ptr->tile);
	ptr->p_left[1] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_left_01.xpm", &ptr->tile, &ptr->tile);
	ptr->p_left[2] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_left_02.xpm", &ptr->tile, &ptr->tile);
	ptr->p_left[3] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_left_03.xpm", &ptr->tile, &ptr->tile);
	ptr->p_left[4] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_left_04.xpm", &ptr->tile, &ptr->tile);
	ptr->p_left[5] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_left_05.xpm", &ptr->tile, &ptr->tile);
	ptr->p_right[0] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_right_00.xpm", &ptr->tile, &ptr->tile);
	ptr->p_right[1] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_right_01.xpm", &ptr->tile, &ptr->tile);
	ptr->p_right[2] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_right_02.xpm", &ptr->tile, &ptr->tile);
	ptr->p_right[3] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_right_03.xpm", &ptr->tile, &ptr->tile);
	ptr->p_right[4] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_right_04.xpm", &ptr->tile, &ptr->tile);
	ptr->p_right[5] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/cat_right_05.xpm", &ptr->tile, &ptr->tile);
}

void	ft_load_coin_frames(t_mlx *ptr)
{
	ptr->collectable[0] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/coin_00.xpm", &ptr->tile, &ptr->tile);
	ptr->collectable[1] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/coin_01.xpm", &ptr->tile, &ptr->tile);
	ptr->collectable[2] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/coin_02.xpm", &ptr->tile, &ptr->tile);
	ptr->collectable[3] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/coin_03.xpm", &ptr->tile, &ptr->tile);
	ptr->collectable[4] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/coin_04.xpm", &ptr->tile, &ptr->tile);
	ptr->collectable[5] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/coin_05.xpm", &ptr->tile, &ptr->tile);
}

void	ft_load_textures(t_mlx *ptr)
{
	ptr->wall[0] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/wall_vines.xpm", &ptr->tile, &ptr->tile);
	ptr->path[0] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/ground.xpm", &ptr->tile, &ptr->tile);
	//ptr->player[0] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/human.xpm", &ptr->tile, &ptr->tile); 
	//ptr->collectable[0] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/coin_00.xpm", &ptr->tile, &ptr->tile);
	ft_load_player_frames(ptr);
	ft_load_coin_frames(ptr);
	ptr->exit[0] = mlx_xpm_file_to_image(ptr->mlx, "./xpm/door_01.xpm", &ptr->tile, &ptr->tile); 
}

void	ft_player_direction(t_mlx *ptrs, int *frame, int w_tile, int h_tile)
{
	if (ptrs->key == 65362 || ptrs->key == 119) /* up */
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_up[*frame], w_tile, h_tile);
	else if (ptrs->key == 65364 || ptrs->key == 115) /* down */
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_down[*frame], w_tile, h_tile);
	else if (ptrs->key == 65361 || ptrs->key == 97) /* left */
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_left[*frame], w_tile, h_tile);
	else if (ptrs->key == 65363 || ptrs->key == 100) /* right */
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_right[*frame], w_tile, h_tile);
	else
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_down[0], w_tile, h_tile);
}

int	ft_draw_map(t_mlx *ptrs)
{
	int			h;
	int			w;
	int			w_tile;
	int			h_tile;
	static int			frame;

	h = -1;
	while (++h < ptrs->height)
	{
		w = -1;
		while (++w < ptrs->width)
		{
			w_tile = w * ptrs->tile;
			h_tile = h * ptrs->tile;
			if (ptrs->map[h][w] == '1')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->wall[0], w_tile, h_tile);
			else if (ptrs->map[h][w] == '0')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->path[0], w_tile, h_tile);
			else if (ptrs->map[h][w] == 'P')
				ft_player_direction(ptrs, &frame, w_tile, h_tile);
			else if (ptrs->map[h][w] == 'C')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->collectable[frame], w_tile, h_tile);
			else if (ptrs->map[h][w] == 'E')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->exit[0], w_tile, h_tile);
		}
	}
	//printf("%d\n", frame);
	frame = (frame + 1) % FRAMES;
	usleep(100000);
	return (0);
}

int	ft_handle_input(int key, t_mlx *ptrs)
{
	int	new_x;
	int	new_y;

	ptrs->key = key;
	printf("key:'%d'\n", ptrs->key);
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
		//mlx_clear_window(ptrs->mlx, ptrs->win);
		//ft_draw_map(ptrs);
	}
	return (0);
}
