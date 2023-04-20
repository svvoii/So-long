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

void	ft_init_map_and_window(t_mlx *p, char *str);
void	ft_load_textures(t_mlx *p);
int		ft_draw_map(t_mlx *p);
void	ft_init_game_elements(t_mlx *p);
int		ft_handle_input(int key, t_mlx *p);
int		ft_on_the_map(t_mlx *p, int x, int y);
void	ft_move_player(t_mlx *p, int x, int y);

void	ft_wall(t_mlx *p, int x, int y);
void	ft_path(t_mlx *p, int x, int y);
void	ft_exit(t_mlx *p, int x, int y);
void	ft_collectable(t_mlx *p, int x, int y, int frame);
void	ft_player(t_mlx *p, int x, int y, int frame);
void	ft_reset_p(t_mlx *p);
void	ft_set_direction(t_mlx *p, int x, int y);

int	main(int ac, char **av)
{
	t_mlx	p;

	if (ac != 2)
		return(0);
	ft_init_map_and_window(&p, av[ac - 1]);

	int i = -1;
	while (p.map[++i])
		printf("'%s'\t'%d'\twidth:'%d'\theight:'%d'\ttile:'%d'\n", p.map[i], i, p.width, p.height, p.tile);

	mlx_hook(p.win, KeyPress, KeyPressMask, ft_handle_input, &p);
	mlx_loop_hook(p.mlx, ft_draw_map, &p);
	mlx_loop(p.mlx);
}

void	ft_init_map_and_window(t_mlx *p, char *str)
{
	ft_map_to_array(p, str); // opening file and storing the map data both in str and 2d arr.
	ft_validating_map(p);
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, (p->tile * p->width), (p->tile * p->height), "Game");
	//p->back_buf = mlx_new_window(p->mlx, (p->tile * p->width), (p->tile * p->height), "Back Buffer");
	p->img.buff = mlx_new_image(p->mlx, (p->tile * p->width), (p->tile * p->height));
	p->img.addr = mlx_get_data_addr(p->img.buff, &(p->img.bpp), &(p->img.line_len), &(p->img.endian));
	ft_load_textures(p); // assign each sprite handle to its respective pointer
}

void	ft_img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pix;

	pix = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	*(int *)pix = color;
}

void	ft_player_direction(t_mlx *p, int *frame, int w_tile, int h_tile)
{
	if (p->key == 65362 || p->key == 119) // up
		mlx_put_image_to_window(p->mlx, p->win, p->p_up[*frame], w_tile, h_tile);
	else if (p->key == 65364 || p->key == 115) // down
		mlx_put_image_to_window(p->mlx, p->win, p->p_down[*frame], w_tile, h_tile);
	else if (p->key == 65361 || p->key == 97) // left 
		mlx_put_image_to_window(p->mlx, p->win, p->p_left[*frame], w_tile, h_tile);
	else if (p->key == 65363 || p->key == 100) // right 
		mlx_put_image_to_window(p->mlx, p->win, p->p_right[*frame], w_tile, h_tile);
	else
		mlx_put_image_to_window(p->mlx, p->win, p->p_down[0], w_tile, h_tile);
}

int	ft_draw_map(t_mlx *p)
{
	int			y;
	int			x;
	static int	frame;

	//mlx_destroy_image(p->mlx, p->back_buf);
	//p->back_buf = mlx_new_image(p->mlx, (p->tile * p->width), (p->tile * p->height));
	//p->back_buf_addr = mlx_get_data_addr(p->back_buf, &(p->bpp), &(p->size_line), &(p->endian));

	y = -1;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
		{
			if (p->map[y][x] == '1')
				mlx_put_image_to_window(p->mlx, p->win, p->wall[0], x * p->tile, y * p->tile);
			else if (p->map[y][x] == '0')
				mlx_put_image_to_window(p->mlx, p->win, p->path[0], x * p->tile, y * p->tile);
			else if (p->map[y][x] == 'E')
				mlx_put_image_to_window(p->mlx, p->win, p->exit[0], x * p->tile, y * p->tile);
			if (p->map[y][x] == 'C')
				mlx_put_image_to_window(p->mlx, p->win, p->collectable[frame], x * p->tile, y * p->tile);
			else if (p->map[y][x] == 'P')
				ft_player_direction(p, &frame, x * PIX, y * PIX);
		}
	}
	//mlx_put_image_to_window(p->mlx, p->win, p->back_buf, 0, 0);

	frame = (frame + 1) % FRAMES;
	usleep(100000);
	return (0);
}

void	ft_player(t_mlx *p, int x, int y, int frame)
{
	static int	i;
	int			step = 4;

	printf("i:'%d'\n", i);
	printf("key:'%d'\n", p->key);
	if (p->key != 0)
	{
		if ((i <= PIX) && (p->next_x != p->player_x || p->next_y != p->player_y))
		{
			if (p->next_y < p->player_y) // move up
			{
				ft_player_direction(p, &frame, x * PIX, (y * PIX) - i);
				if (p->next_y * PIX == (y * PIX) - i)
					ft_reset_p(p);
			}
			if (p->next_y > p->player_y) // move down
			{
				ft_player_direction(p, &frame, x * PIX, (y * PIX) + i);
				if (p->next_y * PIX == (y * PIX) + i)
					ft_reset_p(p);
			}
			if (p->next_x < p->player_x) // move left
			{
				ft_player_direction(p, &frame, (x * PIX) - i, y * PIX);
				if (p->next_x * PIX == (x * PIX) - i)
					ft_reset_p(p);
			}
			if (p->next_x > p->player_x) // move right
			{
				ft_player_direction(p, &frame, (x * PIX) + i, y * PIX);
				if (p->next_x * PIX == (x * PIX) + i)
					ft_reset_p(p);
			}
		}
		else
		{
			i = 0;
			ft_set_direction(p, x, y);
		}
		i += step;
	}
	else
		ft_player_direction(p, &frame, x, y);
}

void	ft_reset_p(t_mlx *p)
{
	if (p->map[p->next_y][p->next_x] == 'C')
		p->map[p->next_y][p->next_x] = '0';
	else if (p->map[p->next_y][p->next_x] == 'E')
		ft_free_and_destroy(p, 0, NULL);
	p->map[p->player_y][p->player_x] = '0';
	p->player_y = p->next_y;
	p->player_x = p->next_x;
	p->map[p->player_y][p->player_x] = 'P';
}

void	ft_set_direction(t_mlx *p, int x, int y)
{
	if ((p->key == 65362 || p->key == 119) && (ft_on_the_map(p, 0, -1))) /* up */
	{
		printf("key:'%d'\tup\n", p->key);
		p->next_y--;
	}
	else if (p->key == 65364 || p->key == 115 && (ft_on_the_map(p, 0, 1))) /* down */
	{
		printf("key:'%d'\tdown\n", p->key);
		p->next_y++;
	}
	else if (p->key == 65361 || p->key == 97 && (ft_on_the_map(p, -1, 0))) /* left */
	{
		printf("key:'%d'\tleft\n", p->key);
		p->next_x--;
	}
	else if (p->key == 65363 || p->key == 100 && (ft_on_the_map(p, 1, 0))) /* right */
	{
		printf("key:'%d'\tright\n", p->key);
		p->next_x++;
	}
	if (p->map[p->next_y][p->next_x] == '1')
	{
		p->next_x = p->player_x;
		p->next_y = p->player_y;
	}
}

int	ft_handle_input(int key, t_mlx *p)
{
	p->key = key;
	if (key == 65307)
		ft_free_and_destroy(p, 0, NULL);
	return (0);
}

int	ft_on_the_map(t_mlx *p, int x, int y)
{
	return (p->next_x + x >= 0 && p->next_x + x < p->width
		&& p->next_y + y >= 0 && p->next_y + y < p->height);
}

void	ft_load_textures(t_mlx *p)
{
	p->wall[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/wall_vines.xpm", &p->tile, &p->tile);
	p->path[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/ground.xpm", &p->tile, &p->tile);
	ft_load_player_frames(p);
	ft_load_coin_frames(p);
	p->exit[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/door_01.xpm", &p->tile, &p->tile); 
}

void	ft_load_player_frames(t_mlx *p)
{
	p->p_up[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_up_00.xpm", &p->tile, &p->tile);
	p->p_up[1] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_up_01.xpm", &p->tile, &p->tile);
	p->p_up[2] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_up_02.xpm", &p->tile, &p->tile);
	p->p_up[3] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_up_03.xpm", &p->tile, &p->tile);
	p->p_up[4] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_up_04.xpm", &p->tile, &p->tile);
	p->p_up[5] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_up_05.xpm", &p->tile, &p->tile);
	p->p_down[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_down_00.xpm", &p->tile, &p->tile);
	p->p_down[1] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_down_01.xpm", &p->tile, &p->tile);
	p->p_down[2] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_down_02.xpm", &p->tile, &p->tile);
	p->p_down[3] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_down_03.xpm", &p->tile, &p->tile);
	p->p_down[4] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_down_04.xpm", &p->tile, &p->tile);
	p->p_down[5] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_down_05.xpm", &p->tile, &p->tile);
	p->p_left[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_left_00.xpm", &p->tile, &p->tile);
	p->p_left[1] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_left_01.xpm", &p->tile, &p->tile);
	p->p_left[2] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_left_02.xpm", &p->tile, &p->tile);
	p->p_left[3] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_left_03.xpm", &p->tile, &p->tile);
	p->p_left[4] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_left_04.xpm", &p->tile, &p->tile);
	p->p_left[5] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_left_05.xpm", &p->tile, &p->tile);
	p->p_right[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_right_00.xpm", &p->tile, &p->tile);
	p->p_right[1] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_right_01.xpm", &p->tile, &p->tile);
	p->p_right[2] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_right_02.xpm", &p->tile, &p->tile);
	p->p_right[3] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_right_03.xpm", &p->tile, &p->tile);
	p->p_right[4] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_right_04.xpm", &p->tile, &p->tile);
	p->p_right[5] = mlx_xpm_file_to_image(p->mlx, "./xpm/cat_right_05.xpm", &p->tile, &p->tile);
}

void	ft_load_coin_frames(t_mlx *p)
{
	p->collectable[0] = mlx_xpm_file_to_image(p->mlx, "./xpm/coin_00.xpm", &p->tile, &p->tile);
	p->collectable[1] = mlx_xpm_file_to_image(p->mlx, "./xpm/coin_01.xpm", &p->tile, &p->tile);
	p->collectable[2] = mlx_xpm_file_to_image(p->mlx, "./xpm/coin_02.xpm", &p->tile, &p->tile);
	p->collectable[3] = mlx_xpm_file_to_image(p->mlx, "./xpm/coin_03.xpm", &p->tile, &p->tile);
	p->collectable[4] = mlx_xpm_file_to_image(p->mlx, "./xpm/coin_04.xpm", &p->tile, &p->tile);
	p->collectable[5] = mlx_xpm_file_to_image(p->mlx, "./xpm/coin_05.xpm", &p->tile, &p->tile);
}
