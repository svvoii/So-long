/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:24:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/04/08 15:30:53 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include "libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"

# define PIX 32
# define BUFF_SIZE 1024
# define W '1'
# define G '0'
# define E 'E'
# define C 'C'
# define P 'P'

typedef struct s_mlx_ptr
{
	void	*mlx;
	void	*win;
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

/* main.c */

/* ft_map.c */
void	ft_map_to_array(t_mlx *m, char *file_path);
void	ft_validating_map(t_mlx *ptrs);
/* ft_free_and_destroy.c */
void	ft_free_and_destroy(t_mlx *ptrs, int status, char *msg);

#endif