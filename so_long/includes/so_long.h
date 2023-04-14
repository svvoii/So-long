/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:24:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/04/14 18:19:07 by sbocanci         ###   ########.fr       */
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

typedef struct s_mlx_ptr
{
	void	*mlx;
	void	*win;
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
	int		height;
	int		width;
	int		tile;
	/* game elements */
	int		c_count;
	int		p;
	int		p_x;
	int		p_y;
	int		t_x;
	int		t_y;
	int		e;
	int		e_x;
	int		e_y;
	int		key;
	/* index */
	int		w;
	int		h;
}	t_mlx;

/* main.c */

/* ft_map.c */
void	ft_map_to_array(t_mlx *m, char *file_path);
void	ft_validating_map(t_mlx *ptrs);
/* ft_free_and_destroy.c */
void	ft_free_and_destroy(t_mlx *ptrs, int status, char *msg);

#endif