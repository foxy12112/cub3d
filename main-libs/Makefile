# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: petrasostaricvulic <petrasostaricvulic@    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 13:48:55 by ldick             #+#    #+#              #
#    Updated: 2025/03/10 07:45:51 by petrasostar      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libs.a

LIBFT_DIR = ./libft
GNL_DIR = ./get_next_line

LIBFTSRCS =	ft_atoi.c ft_atodbl.c ft_strcmp.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back_bonus.c \
			ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c \
			ft_lstsize_bonus.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
			ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c\
			ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
			ft_tolower.c ft_toupper.c ft_strlen_s.c ft_wordconut.c ft_atol.c ft_strcat.c

GNLSRCS = get_next_line.c get_next_line_utils.c

LIBFT_OBJS = $(addprefix $(LIBFT_DIR)/, $(LIBFTSRCS:.c=.o))
GNLOBJS = $(addprefix $(GNL_DIR)/, $(GNLSRCS:.c=.o))

OBJS = $(LIBFT_OBJS) $(GNLOBJS)

OBJDIR = ./objs

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

