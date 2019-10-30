# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/19 14:03:15 by jgourdin          #+#    #+#              #
#    Updated: 2019/10/30 16:16:59 by mguerrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test.filler

SRC_NAME = main.c place.c utils.c get_elems.c

INC_NAME = filler.h

INC_PATH = ./includes

INC_FLAGS = -I./includes -I./libft/includes

LIB_FLAGS = -L./libft

LIBS = -lft -lncurses

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

SRC_PATH = src

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = obj

OBJ_NAME = $(SRC:.c=.o)

OBJ = $(subst $(SRC_PATH),$(OBJ_PATH),$(OBJ_NAME))

INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

RED = \x1B[31m
GRN = \x1B[32m
YEL = \x1B[33m
BLU = \x1B[34m
MAG = \x1B[35m
CYN = \x1B[36m
WHT = \x1B[37m
RESET = \x1B[0m
ERASE = \033[2K

all: $(NAME)

libftmake:
	@make -C ./libft --no-print-directory

$(NAME): $(OBJ) | libftmake
	@$(CC) $(LIB_FLAGS) $(LIBS) -o $@ $(OBJ)
	@echo "\n$(BLU)[$(NAME)]$(GRN) Compilation success$(RESET)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ -c $<
	@echo "\r$(ERASE)$(BLU)[$(NAME)]$(RESET) $@ created\c"

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf $(OBJ_PATH)
	@make -C ./libft clean --no-print-directory
	@echo "$(BLU)[$(NAME)]$(RED) .o files deleted$()$(RESET)"

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(LINKNAME)
	@make -C ./libft fclean --no-print-directory
	@echo  "$(BLU)[$(NAME)]$(RED) executable file deleted$(RESET)"

re: fclean $(NAME)

.PHONY: all, clean, fclean, re, lib
