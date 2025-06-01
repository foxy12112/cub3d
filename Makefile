# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldick <ldick@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/18 19:28:14 by ldick             #+#    #+#              #
#    Updated: 2025/06/01 13:39:03 by ldick            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

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
LIB_FLAGS = -Lmain-libs -ls -L./MLX42/build -lmlx42
CFLAGS		=	-g  -Wall -Werror -Wextra #-fsanitize=address
EXTRA_FLAGS	=	#-ffast-math #-0fast
ERROR_FILE	=	error.log

#################################################################################################
#											Sources												#
#################################################################################################

_RAYCASTING		=	raycasting.c raycasting_utils.c
RAYCASTING		=	$(addprefix raycasting/, $(_RAYCASTING))

_GAME			=	event_utils.c event.c game.c movement.c
GAME			=	$(addprefix game/, $(_GAME))

_DRAWING		=	drawing_utils.c drawing.c
DRAWING			=	$(addprefix drawing/, $(_DRAWING))

_INIT			=	init_utils.c init.c parsing_utils.c parsing.c validate.c texture_utils.c
INIT			=	$(addprefix init/, $(_INIT))

_UTILS			=	utils.c
UTILS			=	$(addprefix utils/, $(_UTILS))

_SRCS			=	cub3d.c $(UTILS) $(INIT) $(DRAWING) $(GAME) $(RAYCASTING)
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
				@mkdir -p bin/init
				@mkdir -p bin/drawing
				@mkdir -p bin/game
				@mkdir -p bin/raycasting

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

MLX42:
				@if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
				@cd MLX42 && cmake -B build -DDEBUG=1 && cmake --build build -j4

clean:
				@rm -rf bin
				@rm -f $(ERROR_FILE)
				@make fclean -C main-libs --silent

fclean:			clean
				@rm -f $(NAME)
				@rm -rf MLX42

soft_clean:
				@rm -f $(NAME)
				@rm -rf bin

re:				fclean all

res:			soft_clean all

run:			all
				@./$(NAME) maps/empty.cub

.PHONY:			all clean fclean re
