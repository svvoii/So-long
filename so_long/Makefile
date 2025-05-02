# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 17:40:09 by sbocanci          #+#    #+#              #
#    Updated: 2023/05/08 14:38:51 by sbocanci         ###   ########.fr        #
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

flags = -Wall -Wextra -Werror -I/Users/serge/LINUX/GITHUB_TMP/So-long/so_long/includes -I/opt/X11/include # MACOS (change path to your `libmlx.a` and X11 !!!) X11 must be installed
# flags = -Wall -Wextra -I/usr/local/include -I/opt/X11/include -Iincludes # MACOS (use this path if libmlx.a is in `/usr/local/include/libmlx.a` and change path to your X11 (if needed) !!!)

Lmlx = -L/Users/serge/LINUX/GITHUB_TMP/So-long/so_long/includes -L/opt/X11/lib -lmlx -lXext -lX11 -lm
# Lmlx = -L/usr/local/lib -lmlx -L/usr/X11/lib -lXext -lX11 -lm # LINUX
# Lmlx = -L/mnt/nfs/homes/sbocanci/Documents/42cursus/So-long/so_long/includes/mlx/ -lmlx -lXext -lX11 # LINUX (42 dump)

all: $(NAME)

$(NAME): $(src) $(obj) $(lib_obj)
	@gcc -v $(flags) $(src) $(libft) $(Lmlx) -o $(NAME)
# @gcc -g $(flags) $(src) $(libft) $(Lmlx) -o $(NAME)
	@echo ------Compiled Mondatory part-------

bonus: $(NAME_B)
$(NAME_B): $(src_b) $(obj_b) $(lib_obj)
	@gcc $(flags) $(src_b) $(libft) $(Lmlx) -o $(NAME_B)
	@echo ------Compiled Bonus part-------

%.o: %.c
	@gcc $(flags) -c $< -o $@
	@echo ------Compiling Objects files-------

clean:
	@rm -rf $(obj) $(obj_b) $(lib_obj)
	@echo ------Deleting Objects Files-------

fclean: clean
	@rm -rf $(NAME) $(NAME_B)
	@echo ------Deleting Output Files-------

re: fclean all
	