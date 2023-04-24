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
int		ft_draw_map(t_mlx *p);
int		ft_handle_input(int key, t_mlx *p);
void	ft_collectable_and_exit(t_mlx *p);

int	ft_handle_event(int key, t_mlx *p);

int	main(int ac, char **av)
{
	t_mlx	p;

	if (ac != 2)
		return(0);
	ft_init_map_and_window(&p, av[ac - 1]);

	/*int i = -1;
	while (p.map[++i])
		printf("'%s'\t'%d'\twidth:'%d'\theight:'%d'\ttile:'%d'\n", p.map[i], i, p.width, p.height, p.tile);
	*/	
	ft_make_pix_map(&p);

	mlx_hook(p.win, KeyPress, KeyPressMask, ft_handle_input, &p);
	//mlx_hook(p.win, DestroyNotify, StructureNotifyMask, ft_handle_event, &p);
	mlx_loop_hook(p.mlx, ft_draw_map, &p);
	mlx_loop(p.mlx);
}

void	ft_init_map_and_window(t_mlx *p, char *str)
{
	int	screen_w;
	int	screen_h;

	ft_map_to_array(p, str); // opening file and storing the map data both in str and 2d arr.
	ft_validating_map(p);
	/* might need to add protection in case of mlx_init error */
	p->mlx = mlx_init();

	mlx_get_screen_size(p->mlx, &screen_w, &screen_h);
	//printf("screen. w:'%d', h:'%d'\n", screen_w, screen_h);

	p->win = mlx_new_window(p->mlx, (p->tile * p->width), (p->tile * p->height), "Game");
	p->buff.img = mlx_new_image(p->mlx, (p->tile * p->width), (p->tile * p->height));
	p->buff.addr = mlx_get_data_addr(p->buff.img, &(p->buff.bpp), &(p->buff.line_len), &(p->buff.endian));
	ft_load_textures(p); // assign each sprite handle to its respective pointer
}

int	ft_handle_event(int event, t_mlx *p)
{
	printf("event: '%d', DestNot: '%d'\n", event, DestroyNotify);
	if (event == DestroyNotify || event == -16778640)
		ft_free_and_destroy(p, 0, NULL);
	return (0);
}

int	ft_handle_input(int key, t_mlx *p)
{
	p->key = key;
	if (key == 65307)
		ft_free_and_destroy(p, 0, NULL);
	return (0);
}

int	ft_max_window(void *mlx, void *win)
{
	int	screen_w;
	int	screen_h;

	mlx_get_screen_size(mlx, &screen_w, &screen_h);
	//mlx_resize_window(mlx, win, screen_w, screen_h);

	return (0);
}

int	ft_draw_map(t_mlx *p)
{
	ft_render_back_buff_img(p);
	ft_render_player(p);

	mlx_put_image_to_window(p->mlx, p->win, p->buff.img, 0, 0);

	usleep(100000);
	return (0);
}

void	ft_collectable_and_exit(t_mlx *p)
{
	if (p->map[p->pos.cur_y][p->pos.cur_x] == 'C')
	{
		p->map[p->pos.cur_y][p->pos.cur_x] = '0';
		p->c_count--;
	}
	else if (p->map[p->pos.cur_y][p->pos.cur_x] == 'E')
	{
		if (p->c_count == 0)
		{
			/* to-do, make exit available */
			ft_free_and_destroy(p, 0, NULL);
		}
	}
	if (p->pos.cur_x != p->pos.prev_x || p->pos.cur_y != p->pos.prev_y)
	{
		p->pos.prev_x = p->pos.cur_x;
		p->pos.prev_y = p->pos.cur_y;
		p->moves++;
	}
}

/*
void	ft_put_pix_to_img(t_image *img, int x, int y, int color)
{
	char	*pix;

	pix = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	*(int *)pix = color;
}
*/
