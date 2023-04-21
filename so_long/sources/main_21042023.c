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

#include <stdio.h>
#include "../includes/libft.h"
#include "../includes/mlx/mlx.h"
#include "../includes/mlx/mlx_int.h"

#define PIX 32
#define BUFF_SIZE 1024
#define W '1'
#define G '0'
#define E 'E'
#define C 'C'
#define P 'P'

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_mlx_ptr
{
	void	*mlx;
	void	*win;
	t_image	buff;
	/* sprites handles */
	void	*wall;
	void	*path;
	void	*player;
	void	*collectable;
	void	*exit;
	/* map */
	char	*raw;
	char	**map;
	int		height;
	int		width;
	int		tile;
	/* game elements */
	int		c_count;
	int		p;
	int		p_x;
	int		p_y;
	int		e;
	int		e_x;
	int		e_y;
}	t_mlx;

void	ft_init_map_and_window(t_mlx *ptrs, char *str);
void	ft_load_textures(t_mlx *ptr);
int		ft_draw_map(t_mlx *ptrs);
void	ft_init_game_elements(t_mlx *ptrs);
int		ft_handle_input(int key, t_mlx *ptrs);
/* ft_map.c */
void	ft_map_to_array(t_mlx *ptrs, char *file_path);
char	*ft_copy_to_buf(int fd);
void	ft_validating_map(t_mlx *ptrs);
int		ft_invalid_elements(char *raw_map);
void	ft_map_validation(t_mlx *ptrs, int h, int w);
/* ft_free_and_exit.c */
void	ft_free_textures(t_mlx *ptrs);
void	ft_free_and_destroy(t_mlx *ptrs, int status, char *msg);
void	ft_free_map(t_mlx *m);

int	main(int ac, char **av)
{
	t_mlx		p;

	ft_map_to_array(&p, av[ac - 1]); // opening file and storing the map data both in str and 2d arr.
	ft_validating_map(&p);

	int i = -1;
	while (p.map[++i])
		printf("'%s'\t'%d'\twidth:'%d'\theight:'%d'\ttile:'%d'\n", p.map[i], i, p.width, p.height, p.tile);

	p.mlx = mlx_init();
	p.win = mlx_new_window(p.mlx, (p.tile * p.width), (p.tile * p.height), "Game");
	p.buff.img = mlx_new_image(p.mlx, (p.tile * p.width), (p.tile * p.height));
	p.buff.addr = mlx_get_data_addr(p.buff.img, &(p.buff.bpp), &(p.buff.line_len), &(p.buff.endian));

	ft_load_textures(&p); // assign each sprite handle to its respective pointer

	mlx_hook(p.win, KeyPress, KeyPressMask, ft_handle_input, &p);
	mlx_loop_hook(p.mlx, ft_draw_map, &p);
	mlx_loop(p.mlx);
}

void	ft_load_textures(t_mlx *ptr)
{
	ptr->wall = mlx_xpm_file_to_image(ptr->mlx, "./xpm/brick.xpm", &ptr->tile, &ptr->tile);
	ptr->path = mlx_xpm_file_to_image(ptr->mlx, "./xpm/ground.xpm", &ptr->tile, &ptr->tile);
	ptr->player = mlx_xpm_file_to_image(ptr->mlx, "./xpm/unseen_horror.xpm", &ptr->tile, &ptr->tile);
	ptr->collectable = mlx_xpm_file_to_image(ptr->mlx, "./xpm/coin_00.xpm", &ptr->tile, &ptr->tile);
	ptr->exit = mlx_xpm_file_to_image(ptr->mlx, "./xpm/door_01.xpm", &ptr->tile, &ptr->tile);
}

void	ft_put_sprite_to_buff(void *spr, int x, int y, t_image *back_buff)
{
	int		pix_x;
	int		pix_y;
	int		pix_offset;
	int		spr_offset;
	int		h;
	int		w;
	t_image	sprite;

	sprite.img = mlx_get_data_addr(spr, &sprite.bpp, &sprite.line_len, &sprite.endian);

	h = -1;
	while (++h < PIX)
	{
		w = -1;
		while (++w < PIX)
		{
			pix_y = y + h;
			pix_x = x + w;
			pix_offset = (pix_y * back_buff->line_len) + (pix_x * (back_buff->bpp / 8));
			spr_offset = (h * sprite.line_len) + (w * (sprite.bpp / 8));
			ft_memcpy(back_buff->addr + pix_offset, sprite.img + spr_offset, back_buff->bpp / 8);
		}
	}
	//printf("img @ '%p'\taddr:'%s'\tbpp:'%d'\tline_len:'%d'\tendian:'%d'\n", sprite.img, sprite.addr, sprite.bpp, sprite.line_len, sprite.endian);
}

int	ft_draw_map(t_mlx *p)
{
	int			y;
	int			x;

	//mlx_do_sync(p->mlx);
	y = -1;
	while (++y < p->height)
	{
		x = -1;
		while (++x < p->width)
		{
			if (p->map[y][x] == '1')
				ft_put_sprite_to_buff(p->wall, x * PIX, y * PIX, &p->buff);
			else if (p->map[y][x] == '0')
				ft_put_sprite_to_buff(p->path, x * PIX, y * PIX, &p->buff);
			else if (p->map[y][x] == 'E')
				ft_put_sprite_to_buff(p->exit, x * PIX, y * PIX, &p->buff);
			else if (p->map[y][x] == 'C')
				ft_put_sprite_to_buff(p->collectable, x * PIX, y * PIX, &p->buff);
			else if (p->map[y][x] == 'P')
				ft_put_sprite_to_buff(p->player, x * PIX, y * PIX, &p->buff);
		}
	}

	mlx_put_image_to_window(p->mlx, p->win, p->buff.img, 0, 0);
	//printf("buff @ '%p'\taddr:'%s'\tbpp:'%d'\tline_len:'%d'\tendian:'%d'\n", p->buff.img, p->buff.addr, p->buff.bpp, p->buff.line_len, p->buff.endian);

	usleep(100000);
	return (0);
}

int	ft_handle_input(int key, t_mlx *ptrs)
{
	int	new_x;
	int	new_y;

	if (key == 65307)
		ft_free_and_destroy(ptrs, 0, NULL);
	new_x = ptrs->p_x;
	new_y = ptrs->p_y;
	if (key == 65362 || key == 119) /* up */
	{
		new_y--;
		printf("UP key:'%d'\n", key);
	}
	else if (key == 65364 || key == 115) /* down */
	{
		new_y++;
		printf("DOWN key:'%d'\n", key);
	}
	else if (key == 65361 || key == 97) /* left */
	{
		new_x--;
		printf("LEFT key:'%d'\n", key);
	}
	else if (key == 65363 || key == 100) /* right */
	{
		new_x++;
		printf("RIGHT key:'%d'\n", key);
	}
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

/* map */
void	ft_map_to_array(t_mlx *ptrs, char *file_path)
{
	int		fd;
	int		i;
	int		tmp;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return;
	ptrs->raw = ft_copy_to_buf(fd);
	close(fd);
	ptrs->map = ft_split(ptrs->raw, '\n');
	i = 0;
	ptrs->width = (int)ft_strlen(ptrs->map[i]);
	while (ptrs->map[++i])
	{
		tmp = (int)ft_strlen(ptrs->map[i]);
		if (tmp != ptrs->width)
			ft_free_and_destroy(ptrs, 1, "Map rows length error.\n");
	}
	ptrs->height = i;
	ptrs->tile = PIX;
	if (ptrs->width == ptrs->height)
		ft_free_and_destroy(ptrs, 1, "Error: Make sure the map has rectangular shape.\n");
}

char	*ft_copy_to_buf(int fd)
{
	char	buff[BUFF_SIZE + 1];
	char 	*map_str;
	char	*tmp;
	ssize_t	ret;

	map_str = ft_strdup("");
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buff, BUFF_SIZE);
		buff[ret] = '\0';
		tmp = ft_strjoin(map_str, buff);
		free(map_str);
		map_str = tmp;
	}
	if (ret == -1)
	{
		free(map_str);
		return (NULL);
	}
	return(map_str);
}

void	ft_validating_map(t_mlx *ptrs)
{
	int	h;
	int	w;

	if (ft_invalid_elements(ptrs->raw))
		ft_free_and_destroy(ptrs, 1, "Error: Invalid map elements.\n");
	h = -1;
	ptrs->p = 0;
	ptrs->e = 0;
	ptrs->c_count = 0;
	ft_map_validation(ptrs, h, w);
	if (ptrs->p != 1)
		ft_free_and_destroy(ptrs, 1, "Error: Single player required.\n");
	if (ptrs->e != 1)
		ft_free_and_destroy(ptrs, 1, "Error: Single exit required.\n");
	if (!ptrs->c_count)
		ft_free_and_destroy(ptrs, 1, "Error: At least one collectable required.\n");

	// Start to exit path validation
}

int	ft_invalid_elements(char *raw_map)
{
	int	i;

	i = -1;
	while(raw_map[++i])
	{
		if (raw_map[i] != W // 49
			&& raw_map[i] != G // 48
			&& raw_map[i] != P // 80
			&& raw_map[i] != E // 69
			&& raw_map[i] != C // 67
			&& raw_map[i] != '\n')// 10
			return (1);
	}
	return (0);
}

void	ft_map_validation(t_mlx *ptrs, int h, int w)
{
	while (++h < ptrs->height)
	{
		w = -1;
		while (++w < ptrs->width)
		{
			if ((h == 0 || h == ptrs->height - 1) && ptrs->map[h][w] != '1')
				ft_free_and_destroy(ptrs, 1, "Error: Make sure the map wals are complete.\n");
			else if ((w == 0 || w == ptrs->width - 1) && ptrs->map[h][w] != '1')
				ft_free_and_destroy(ptrs, 1, "Error: Make sure the map wals are complete.\n");
			if (ptrs->map[h][w] == 'P')
			{
				ptrs->p_y = h;
				ptrs->p_x = w;
				ptrs->p++;
			}
			else if (ptrs->map[h][w] == 'E')
			{
				ptrs->e_y = h;
				ptrs->e_x = w;
				ptrs->e++;
			}
			else if (ptrs->map[h][w] == 'C')
				ptrs->c_count++;
		}
	}
}

/* ft_free_and_exit.c */
void	ft_free_textures(t_mlx *ptrs);
void	ft_free_and_destroy(t_mlx *ptrs, int status, char *msg);
void	ft_free_map(t_mlx *m);

void	ft_free_and_destroy(t_mlx *ptrs, int status, char *msg)
{
	if (ptrs->mlx)
	{
		ft_free_textures(ptrs);
		mlx_destroy_window(ptrs->mlx, ptrs->win);
		mlx_destroy_display(ptrs->mlx);
		free(ptrs->mlx);
	}
	ft_free_map(ptrs);
	if (msg)
		ft_putstr_fd(msg, 2);	
	exit(status);
}

void	ft_free_textures(t_mlx *ptrs)
{
	mlx_destroy_image(ptrs->mlx, ptrs->wall);
	mlx_destroy_image(ptrs->mlx, ptrs->path);
	mlx_destroy_image(ptrs->mlx, ptrs->player);
	mlx_destroy_image(ptrs->mlx, ptrs->collectable);
	mlx_destroy_image(ptrs->mlx, ptrs->exit);
}

void	ft_free_map(t_mlx *ptrs)
{
	int	i;

	free(ptrs->raw);
	i = 0;
	while (ptrs->map[i])
		free(ptrs->map[i++]);
	free(ptrs->map[i]);
	free(ptrs->map);
}
