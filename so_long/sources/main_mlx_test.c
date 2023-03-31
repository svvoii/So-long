/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mlx_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/03/31 18:31:54 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>
#include "../includes/so_long.h"
//#include "../includes/mlx/mlx.h"
//#include "../includes/mlx/mlx_init.h"

/*
int	deal_key(int key, void *param);
void	ft_putchar(char	c);

int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 700, PIX + 10, "test_window");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFAA00);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	// The following will allow to handle events
	mlx_loop(mlx_ptr);
}

int	deal_key(int key, void *param)
{
	ft_putchar('x');
}

void	ft_putchar(char	c)
{
	write(1, &c, 1);
}
*/

typedef struct s_mlx
{
	void	*mlx_win;
	void	*mlx;
	t_img	*mlx_img;

}	t_mlx;

typedef struct s_game
{
	t_mlx	mlx;
	int		map_width;
	int		map_height;
	int		numb_move;
	t_img	*ground;
	t_img	*player;
	t_img	*collectible;
	t_img	*wall;
	t_img	*exit;
	char	*map;
	int		total_line_char;
	int		line_number;
	char	*player_position;
	int		nb_exit;
	int		numb;
	int		endline;
	int		fd;
	int		x;
	int		y;
}	t_game;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

void			ft_texture_load(t_game *game, t_img **img, char *path);
void			ft_check_arg(int argc, char **argv);
int				ft_key_hook(int keycode, t_game *game);
void			ft_verify_walls(char *line);
void			ft_check_map_elements(char *map_buff);
int				ft_init_struc(t_game *game);
int				ft_init_map(t_game *game, char *map_name);
void			ft_render_map(t_game *game);
void			ft_draw_square(t_game *game, t_img *img, int x, int y);
unsigned int	ft_get_pixel_mlx(t_img *img, int x, int y);
void			ft_draw_pixel_mlx(t_img *mlx_img, int x, int y, int color);
unsigned int	ft_rgbtoi_mlx(int o, int r, int g, int b);
void			ft_identify_elements(t_game *game, int x, int y, int z);
int				ft_exit(t_game *game);
void			ft_down(t_game *game);
void			ft_left(t_game *game);
void			ft_right(t_game *game);
void			ft_up(t_game *game);
void			ft_game_completed(t_game *game);
void			ft_init_textures(t_game *game);
int				ft_window_handling(t_game *game);
void			ft_error(char *nature, char *map_buff);


int	main(int argc, char **argv)
{
	t_game	game;

	ft_check_arg(argc, argv);
	ft_init_map(&game, argv[1]);
	ft_init_struc(&game);
	ft_render_map(&game);
	mlx_key_hook(game.mlx.mlx_win, ft_key_hook, &game);
	mlx_hook(game.mlx.mlx_win, 33, 1L << 5, ft_exit, &game);
	mlx_hook(game.mlx.mlx_win, 15, 1L << 16, ft_window_handling, &game);
	mlx_loop(game.mlx.mlx);

	return (0);
}

void	ft_check_arg(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of argument\n", 2);
		exit(0);
	}
	if ((ft_strlen(argv[1]) < 4) || (!ft_strrchr(argv[1], '.')))
	{
		ft_putstr_fd("Error\ninvalid argument\n", 2);
		exit(0);
	}
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".ber", ft_strlen(".ber")) != 0)
	{
		ft_putstr_fd("Error\nfile must be of type \"<name>.ber\"\n", 2);
		exit(0);
	}
}

void	ft_map_elements(t_game *game, char *map_buff);
void	deal_ret(int ret, t_game *game, char *line, char *map_buff);

int	ft_init_map(t_game *game, char *map_name)
{
	char	*line;
	int		ret;
	char	*map_buff;

	map_buff = malloc(sizeof(char) * 10000);
	*map_buff = 0;
	game->line_number = 0;
	game->fd = open(map_name, O_RDONLY);
	if (game->fd == -1)
		ft_error("Error\nfile cannot be read\n", map_buff);
	line = 0;
	ret = get_next_line(game->fd, &line);
	ft_verify_walls(line);
	game->total_line_char = ft_strlen(line);
	deal_ret(ret, game, line, map_buff);
	ft_map_elements(game, map_buff);
	return (1);
}

void	ft_map_elements(t_game *game, char *map_buff)
{
	if (((ft_strrchr(map_buff, 'P') == NULL)
		|| (ft_strrchr(map_buff, 'E') == NULL)
		|| (ft_strrchr(map_buff, 'C') == NULL))
		&& ((ft_strrchr(map_buff, 'p') == NULL)
		|| (ft_strrchr(map_buff, 'e') == NULL)
		|| (ft_strrchr(map_buff, 'c') == NULL)))
		ft_error("Error\nMissing one player, one collectible or one exit\n",
			map_buff);
	if (game->line_number - 1 == game->total_line_char)
		ft_error("Error\nMap is square!\n", map_buff);
	ft_check_map_elements(map_buff);
	game->map_height = (game->line_number - 1) * PIX;
	game->map_width = game->total_line_char * PIX;
	game->map = malloc(sizeof(char) * (game->total_line_char * game->line_number) + 1);
	ft_strlcpy(game->map, map_buff, (game->line_number * game->total_line_char));
	game->fd = close(game->fd);
	free(map_buff);
}

void	deal_ret(int ret, t_game *game, char *line, char *map_buff)
{
	while (ret > 0)
	{
		game->line_number++;
		game->endline = ft_strlen(line) - 1;
		if (line[0] != '1' || line[game->endline] != '1')
			ft_error("Error\nWall missing in the border\n", map_buff);
		ft_strcat(map_buff, line);
		free(line);
		line = 0;
		ret = get_next_line(game->fd, &line);
		if ((ret != 0) && (ft_strlen(line) != (long unsigned int)game->total_line_char))
			ft_error("Error\nmap has a problem\n", map_buff);
		if (ret == 0)
		{
			game->line_number++;
			ft_verify_walls(line);
			ft_strcat(map_buff, line);
			free(line);
			line = 0;
		}
	}
}

int	ft_init_struc(t_game *game)
{
	game->nb_exit = 0;
	game->numb_move = 0;
	game->mlx.mlx = mlx_init();
	game->mlx.mlx_win = mlx_new_window(game->mlx.mlx, game->map_width, game->map_height, "Game");
	game->mlx.mlx_img = mlx_new_image(game->mlx.mlx, game->map_width, game->map_height);
	ft_init_textures(game);
	return (1);
}

// draw map
void	ft_render_map(t_game *game)
{
	int	z;

	game->numb = 0;
	game->y = 0;
	game->x = -PIX;
	while (game->y < (game->line_number - 1))
	{
		z = 0;
		while (z < game->total_line_char)
		{
			if (game->map[z + game->numb] == '1')
				ft_draw_square(game, game->wall, game->x += PIX, game->y * PIX);
			else
			{
				ft_draw_square(game, game->ground, game->x += PIX, game->y * PIX);
				ft_identify_elements(game, game->x, game->y, z);
			}
			z++;
		}
		game->y++;
		game->numb = game->total_line_char * game->y;
	}
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.mlx_win,
		game->mlx.mlx_img, 0, 0);
}

void	ft_draw_square(t_game *game, t_img *img, int x, int y)
{
	unsigned int	color;
	int				i;
	int				j;

	j = 0;
	while (j < PIX)
	{
		i = 0;
		while (i < PIX)
		{
			color = ft_get_pixel_mlx(img, i, j);
			if (color != ft_rgbtoi_mlx(0, 255, 255, 255))
				ft_draw_pixel_mlx(game->mlx.mlx_img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	ft_identify_elements(t_game *game, int x, int y, int z)
{
	if (game->map[z + game->numb] == 'P' || game->map[z + game->numb] == 'p')
		ft_draw_square(game, game->player, x, y * (PIX - 1));
	if (game->map[z + game->numb] == 'C' || game->map[z + game->numb] == 'c')
		ft_draw_square(game, game->collectible, x, y * (PIX - 1));
	if (game->map[z + game->numb] == 'E' || game->map[z + game->numb] == 'e' 
		|| game->map[z + game->numb] == 'X')
		ft_draw_square(game, game->exit, x, y * (PIX - 1));
}

// helpers
void	ft_texture_load(t_game *game, t_img **img, char *path)
{
	int	width;
	int	height;

	*img = mlx_xpm_file_to_image(game->mlx.mlx, path, &width, &height);
	if (*img == 0)
		ft_putstr_fd("Error\nCan't load texture\n", 2);
	(*img)->width = width;
	(*img)->height = height;
}

void	ft_init_textures(t_game *game)
{
	ft_texture_load(game, &game->player, "./xpm/1player.xpm");
	ft_texture_load(game, &game->exit, "./xpm/1exit.xpm");
	ft_texture_load(game, &game->collectible, "./xpm/1collectable.xpm");
	ft_texture_load(game, &game->wall, "./xpm/1wall.xpm");
	ft_texture_load(game, &game->ground, "./xpm/1ground.xpm");
	/*
	ft_texture_load(game, &game->player, "./img/link1.xpm");
	ft_texture_load(game, &game->exit, "./img/tent.xpm");
	ft_texture_load(game, &game->collectible, "./img/key.xpm");
	ft_texture_load(game, &game->wall, "./img/wall.xpm");
	ft_texture_load(game, &game->ground, "./img/ground.xpm");
	*/
}

unsigned int	ft_get_pixel_mlx(t_img *img, int x, int y)
{
	return (*(unsigned int *)
		(img->data + (x * img->bpp / 8 + y * img->size_line)));
}

void	ft_draw_pixel_mlx(t_img *mlx_img, int x, int y, int color)
{
	char			*target;

	target = mlx_img->data + (x * mlx_img->bpp / 8 + y * mlx_img->size_line);
	*(unsigned int *)target = color;
}

unsigned int	ft_rgbtoi_mlx(int o, int r, int g, int b)
{
	return (o << 24 | r << 16 | g << 8 | b);
}

//moves

void	ft_down(t_game *game)
{
	char	*ptr;
	int		i;

	i = -1;
	if (!ft_strchr(game->map, 'p'))
		ptr = ft_strchr(game->map, 'P');
	else
		ptr = ft_strchr(game->map, 'p');
	while (++i < game->total_line_char)
		++ptr;
	if (*ptr != '1' && (*ptr != 'E' || *ptr != 'e'))
	{
		*ptr = 'P';
		ptr = ft_strchr(game->map, 'P');
		*ptr = '0';
		game->numb_move += 1;
		ft_putnbr_fd(game->numb_move, 1);
		write(1, "\n", 1);
	}
	mlx_destroy_image(game->mlx.mlx, game->player);
	ft_texture_load(game, &game->player, "./xpm/1player.xpm");
}

void	ft_up(t_game *game)
{
	char	*ptr;
	int		i;

	i = -1;
	if (!ft_strchr(game->map, 'p'))
		ptr = ft_strchr(game->map, 'P');
	else
		ptr = ft_strchr(game->map, 'p');
	while (++i < game->total_line_char)
		--ptr;
	if (*ptr != '1' && (*ptr != 'E' || *ptr != 'e'))
	{
		*ptr = 'P';
		while (--i >= 0)
			++ptr;
		*ptr = '0';
		game->numb_move += 1;
		ft_putnbr_fd(game->numb_move, 1);
		write(1, "\n", 1);
	}
	mlx_destroy_image(game->mlx.mlx, game->player);
	ft_texture_load(game, &game->player, "./xpm/1player.xpm");
}

void	ft_right(t_game *game)
{
	char	*ptr;

	if (!ft_strchr(game->map, 'p'))
		ptr = ft_strchr(game->map, 'P');
	else
		ptr = ft_strchr(game->map, 'p');
	if ((*++ptr != '1' && (*ptr != 'E' || *ptr != 'e')))
	{
		*--ptr = '0';
		*++ptr = 'P';
		game->numb_move += 1;
		ft_putnbr_fd(game->numb_move, 1);
		write(1, "\n", 1);
	}
	mlx_destroy_image(game->mlx.mlx, game->player);
	ft_texture_load(game, &game->player, "./xpm/1player.xpm");
}

void	ft_left(t_game *game)
{
	char	*ptr;

	if (!ft_strchr(game->map, 'p'))
		ptr = ft_strchr(game->map, 'P');
	else
		ptr = ft_strchr(game->map, 'p');
	if (*--ptr != '1' && (*ptr != 'E' || *ptr != 'e'))
	{
		*++ptr = '0';
		*--ptr = 'P';
		game->numb_move += 1;
		ft_putnbr_fd(game->numb_move, 1);
		write(1, "\n", 1);
	}
	mlx_destroy_image(game->mlx.mlx, game->player);
	ft_texture_load(game, &game->player, "./xpm/1player.xpm");
}

// keys
int	ft_exit(t_game *game)
{
	free(game->map);
	exit(1);
}

void	ft_game_completed(t_game *game)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (ft_strchr(game->map, 'E') == NULL || ft_strchr(game->map, 'e') == NULL)
	{
		if (game->nb_exit <= 1)
			if (ft_strchr(game->map, 'X') == NULL)
				ft_exit(game);
		while (game->map[i])
		{
			if (game->map[i] == 'X')
				count++;
			i++;
		}
		if (count == game->nb_exit - 1)
			ft_exit(game);
	}
}

int	ft_window_handling(t_game *game)
{
	ft_render_map(game);
	return (1);
}

int	ft_key_hook(int keycode, t_game *game)
{
	if (ft_strchr(game->map, 'C') == NULL)
	{
		while (ft_strchr(game->map, 'E'))
		{
			game->nb_exit++;
			*ft_strchr(game->map, 'E') = 'X';
		}
	}	
	if (keycode == 65307)
		ft_exit(game);
	if (keycode == 115 || keycode == 65364)
		ft_down(game);
	if (keycode == 119 || keycode == 65362)
		ft_up(game);
	if (keycode == 100 || keycode == 65363)
		ft_right(game);
	if (keycode == 97 || keycode == 65361)
		ft_left(game);
	ft_game_completed(game);
	ft_render_map(game);
	return (1);
}

// error handling
void	ft_error(char *nature, char *map_buff)
{
	ft_putstr_fd(nature, 2);
	free(map_buff);
	exit (0);
}

void	ft_verify_walls(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1')
		{
			ft_putstr_fd("map is not surrounded by walls\n", 2);
			free(line);
			exit (1);
		}
		i++;
	}
}

void	ft_check_map_elements(char *map_buff)
{
	int	i;
	int	count_p;

	i = 0;
	count_p = 0;
	while (map_buff[i] != '\0')
	{
		if (map_buff[i] == 'P' || map_buff[i] == 'p')
			count_p++;
		if (!((map_buff[i] == '1') || (map_buff[i] == '0')
			|| ((map_buff[i] == 'E') || (map_buff[i] == 'e'))
			|| ((map_buff[i] == 'P') || (map_buff[i] == 'p'))
			|| ((map_buff[i] == 'C') || (map_buff[i] == 'c'))))
		{
			ft_putstr_fd("Error\nUnrecognized  characters in '.ber' file.\n'", 2);
			write(2, &map_buff[i], 1);
			write(2, "'\n", 2);
			ft_putstr_fd("Allowed map items: (1; 0; P or p; E or e; C or c)\n", 2);
			free(map_buff);
			exit (1);
		}
		i++;
	}
	if (count_p > 1)
		ft_error("only one player should be on the map\n", map_buff);
}
