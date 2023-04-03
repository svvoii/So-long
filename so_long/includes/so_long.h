/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:24:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/04/03 18:55:18 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include "libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"

# define PIX 32

typedef struct s_map
{
	char	*raw;
	char	**map;
	int		height;
	int		width;
	int		tile;
}	t_map;

typedef struct s_mlx_ptr
{
	void	*mlx;
	void	*win;
	t_map	*m;
}	t_mlx;

typedef struct s_game
{
	t_mlx	*ptr;
	t_map	*m;
	int		c_count;
	int		p_x;
	int		p_y;
}	t_game;

/* main.c */

/* ft_map */
void	*ft_map_to_array(t_map *m, char *file_path);

#endif