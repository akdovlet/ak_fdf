# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 16:05:42 by akdovlet          #+#    #+#              #
#    Updated: 2024/01/07 22:39:27 by akdovlet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDE = libft.h

SRCS =	ak_countword.c		\
		ft_free_array.c		\
		ft_ischarset.c		\
		ft_multi_split.c	\
		ft_strndup.c		\
		ft_atoi.c			\
		ft_isascii.c		\
		ft_isalnum.c		\
		ft_isalpha.c		\
		ft_isdigit.c		\
		ft_isprint.c		\
		ft_split.c			\
		ft_strjoin.c		\
		ft_strdup.c			\
		ft_strlcpy.c		\
		ft_strlcat.c		\
		ft_strlen.c			\
		ft_strnstr.c		\
		ft_tolower.c		\
		ft_toupper.c		\
		ft_itoa.c			\
		ft_memcmp.c			\
		ft_memcpy.c			\
		ft_putstr_fd.c		\
		ft_putchar_fd.c		\
		ft_putnbr_fd.c		\
		ft_calloc.c			\
		ft_putendl_fd.c		\
		ft_strncmp.c		\
		ft_bzero.c			\
		ft_strchr.c			\
		ft_strrchr.c		\
		ft_memmove.c 		\
		ft_memset.c 		\
		ft_memchr.c 		\
		ft_substr.c 		\
		ft_strmapi.c 		\
		ft_striteri.c 		\
		ft_strtrim.c		\
		ft_lstnew_bonus.c	\
		ft_lstadd_front_bonus.c	\
		ft_lstsize_bonus.c		\
		ft_lstlast_bonus.c		\
		ft_lstadd_back_bonus.c	\
		ft_lstdelone_bonus.c	\
		ft_lstclear_bonus.c		\
		ft_lstiter_bonus.c		\
		ft_lstmap_bonus.c		\
		get_next_line.c			\
		get_next_line_utils.c	\
		get_next_line_multi.c
SRCS := $(addprefix srcs/, $(SRCS))
OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))

define AK
          :::     :::    :::   :::     ::::::::
       :+: :+:   :+:   :+:   :+:     :+:    :+:
     +:+   +:+  +:+  +:+   +:+ +:+        +:+
   +#++:++#++: +#++:++   +#+  +:+      +#+
  +#+     +#+ +#+  +#+ +#+#+#+#+#+  +#+
 #+#     #+# #+#   #+#      #+#   #+#
###     ### ###    ###     ###  ##########
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣠⣦⣤⣴⣤⣤⣄⣀⣀⣀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣤⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡀⠀⠀⣀⣀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣛⣛⣻⣿⣦⣀⠀⢀⣀⣀⣏⣹⠀
⢠⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠭⠭⠽⠽⠿⠿⠭⠭⠭⠽⠿⠿⠛
⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠉⢻⣿⣿⣿⡟⠏⠉⠉⣿⢿⣿⣿⣿⣇⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠉⠁⠀⠀⠀⢠⣿⣿⣿⠋⠑⠒⠒⠚⠙⠸⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⣿⣿⡿⠿⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠛⠛⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⢿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
endef
export AK

CC := cc
CFLAGS := -Wall -Werror -Wextra -MMD -MP -Iinclude

RM = rm -rf

all: create_dirs $(NAME)

title:
	@echo "$$AK"

create_dirs:
	@if [ ! -d "objs" ]; then mkdir objs; fi

objs/%.o: srcs/%.c
		@printf "\033[0;32%sm\tCompiling: $<\033[0m\n";
		@$(CC) $(CFLAGS) -c $< -o $@;

clean:
	@if [ -d "objs" ]; then rm -rf objs && echo "\033[1;31mLibft .o files have been deleted\033[0m"; fi

fclean: clean
	@if [ -f "libft.a" ]; then rm -rf libft.a  && echo "\033[1;31mLibft .a file has been deleted\033[0m"; fi

re: fclean all

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

-include $(DEPS)

.PHONY: all clean fclean re create_dirs title
