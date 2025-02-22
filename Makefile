# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: foxy <foxy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/18 19:28:14 by ldick             #+#    #+#              #
#    Updated: 2025/02/22 17:08:29 by foxy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

#################################################################################################
#											Colors												#
#################################################################################################

CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
BOLD_BLUE	:= \033[0;34m
NC			:= \033[0m

#################################################################################################
#											Flags												#
#################################################################################################

COMPILER	=	cc
INCLUDES	=	-I includes -I main-libs
SUBMODULE	=	main-libs/Makefile
LIB_FLAGS	=	-ls -Lmain-libs ./MLX42/build/libmlx42.a
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address
EXTRA_FLAGS	=	-O3 -ffast-math
ERROR_FILE	=	error.log

#################################################################################################
#											Sources												#
#################################################################################################

_PARSING		=	parsing_utils.c parsing.c map_parse_utils.c
PARSING			=	$(addprefix parsing/, $(_PARSING))

_MATH			=	color.c raytracing.c
MATH			=	$(addprefix math/, $(_MATH))

_UTILS			=	init.c init_utils.c tmp.c ft_ftoa.c
UTILS			=	$(addprefix utils/, $(_UTILS))

_ERROR			=	error_utils.c error.c
ERROR			=	$(addprefix error/, $(_ERROR))

_GAME			=	game.c event.c map/map.c player/player.c rendering/render.c
GAME			=	$(addprefix game/, $(_GAME))

_SRCS			=	cub3d.c $(ERROR) $(UTILS) $(MATH) $(PARSING) $(GAME)
SRCS			=	$(addprefix srcs/, $(_SRCS))

OBJS			=	$(SRCS:srcs/%.c=bin/%.o)
LIBRARY			=	main-libs/libs.a

#################################################################################################
#											MLX													#
#################################################################################################

USER = $(shell whoami)
OS = $(shell uname)
# OS = ("MINISHELL");

ifeq ($(OS),Linux)
		MLX_FLAGS = MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
else ifeq ($(OS),Darwin)
		MLX_FLAGS = -framework Cocoa -framework OpenGl -framework IOKit -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib"
endif

#################################################################################################
#											Rules												#
#################################################################################################

all:			MLX42 $(NAME)

bin:
				@echo "\t\t\t$(BLUE) Making bin directory"
				@mkdir -p bin/utils
				@mkdir -p bin/math
				@mkdir -p bin/error
				@mkdir -p bin/parsing
				@mkdir -p bin/game/map
				@mkdir -p bin/game/player
				@mkdir -p bin/game/rendering

bin/%.o:		srcs/%.c | bin
				@echo "$(GREEN) Compiling $(Compiler) $(CLR_RMV) -c -o $(YELLOW) $@ $(CYAN) $^ $(GREEN) $(EXTRA_FLAGS) $(CFLAGS) $(GREEN) $(INCLUDES) $(NC)"
				@$(COMPILER) -c -o $@ $^ $(EXTRA_FLAGS) $(CFLAGS) $(INCLUDES) 2> $(ERROR_FILE) || (cat $(ERROR_FILE) && echo "$(RED)Compilation failed :0\nfailed file: \t\t$(YELLOW)$<$(NC)\n\n" && exit 1$(NC))

$(LIBRARY):		$(SUBMODULE)
				@make -C main-libs --silent

$(SUBMODULE):
				@git submodule update --init --recursive

$(NAME): $(LIBRARY) $(OBJS)
				@$(COMPILER) -o $(NAME) $(OBJS) $(LIB_FLAGS) $(MLX_FLAGS) $(EXTRA_FLAGS) $(CFLAGS)
				@echo "\t\t\t\t$(RED) compilation success :3$(NC)"
				@mkdir -p .git/permanent_history

MLX42:
				@if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
				@cd MLX42 && cmake -B build && cmake --build build -j4

clean:
				@rm -rf bin
				@rm -f $(ERROR_FILE)
				@make fclean -C main-libs --silent

fclean:			clean
				@rm -f $(NAME)
				@rm -rf MLX42

history:		clean
				@rm -rf .git/permanent_history

re:				fclean all

re_s:			clean all

.PHONY:			all clean fclean re