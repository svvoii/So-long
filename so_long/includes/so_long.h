/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:24:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/04/24 15:07:17by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdbool.h>
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
# define EN_COUNT 10
# define NORTH	'N'
# define SOUTH	'S'
# define WEST	'W'
# define EAST	'E'

typedef struct s_enemy
{
	int		x;
	int		y;
	int		st_x;
	int		st_y;
	int		tg_x;
	int		tg_y;
	int		pix_x;
	int		pix_y;
	int		depth;
	int		step;
	char	direction;
}	t_enemy;

typedef	struct s_bfs
{
	bool	**visited;
	int		*queue_x;
	int		*queue_y;
	int		vect_x[4];
	int		vect_y[4];
	int		fr;
	int		rr;
	int		x;
	int		y;
	int		nxt_x;
	int		nxt_y;
}	t_bfs;

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
	int	cur_x;
	int	cur_y;
	int	prev_x;
	int	prev_y;
	int	ex_x;
	int	ex_y;
}	t_pos;

typedef struct s_sprites
{
	/* sprites handles */
	void	*w[FRAMES];
	void	*p[FRAMES];
	void	*up[FRAMES];
	void	*dn[FRAMES];
	void	*lt[FRAMES];
	void	*rt[FRAMES];
	void	*c[FRAMES];
	void	*e[FRAMES];
	void	*uh[FRAMES];
}	t_spr;

typedef struct s_mlx_ptr
{
	void	*mlx;
	void	*win;
	t_spr	sp;
	t_image	bf;
	t_enemy	en[EN_COUNT];
	int		en_count;
	/* map */
	char	*raw;
	char	**map;
	char	**pix_map;
	int		height;
	int		width;
	int		t;
	/* game elements */
	int		moves;
	int		c_count;
	int		player;
	int		exit;
	int		key;
	t_pos	pos;
}	t_mlx;

/* main.c */
void	ft_init_map_and_window(t_mlx *p, char *str);
int		ft_handle_input(int key, t_mlx *p);
int		ft_handle_on_destroy(t_mlx *p);
int		ft_draw_map(t_mlx *p);
void	ft_collect_and_exit(t_mlx *p);
/* map_setting.c */
void	ft_map_to_array(t_mlx *p, char *file_path);
char	*ft_copy_to_buf(int fd);
void	ft_make_pix_map(t_mlx *p);
void	ft_set_mem_for_pixmap(t_mlx *p);
void	ft_fill_in_map(t_mlx *p, int w_pix, int h_pix, char c);
/* validating_map.c */
void	ft_set_values(t_mlx *p);
void	ft_validating_map(t_mlx *p);
int		ft_invalid_elements(char *raw_map);
void	ft_map_elements_check(t_mlx *p, int h, int w);
/* upload_sprites.c */
void	ft_load_textures(t_mlx *p);
void	ft_load_player_frames(t_mlx *p);
void	ft_load_coin_frames(t_mlx *p);
/* free_and_exit.c */
void	ft_free_and_destroy(t_mlx *p, int status, char *msg);
void	ft_free_textures(t_mlx *p);
void	ft_destroy_img(t_mlx *p, void **img);
void	ft_free_map(t_mlx *m);
/* render_sprited */
void	ft_render_back_buff_img(t_mlx *p);
void	ft_render_player(t_mlx *p);
void	ft_set_direction(t_mlx *p);
void	ft_drawing_movement(t_mlx *p, int *frame, int w_tile, int h_tile);
void	ft_put_sprite_to_buff(void *spr, int x, int y, t_image *back_buff);
/* bfs.c */
bool	ft_bfs(t_mlx *p, t_bfs *bfs);
bool	ft_bfs_search(t_mlx *p, t_bfs *bfs);
bool	valid(t_mlx *p, int x, int y);
void	*ft_malloc_bfs(t_mlx *p, t_bfs *bfs);
void	ft_free_bfs(t_mlx *p, t_bfs *bfs);
/* bonus_enemy.c */
void	place_enemy(t_mlx *p, int i);
int		valid_tile(t_mlx *p, int x, int y);
int		insert_enemy(t_mlx *p);
void	render_enemy(t_mlx *p);
void	drawing_enemy(t_mlx *p, int w_tile, int h_tile);

void	game_over(t_mlx *p);
void	game_stat(t_mlx *p);

#endif