/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:24:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/05/06 15:13:48 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include "libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"

# define PIX 32
# define FRAMES 6
# define DIGITS 10
# define END_FRAMES 24
# define BUFF_SIZE 1024
# define PLAYER_SPEED 16
# define ENEMIES_COUNT 12
# define TMP_BUF 256

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

typedef struct s_bfs
{
	char	**visited;
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
	int		w;
	int		h;
}	t_image;

typedef struct s_pos
{
	int	x;
	int	y;
	int	cur_x;
	int	cur_y;
	int	prev_x;
	int	prev_y;
	int	ex_x;
	int	ex_y;
	int	step;
}	t_pos;

/* sprites handles */
typedef struct s_sprites
{
	void	*up[FRAMES];
	void	*dn[FRAMES];
	void	*lt[FRAMES];
	void	*rt[FRAMES];
	void	*c[FRAMES];
	void	*num[DIGITS];
	void	*win[END_FRAMES];
	void	*e;
	void	*w;
	void	*p;
	void	*uh;
	void	*ov;
	int		wd;
	int		ht;
}	t_spr;

/* mlx elements */
/* map elements */
/* game elements */
typedef struct s_mlx_ptr
{
	void	*mlx;
	void	*win;
	t_spr	sp;
	t_image	bf;
	t_enemy	en[ENEMIES_COUNT];
	t_bfs	bfs;

	int		game_over;
	int		cent_w;
	int		cent_h;
	char	*raw;
	char	**map;
	char	**pix_map;
	int		height;
	int		width;
	int		t;

	int		moves;
	int		c_count;
	int		player;
	int		exit;
	int		key;
	int		ground;
	t_pos	pos;
}	t_mlx;

/* main.c */
void	ft_init_map_and_window(t_mlx *p, char *str);
int		ft_handle_input(int key, t_mlx *p);
int		ft_draw_map(t_mlx *p);
void	ft_collect_and_exit(t_mlx *p);
void	ft_render_player(t_mlx *p);
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
void	ft_map_elements_check(t_mlx *p);
void	calculate_map_elements(t_mlx *p, char c);
/* upload_sprites.c */
void	ft_load_textures(t_mlx *p);
void	ft_load_player_frames(t_mlx *p);
void	ft_load_coin_frames(t_mlx *p);
void	ft_load_numbers(t_mlx *p);
void	ft_load_you_win(t_mlx *p);
/* free_and_exit.c */
void	ft_free_and_destroy(t_mlx *p, int status, char *msg);
void	ft_free_textures(t_mlx *p);
void	ft_destroy_img(t_mlx *p, void **img, int frames);
void	ft_free_map(t_mlx *m);
int		ft_handle_on_destroy(t_mlx *p);
/* render_sprites */
void	ft_render_back_buff_img(t_mlx *p);
void	ft_set_direction(t_mlx *p);
void	ft_update_player_pos(t_mlx *p);
void	ft_drawing_movement(t_mlx *p, int *frame, int w_tile, int h_tile);
void	ft_put_sprite_to_buff(void *spr, int x, int y, t_image *back_buff);
/* bfs.c */
int		ft_bfs(t_mlx *p);
int		ft_bfs_search(t_mlx *p);
int		valid(t_mlx *p, int x, int y);
char	**ft_malloc_bfs(t_mlx *p);
void	ft_free_bfs(t_mlx *p);
/* helpers.c */
void	game_statistics(t_mlx *p);
void	moves_count(t_mlx *p);
void	collectables_count(t_mlx *p);
void	ft_collectables(t_mlx *p);

/* BONUS PART */
/* bonus_spawn_enemies.c */
void	insert_enemy(t_mlx *p);
void	spawn_enemy(t_mlx *p);
void	save_valid_tiles(int tile[2], int x, int y, int *count);
int		valid_tile(t_mlx *p, int x, int y);
void	render_enemy(t_mlx *p);
/* bonus_set_enemy_direction.c */
void	set_enemy_direction(t_mlx *p, int i, char axis);
void	set_y_axis_direction(t_mlx *p, int i, int x, int y);
void	set_x_axis_direction(t_mlx *p, int i, int x, int y);
void	set_target(t_mlx *p, int i, int x, int y);
int		valid_direction(t_mlx *p, int x, int y);
/* bonus_update_enemy.c */
void	reset_direction(t_mlx *p, int i);
void	move_enemy(t_mlx *p, int i);
void	chase_player(t_mlx *p, int i);
void	move_chasing_enemy(t_mlx *p, int i, char dir);
void	update_enemy_pos(t_mlx *p, int i, char dir);

#endif