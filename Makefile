# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/19 15:35:14 by mhonchar          #+#    #+#              #
#    Updated: 2019/05/09 17:34:49 by mhonchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
LIB_NAME = libft.a
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = includes/
LIB_DIR = libft/

LIB = $(addprefix $(LIB_DIR), $(LIB_NAME))

SRC_FILES =		main.c \
				input_handler.c \
				utils.c \
				mandelbrot.c \
				julia.c \
				bship.c \
				spinner.c \
				fish.c \
				flower.c \
				heart.c \
				splash.c \
				mouse_handler.c


HEADERS = $(INC_DIR)fractol.h $(LIB_DIR)libft.h

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

CC = gcc -g
CFLAGS = -Wall -Werror -Wextra
INC = -I $(INC_DIR) -I $(LIB_DIR)
FRAMEWORKS = -lmlx -framework OpenGL -framework Appkit
C_RED = \033[31m
C_GREEN = \033[32m
C_MAGENTA = \033[35m
C_NONE = \033[0m

all: $(NAME)

$(NAME): $(HEADERS) $(OBJ_DIR) $(OBJ)
	@make -C $(LIB_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(FRAMEWORKS) -o $(NAME)
	@printf "$(C_MAGENTA)FDF:$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR):
	@mkdir obj
	@printf "$(C_MAGENTA)FDF:$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "$(C_MAGENTA)FDF:$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

clean:
	@rm -rf $(OBJ_DIR)*
	@make fclean -C $(LIB_DIR)
	@printf "$(C_MAGENTA)FDF:$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_DIR)
	@printf "$(C_MAGENTA)FDF:$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all

norm:
	@norminette $(SRC) $(HEADERS)
