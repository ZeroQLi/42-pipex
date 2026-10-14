# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/02 18:11:16 by mtangalv          #+#    #+#              #
#    Updated: 2025/08/14 21:03:14 by mtangalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus

CFILES = src/pipex.c \
	src/parse.c \
	utils/errs.c \
	utils/utils.c

CFILES_BONUS = src/pipex.c \
	src/parse.c \
	utils/errs.c \
	utils/utils.c

OBJECTS = $(CFILES:.c=.o)
OBJECTS_BONUS = $(CFILES_BONUS:.c=.o)

LIBFT_PATH = libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: subsystems $(NAME)

bonus: subsystems $(BONUS_NAME)

subsystems:
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJECTS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_FLAGS) -o $(NAME)

# Bonus target
$(BONUS_NAME): $(OBJECTS_BONUS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJECTS_BONUS) $(LIBFT_FLAGS) -o $(BONUS_NAME)

clean:
	make clean -C libft/
	rm -rf $(OBJECTS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all

re_bonus: fclean bonus

.PHONY:	all clean fclean re bonus re_bonus
