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
int		ft_on_the_map(t_mlx *ptr, int x, int y);

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
	if ((ptrs->key == 65362 || ptrs->key == 119) && (h_tile > ptrs->t_y)) // up 
	{
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_up[*frame], w_tile, h_tile);
	}
	else if ((ptrs->key == 65364 || ptrs->key == 115) && (h_tile < ptrs->t_y)) // down
	{
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_down[*frame], w_tile, h_tile);
	}
	else if ((ptrs->key == 65361 || ptrs->key == 97) && (w_tile + ptrs->w > w_tile - ptrs->tile)) // left
	{
		ptrs->w -= 2;
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_left[*frame], w_tile + ptrs->w, h_tile);
		printf("left: w'%d'\n", ptrs->w);
	}
	else if ((ptrs->key == 65363 || ptrs->key == 100) && (w_tile + ptrs->w < w_tile + ptrs->tile)) // right
	{
		ptrs->w += 2;
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_right[*frame], w_tile + ptrs->w, h_tile);
		printf("right: w'%d'\n", ptrs->w);
	}
	else
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_down[0], w_tile, h_tile);
	//printf("t_x:'%d'\tt_y:'%d'\n", ptrs->t_x * ptrs->tile, ptrs->t_y * ptrs->tile);
	if (w_tile + ptrs->w == ptrs->t_x * ptrs->tile && h_tile + ptrs->h == ptrs->t_y * ptrs->tile)
	{
		ptrs->map[ptrs->p_y][ptrs->p_x] = '0';
		ptrs->p_x = ptrs->t_x;
		ptrs->p_y = ptrs->t_y;
		ptrs->map[ptrs->p_y][ptrs->p_x] = 'P';
		ptrs->w = 0;
		ptrs->h = 0;
		printf("\treset! w:'%d'\tw_tile:'%d', h_tile:'%d'\n", ptrs->w, w_tile, h_tile);
		//ptrs->key = 0;
	}
}
/*
void	ft_player_direction(t_mlx *ptrs, int *frame, int w_tile, int h_tile)
{
	if (ptrs->key == 65362 || ptrs->key == 119) // up
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_up[*frame], w_tile, h_tile);
	else if (ptrs->key == 65364 || ptrs->key == 115) // down
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_down[*frame], w_tile, h_tile);
	else if (ptrs->key == 65361 || ptrs->key == 97) // left 
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_left[*frame], w_tile, h_tile);
	else if (ptrs->key == 65363 || ptrs->key == 100) // right 
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_right[*frame], w_tile, h_tile);
	else
		mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->p_down[0], w_tile, h_tile);
}
*/
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
			{
				ft_player_direction(ptrs, &frame, w_tile, h_tile);
			}
			else if (ptrs->map[h][w] == 'C')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->collectable[frame], w_tile, h_tile);
			else if (ptrs->map[h][w] == 'E')
				mlx_put_image_to_window(ptrs->mlx, ptrs->win, ptrs->exit[0], w_tile, h_tile);
		}
	}
	//printf("frame: '%d'\n", frame);
	frame = (frame + 1) % FRAMES;
	usleep(100000);
	return (0);
}

int	ft_handle_input(int key, t_mlx *ptrs)
{
	ptrs->key = key;
	if (key == 65307)
		ft_free_and_destroy(ptrs, 0, NULL);
	ptrs->t_x = ptrs->p_x;
	ptrs->t_y = ptrs->p_y;
	if ((key == 65362 || key == 119) && (ft_on_the_map(ptrs, 0, -1))) /* up */
	{
		printf("key:'%d'\tup\n", ptrs->key);
		ptrs->t_y--;
	}
	else if (key == 65364 || key == 115 && (ft_on_the_map(ptrs, 0, 1))) /* down */
	{
		printf("key:'%d'\tdown\n", ptrs->key);
		ptrs->t_y++;
	}
	else if (key == 65361 || key == 97 && (ft_on_the_map(ptrs, -1, 0))) /* left */
	{
		printf("key:'%d'\tleft\n", ptrs->key);
		ptrs->t_x--;
	}
	else if (key == 65363 || key == 100 && (ft_on_the_map(ptrs, 1, 0))) /* right */
	{
		printf("key:'%d'\tright\n", ptrs->key);
		ptrs->t_x++;
	}
	if (ptrs->map[ptrs->t_y][ptrs->t_x] != '1')
	{
		//ptrs->map[ptrs->p_y][ptrs->p_x] = 'p';
		//ptrs->p_x = ptrs->t_x;
		//ptrs->p_y = ptrs->t_y;
		if (ptrs->map[ptrs->t_y][ptrs->t_x] == 'C')
			ptrs->map[ptrs->t_y][ptrs->t_x] = '0';
		else if (ptrs->map[ptrs->t_y][ptrs->t_x] == 'E')
			ft_free_and_destroy(ptrs, 0, NULL);
		ptrs->map[ptrs->t_y][ptrs->t_x] = 'T';
		//mlx_clear_window(ptrs->mlx, ptrs->win);
		//ft_draw_map(ptrs);
	}
	return (0);
}

int	ft_on_the_map(t_mlx *ptr, int x, int y)
{
	return (ptr->t_x + x >= 0 && ptr->t_x + x < ptr->width
		&& ptr->t_y + y >= 0 && ptr->t_y + y < ptr->height);
}
