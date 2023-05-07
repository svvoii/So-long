# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 17:40:09 by sbocanci          #+#    #+#              #
#    Updated: 2023/05/07 14:34:23 by svoi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
NAME_B = so_long_bonus

libft = includes/libft/ft_putstr_fd.c includes/libft/ft_strlen.c includes/libft/ft_strdup.c \
	includes/libft/ft_strjoin.c includes/libft/ft_putnbr_fd.c includes/libft/ft_putchar_fd.c \
	includes/libft/ft_bzero.c includes/libft/ft_memcpy.c includes/libft/ft_split.c

src = sources/main.c sources/map_setting.c sources/validating_map.c sources/upload_sprites.c \
	sources/free_and_exit.c sources/render_sprites.c sources/helpers.c sources/bfs.c \

src_b = sources/bonus_main.c sources/map_setting.c sources/validating_map.c sources/upload_sprites.c \
	sources/free_and_exit.c sources/render_sprites.c sources/helpers.c sources/bfs.c \
	sources/bonus_spawn_enemies.c sources/bonus_set_enemy_direction.c sources/bonus_update_enemy.c

lib_obj = $(includes/libft:.c=.o)

obj = $(src:.c=.o)
obj_b = $(src_b:.c=.o)

flags = -Wall -Wextra -Werror

#Lmlx = -L/home/svoi/Documents/So-long/so_long/includes/mlx/ -lmlx -lXext -lX11
Lmlx = -L/mnt/nfs/homes/sbocanci/Documents/42cursus/So-long/so_long/includes/mlx/ -lmlx -lXext -lX11

all: $(NAME)

$(NAME): $(src) $(obj) $(lib_obj)
	@gcc -g $(flags) $(src) $(libft) $(Lmlx) -o $(NAME)
	@echo ------Compiled Mondatory part-------

bonus: $(NAME_B)
$(NAME_B): $(src_b) $(obj_b) $(lib_obj)
	@gcc $(flags) $(src_b) $(libft) $(Lmlx) -o $(NAME_B)
	@echo ------Compiled Bonus part-------

%.o: %.c
	@gcc -c $< -o $@
	@echo ------Compiling Objects files-------

clean:
	@rm -rf $(obj) $(obj_b) $(lib_obj)
	@echo ------Deleting Objects Files-------

fclean: clean
	@rm -rf $(NAME) $(NAME_B)
	@echo ------Deleting Output Files-------

re: fclean all
	