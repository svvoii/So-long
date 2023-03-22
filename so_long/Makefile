# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 17:40:09 by sbocanci          #+#    #+#              #
#    Updated: 2023/03/22 16:41:28 by sbocanci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

#libft = libft/ft_bzero.c libft/ft_putchar_fd.c libft/ft_split.c\
	libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strncmp.c libft/ft_memcpy.c\
	libft/ft_putstr_fd.c libft/ft_strchr.c libft/ft_streq.c libft/ft_strlen.c\
	libft/ft_substr.c

src = sources/main.c 

#src_b = bonus/checker.c bonus/execute.c bonus/get_next_line.c\
	sources/push_swap.c sources/stack.c sources/stack_instructions.c

#lib_obj = $(libft:.c=.o)

obj = $(src:.c=.o)

#obj_b = $(src_b:.c=.o)

flags =#-Wall -Wextra -Werror

Lmlx = -L/mnt/nfs/homes/sbocanci/Documents/42cursus/So-long/so_long/includes/mlx/ -lmlx -lXext -lX11

all: $(NAME)

$(NAME): $(src) $(obj)#$(lib_obj) includes/push_swap.h includes/libft.h
	@gcc $(flags) $(src) $(Lmlx) -o $(NAME)
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
	