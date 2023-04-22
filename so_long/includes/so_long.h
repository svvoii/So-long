/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:24:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/04/22 14:23:01 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include "libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"

# define FRAMES 6
# define PIX 32
# define BUFF_SIZE 1024
# define W '1'
# define G '0'
# define E 'E'
# define C 'C'
# define P 'P'

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef	struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_mlx_ptr
{
	void	*mlx;
	void	*win;
	t_image	buff;
	/* sprites handles */
	void	*wall[FRAMES];
	void	*path[FRAMES];
	void	*p_up[FRAMES];
	void	*p_down[FRAMES];
	void	*p_left[FRAMES];
	void	*p_right[FRAMES];
	void	*collectable[FRAMES];
	void	*exit[FRAMES];
	/* map */
	char	*raw;
	char	**map;
	char	**pix_map;
	int		height;
	int		width;
	int		tile;
	/* game elements */
	int		c_count;
	int		p;
	int		player_x;
	int		player_y;
	int		next_x;
	int		next_y;
	int		e;
	int		e_x;
	int		e_y;
	int		key;
	t_pos	pos;
	/* index */
	int		w;
	int		h;
}	t_mlx;

/* main.c */

/* map_setting.c */
void	ft_map_to_array(t_mlx *ptrs, char *file_path);
char	*ft_copy_to_buf(int fd);
void	ft_make_pix_map(t_mlx *p);
void	ft_set_mem_for_pixmap(t_mlx *p);
void	ft_fill_in_map(t_mlx *p, int w_pix, int h_pix, char c);
/* validating_map.c */
void	ft_validating_map(t_mlx *ptrs);
int		ft_invalid_elements(char *raw_map);
void	ft_map_validation(t_mlx *ptrs, int h, int w);
/* upload_textures.c */
void	ft_load_textures(t_mlx *p);
void	ft_load_player_frames(t_mlx *p);
void	ft_load_coin_frames(t_mlx *p);
/* ft_free_and_destroy.c */
void	ft_free_and_destroy(t_mlx *ptrs, int status, char *msg);
void	ft_free_textures(t_mlx *ptrs);
void	ft_destroy_img(t_mlx *p, void **img);
void	ft_free_map(t_mlx *m);

#endif