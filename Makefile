# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/19 15:35:14 by mhonchar          #+#    #+#              #
#    Updated: 2019/03/24 20:07:58 by mhonchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
LIBFT_NAME = libft.a
LIBMLX_NAME = libmlx.a
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = includes/
LIBFT_DIR = libft/
LIBMLX_DIR = libmlx/
LIB = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME)) $(addprefix $(LIBMLX_DIR), $(LIBMLX_NAME))

SRC_FILES =		main.c \
				input_handler.c \
				utils.c \
				mandelbrot.c \
				julia.c

HEADERS = $(INC_DIR)fractol.h $(LIBFT_DIR)libft.h $(LIBMLX_DIR)mlx.h

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))


CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -I $(INC_DIR) -I $(LIBFT_DIR) -I $(LIBMLX_DIR)
FRAMEWORKS = -lXext -lX11  -pthread
C_RED = \033[31m
C_GREEN = \033[32m
C_MAGENTA = \033[35m
C_NONE = \033[0m



all: $(NAME)


$(NAME): $(HEADERS) $(OBJ_DIR) $(OBJ)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(FRAMEWORKS) -o $(NAME) -lm
	@printf "$(C_MAGENTA)FDF:$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR):
	@mkdir obj
	@printf "$(C_MAGENTA)FDF:$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "$(C_MAGENTA)FDF:$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

clean:
	@rm -rf $(OBJ_DIR)*
	@make fclean -C $(LIBFT_DIR)
	@printf "$(C_MAGENTA)FDF:$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@printf "$(C_MAGENTA)FDF:$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all

norm:
	@norminette $(SRC) $(HEADERS)
