# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 17:40:09 by sbocanci          #+#    #+#              #
#    Updated: 2023/04/07 15:27:25 by sbocanci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

libft = includes/libft/ft_putstr_fd.c includes/libft/ft_strlen.c includes/libft/ft_strcat.c \
	includes/libft/ft_strchr.c includes/libft/ft_strdup.c includes/libft/ft_strjoin.c \
	includes/libft/ft_strlcpy.c includes/libft/ft_substr.c includes/libft/ft_strncmp.c \
	includes/libft/ft_putnbr_fd.c includes/libft/ft_strrchr.c includes/libft/ft_putchar_fd.c \
	includes/libft/ft_split.c

#src = sources/main_06042023.c
#src = sources/main_05042023.c
src = sources/main.c sources/ft_map.c sources/ft_free_and_exit.c

#src_b = bonus/checker.c bonus/execute.c bonus/get_next_line.c\
	sources/push_swap.c sources/stack.c sources/stack_instructions.c

lib_obj = $(includes/libft:.c=.o)

obj = $(sources:.c=.o)

#obj_b = $(src_b:.c=.o)

flags =#-Wall -Wextra -Werror

Lmlx = -L/mnt/nfs/homes/sbocanci/Documents/42cursus/So-long/so_long/includes/mlx/ -lmlx -lXext -lX11
#frame = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(src) $(obj) $(lib_obj)#includes/so_long.h includes/libft.h
	@gcc -g $(flags) $(src) $(libft) $(Lmlx) -o $(NAME)
	@echo ------Compiled Mondatory part-------

#bonus: $(NAME_B)

#$(NAME_B): $(src_b) $(obj_b) $(lib_obj) includes/checker.h includes/libft.h
#	@gcc $(flags) $(src_b) $(libft) -o $(NAME_B)
#	@echo ------Compiled Bonus part-------

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
	