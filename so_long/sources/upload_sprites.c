/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/03/30 14:54:27by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_load_textures(t_mlx *p);
void	ft_load_player_frames(t_mlx *p);
void	ft_load_coin_frames(t_mlx *p);

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
