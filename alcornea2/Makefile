# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/01 20:44:23 by alcornea          #+#    #+#              #
#    Updated: 2017/07/07 15:16:00 by alcornea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), test, clean, fclean, re

NAME= ft_select

CC= gcc -g

CFLAGS+= -Wall -Wextra -Werror

SRC_PATH= src/
INC_PATH= includes/
OBJ_PATH= obj/
LIBFT_PATH= libft/

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I ,$(INC_PATH))
INC_LFT = $(addprefix -I ,$(addprefix $(LIBFT_PATH), $(INC_PATH)))

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_NAME = main.c \
					ft_select.c \
					ft_print.c \
					ft_keyhook.c \
					ft_window.c \
					ft_signal.c \

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft -ltermcap

	@echo "\033[1;32m$(NAME) has been created!\n\\033[0;39m\\033[1;31mRun: ./ft_select [arg1] [arg2] ...\\033[0;39m"


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) $(INC_LFT) -o $@ -c $<

test: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all
