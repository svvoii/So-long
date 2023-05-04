/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/04 17:06:12 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_init_map_and_window(t_mlx *p, char *str);
int		ft_handle_input(int key, t_mlx *p);
int		ft_draw_map(t_mlx *p);
void	ft_collect_and_exit(t_mlx *p);
void	ft_render_player(t_mlx *p);

int	main(int ac, char **av)
{
	t_mlx	p;

	if (ac != 2)
		return (0);
	ft_init_map_and_window(&p, av[ac - 1]);
	if (p.ground / 3 > ENEMIES_COUNT)
		insert_enemy(&p);
	mlx_hook(p.win, DestroyNotify, NoEventMask, ft_handle_on_destroy, &p);
	mlx_hook(p.win, KeyPress, KeyPressMask, ft_handle_input, &p);
	mlx_loop_hook(p.mlx, ft_draw_map, &p);
	mlx_loop(p.mlx);
}

void	ft_init_map_and_window(t_mlx *p, char *str)
{
	p->mlx = NULL;
	p->win = NULL;
	ft_map_to_array(p, str);
	ft_make_pix_map(p);
	ft_validating_map(p);
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, (PIX * p->width), (PIX * p->height), "S");
	p->bf.img = mlx_new_image(p->mlx, (PIX * p->width), (PIX * p->height));
	p->bf.addr = mlx_get_data_addr(
			p->bf.img, &(p->bf.bpp), &(p->bf.line_len), &(p->bf.endian));
	ft_load_textures(p);
}

int	ft_handle_input(int key, t_mlx *p)
{
	p->key = key;
	if (key == 65307)
		ft_free_and_destroy(p, 0, NULL);
	return (0);
}

int	ft_draw_map(t_mlx *p)
{
	static int	frame;

	ft_render_back_buff_img(p);
	ft_render_player(p);
	if (p->ground / 3 > ENEMIES_COUNT)
		render_enemy(p);
	if (p->game_over == 1)
		mlx_put_image_to_window(
			p->mlx, p->win, p->sp.win[frame], p->cent_w, p->cent_h);
	else if (p->game_over == -1)
		mlx_put_image_to_window(p->mlx, p->win, p->sp.ov, p->cent_w, p->cent_h);
	else
		mlx_put_image_to_window(p->mlx, p->win, p->bf.img, 0, 0);
	game_statistics(p);
	usleep(110000);
	frame = (frame + 1) % 24;
	return (0);
}

void	ft_render_player(t_mlx *p)
{
	static int	frame;

	ft_set_direction(p);
	ft_drawing_movement(p, &frame, p->pos.x, p->pos.y);
	ft_collectables(p);
	frame = (frame + 1) % FRAMES;
}
