# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 13:57:12 by akdovlet          #+#    #+#              #
#    Updated: 2024/01/14 18:58:24 by akdovlet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

.EXTRA_PREREQS:= $(abspath $(lastword $(MAKEFILE_LIST)))

LIBFT	= 	libft/libft.a
PRINTF	=	printf/libftprintf.a
MLX 	=	mlx_linux/libmlx.a

SRCS :=		parsing.c	\
			get_file.c
SRCS := 	$(addprefix source/, $(SRCS))
OBJS := 	$(patsubst source/%.c, object/%.o, $(SRCS))
DEPS := 	$(OBJS:.o=.d)


CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP -Iinclude -Ilibft/include -Iprintf/include -Imlx_linux

all: create_dirs $(NAME)

# ifeq (run, $(firstword $(MAKECMDGOALS)))
# 	runargs := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
# 	$(eval $(runargs):;@true)
# endif

$(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux $(PRINTF) $(LIBFT) -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

object/%.o: source/%.c
	@printf "\033[0;32%sm\tCompiling: $<\033[0m\n";
	@$(CC) $(CFLAGS) -c $< -o $@

create_dirs:
	@if [ ! -d "object" ]; then mkdir object; fi

$(LIBFT):
	@$(MAKE) -sC libft

$(PRINTF):
	@$(MAKE) -sC printf

$(MLX):
	@$(MAKE) -sC mlx_linux

# run: $(NAME)
# 	./fdf $(runargs)

clean:
	@if [ -d "object" ]; then rm -rf object && echo "\033[1;31mFdf .o files have been deleted\033[0m"; fi
	@$(MAKE) --no-print-directory clean -C libft
	@$(MAKE) --no-print-directory clean -C printf
	@$(MAKE) --no-print-directory clean -C mlx_linux

fclean: clean
	@if [ -f "fdf" ]; then rm -rf fdf && echo "\033[1;31mFdf executable has been deleted\033[0m"; fi
	@$(MAKE) --no-print-directory fclean -C libft
	@$(MAKE) --no-print-directory fclean -C printf

re: fclean all

-include $(DEPS)

.PHONY: all create_dirs clean fclean
