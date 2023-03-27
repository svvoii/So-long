/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mlx_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:21:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/03/27 18:31:14 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/mlx/mlx.h"

/*
int	deal_key(int key, void *param);
void	ft_putchar(char	c);

int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 700, 400, "test_window");
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

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_game
{
	t_mlx	mlx;
	int		map_width;
	int		map_height;
	int		numb_move;
	t_img	*ground;
	t_img	*player;
	t_img	*collectible;
	t_img	*tree;
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

void			texture_load(t_game *game, t_img **img, char *path);
void			check_arg(int argc, char **argv);
int				key_hook(int keycode, t_game *game);
void			check_walls(char *line);
void			check_map_elements(char *whole_chars);
int				init_struc(t_game *game);
int				init_map(t_game *game, char *map_name);
void			draw_map(t_game *game);
void			draw_square(t_game *game, t_img *img, int x, int y);
unsigned int	mlx_get_pixel(t_img *img, int x, int y);
void			mlx_draw_pixel(t_img *mlx_img, int x, int y, int color);
unsigned int	mlx_rgb_to_int(int o, int r, int g, int b);
void			check_for_elements(t_game *game, int x, int y, int z);
int				exit_hook(t_game *game);
void			move_bottom(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			move_up(t_game *game);
void			is_game_finished(t_game *game);
void			texture_init(t_game *game);
int				reduce_window(t_game *game);
void			problems(char *nature, char *whole_chars);


int	main(int argc, char **argv)
{
	t_game	game;

	check_arg(argc, argv);
	init_map(&game, argv[1]);
	init_struc(&game);
	draw_map(&game);
	mlx_key_hook(game.mlx.mlx_win, key_hook, &game);
	mlx_hook(game.mlx.mlx_win, 33, 1L << 5, exit_hook, &game);
	mlx_hook(game.mlx.mlx_win, 15, 1L << 16, reduce_window, &game);
	mlx_loop(game.mlx.mlx);

	return (0);
}

void	check_arg(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("Error\nInvalid number of argument", 2);
		exit(0);
	}
	if ((ft_strlen(argv[1]) < 4) || (!ft_strrchr(argv[1], '.')))
	{
		ft_putendl_fd("Error\ninvalid argument", 2);
		exit(0);
	}
	if (ft_strcmp(ft_strrchr(argv[1], '.'), ".ber") != 0)
	{
		ft_putendl_fd("Error\nfile must be of type \"<name>.ber\"", 2);
		exit(0);
	}
}

int	init_map(t_game *game, char *map_name)
{
	char	*line;
	int		ret;
	char	*whole_chars;

	whole_chars = malloc(sizeof(char) * 10000);
	*whole_chars = 0;
	game->line_number = 0;
	game->fd = open(map_name, O_RDONLY);
	if (game->fd == -1)
		problems("Error\nfile cannot be read", whole_chars);
	line = 0;
	ret = get_next_line(game->fd, &line);
	check_walls(line);
	game->total_line_char = strlen(line);
	deal_ret(ret, game, line, whole_chars);
	init_map2(game, whole_chars);
	return (1);
}

void	init_map2(t_game *game, char *whole_chars)
{
	if ((ft_strchr(whole_chars, 'P') == NULL)
		|| (ft_strchr(whole_chars, 'E') == NULL)
		|| (ft_strchr(whole_chars, 'C') == NULL))
		problems("Error\nMissing one player, one collectible or one exit",
			whole_chars);
	if (game->line_number - 1 == game->total_line_char)
		problems("Error\nMap is square!", whole_chars);
	check_map_elements(whole_chars);
	game->map_height = (game->line_number - 1) * 40;
	game->map_width = game->total_line_char * 40;
	game->map = malloc(sizeof(char) * (game->total_line_char * game->line_number) + 1);
	ft_strlcpy(game->map, whole_chars, (game->line_number * game->total_line_char));
	game->fd = close(game->fd);
	free(whole_chars);
}

void	deal_ret(int ret, t_game *game, char *line, char *whole_chars)
{
	while (ret > 0)
	{
		game->line_number++;
		game->endline = ft_strlen(line) - 1;
		if (line[0] != '1' || line[game->endline] != '1')
			problems("Error\nWall missing in the border", whole_chars);
		ft_strcat(whole_chars, line);
		free(line);
		line = 0;
		ret = get_next_line(game->fd, &line);
		if ((ret != 0) && (strlen(line) != (long unsigned int)game->total_line_char))
			problems("Error\nmap has a problem", whole_chars);
		if (ret == 0)
		{
			game->line_number++;
			check_walls(line);
			ft_strcat(whole_chars, line);
			free(line);
			line = 0;
		}
	}
}

int	init_struc(t_game *game)
{
	game->nb_exit = 0;
	game->numb_move = 0;
	game->mlx.mlx = mlx_init();
	game->mlx.mlx_win = mlx_new_window(game->mlx.mlx, game->map_width, game->map_height, "SO_LONG_EDJ");
	game->mlx.mlx_img = mlx_new_image(game->mlx.mlx, game->map_width, game->map_height);
	texture_init(game);
	return (1);
}

// draw map
void	draw_map(t_game *game)
{
	int	z;

	game->numb = 0;
	game->y = 0;
	game->x = -40;
	while (game->y < (game->line_number - 1))
	{
		z = 0;
		while (z < game->total_line_char)
		{
			if (game->map[z + game->numb] == '1')
				draw_square(game, game->tree, game->x += 40, game->y * 39);
			else
			{
				draw_square(game, game->ground, game->x += 40, game->y * 39);
				check_for_elements(game, game->x, game->y, z);
			}
			z++;
		}
		game->y++;
		game->numb = game->total_line_char * game->y;
	}
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.mlx_win,
		game->mlx.mlx_img, 0, 0);
}

void	draw_square(t_game *game, t_img *img, int x, int y)
{
	unsigned int	color;
	int				i;
	int				j;

	j = 0;
	while (j < 40)
	{
		i = 0;
		while (i < 40)
		{
			color = mlx_get_pixel(img, i, j);
			if (color != mlx_rgb_to_int(0, 255, 255, 255))
				mlx_draw_pixel(game->mlx.mlx_img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	check_for_elements(t_game *game, int x, int y, int z)
{
	if (game->map[z + game->numb] == 'P')
		draw_square(game, game->player, x, y * 39);
	if (game->map[z + game->numb] == 'C')
		draw_square(game, game->collectible, x, y * 39);
	if (game->map[z + game->numb] == 'E' || game->map[z + game->numb] == 'X')
		draw_square(game, game->exit, x, y * 39);
}

// helpers
void	texture_load(t_game *game, t_img **img, char *path)
{
	int				width;
	int				height;

	*img = mlx_xpm_file_to_image(game->mlx.mlx, path, &width, &height);
	if (*img == 0)
		ft_putendl_fd("Error\nCan't load texture", 2);
	(*img)->width = width;
	(*img)->height = height;
}

void	texture_init(t_game *game)
{
	texture_load(game, &game->player, "./img/link1.xpm");
	texture_load(game, &game->exit, "./img/tent.xpm");
	texture_load(game, &game->collectible, "./img/key.xpm");
	texture_load(game, &game->tree, "./img/tree.xpm");
	texture_load(game, &game->ground, "./img/ground.xpm");
}

unsigned int	mlx_get_pixel(t_img *img, int x, int y)
{
	return (*(unsigned int *)
		(img->data + (x * img->bpp / 8 + y * img->size_line)));
}

void	mlx_draw_pixel(t_img *mlx_img, int x, int y, int color)
{
	char			*target;

	target = mlx_img->data + (x * mlx_img->bpp / 8 + y * mlx_img->size_line);
	*(unsigned int *)target = color;
}

unsigned int	mlx_rgb_to_int(int o, int r, int g, int b)
{
	return (o << 24 | r << 16 | g << 8 | b);
}

//moves

void	move_bottom(t_game *game)
{
	char	*ptr;
	int		i;

	ptr = strchr(game->map, 'P');
	i = -1;
	while (++i < game->total_line_char)
		++ptr;
	if (*ptr != '1' && *ptr != 'E')
	{
		*ptr = 'P';
		ptr = ft_strchr(game->map, 'P');
		*ptr = '0';
		game->numb_move += 1;
		ft_putnbr_fd(game->numb_move, 1);
		ft_putchar_fd('\n', 1);
	}
	mlx_destroy_image(game->mlx.mlx, game->player);
	texture_load(game, &game->player, "./img/link1.xpm");
}

void	move_up(t_game *game)
{
	char	*ptr;
	int		i;

	i = -1;
	ptr = ft_strchr(game->map, 'P');
	while (++i < game->total_line_char)
		--ptr;
	if (*ptr != '1' && *ptr != 'E')
	{
		*ptr = 'P';
		while (--i >= 0)
			++ptr;
		*ptr = '0';
		game->numb_move += 1;
		ft_putnbr_fd(game->numb_move, 1);
		ft_putchar_fd('\n', 1);
	}
	mlx_destroy_image(game->mlx.mlx, game->player);
	texture_load(game, &game->player, "./img/link_up.xpm");
}

void	move_right(t_game *game)
{
	char	*ptr;

	ptr = ft_strchr(game->map, 'P');
	if ((*++ptr != '1' && *ptr != 'E'))
	{
		*--ptr = '0';
		*++ptr = 'P';
		game->numb_move += 1;
		ft_putnbr_fd(game->numb_move, 1);
		ft_putchar_fd('\n', 1);
	}
	mlx_destroy_image(game->mlx.mlx, game->player);
	texture_load(game, &game->player, "./img/link_right.xpm");
}

void	move_left(t_game *game)
{
	char	*ptr;

	ptr = ft_strchr(game->map, 'P');
	if (*--ptr != '1' && *ptr != 'E')
	{
		*++ptr = '0';
		*--ptr = 'P';
		game->numb_move += 1;
		ft_putnbr_fd(game->numb_move, 1);
		ft_putchar_fd('\n', 1);
	}
	mlx_destroy_image(game->mlx.mlx, game->player);
	texture_load(game, &game->player, "./img/link_left.xpm");
}

// keys
int	exit_hook(t_game *game)
{
	free(game->map);
	exit(1);
}

void	is_game_finished(t_game *game)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (ft_strchr(game->map, 'E') == NULL)
	{
		if (game->nb_exit <= 1)
			if (ft_strchr(game->map, 'X') == NULL)
				exit_hook(game);
		while (game->map[i])
		{
			if (game->map[i] == 'X')
				count++;
			i++;
		}
		if (count == game->nb_exit - 1)
			exit_hook(game);
	}
}

int	reduce_window(t_game *game)
{
	draw_map(game);
	return (1);
}

int	key_hook(int keycode, t_game *game)
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
		exit_hook(game);
	if (keycode == 115 || keycode == 65364)
		move_bottom(game);
	if (keycode == 119 || keycode == 65362)
		move_up(game);
	if (keycode == 100 || keycode == 65363)
		move_right(game);
	if (keycode == 97 || keycode == 65361)
		move_left(game);
	is_game_finished(game);
	draw_map(game);
	return (1);
}

// error handling
void	problems(char *nature, char *whole_chars)
{
	ft_putendl_fd(nature, 2);
	free(whole_chars);
	exit (0);
}

void	check_walls(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1')
		{
			ft_putendl_fd("map is not surrounded by walls", 2);
			free(line);
			exit (1);
		}
		i++;
	}
}

void	check_map_elements(char *whole_chars)
{
	int	i;
	int	count_p;

	i = 0;
	count_p = 0;
	while (whole_chars[i] != '\0')
	{
		if (whole_chars[i] == 'P')
			count_p++;
		if ((whole_chars[i] != '1') && (whole_chars[i] != '0')
			&& (whole_chars[i] != 'E') && (whole_chars[i] != 'P')
			&& (whole_chars[i] != 'C'))
		{
			ft_putendl_fd
			("Error\nFile contains different character than 1, 0, P, E or C", 2);
			free(whole_chars);
			exit (1);
		}
		i++;
	}
	if (count_p > 1)
		problems("only one player should be on the map", whole_chars);
}
