# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 18:45:21 by kbarru            #+#    #+#              #
#    Updated: 2025/04/08 17:21:22 by kbarru           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
FLAGS = -Werror -Wextra -Wall -g
DEBUG_FLAGS = -g -fsanitize=address

OBJ_DIR = .obj/
SRC_DIR = src/
HEADER_DIR = inc/
LIBFT_DIR = lib/libft/
MLX_DIR = lib/minilibx-linux/
MLX = mlx
LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -L$(LIBFT_DIR) \
-lft -L$(MATRIX_DIR) -lmatrix
INCS = -I$(HEADER_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
HEADER = $(HEADER_DIR)fdf.h
SRC = main.c parsing.c bresenham.c error.c dynamic_array_utils.c graphics.c \
debug.c scale.c rotation.c init.c point_utils.c hooks.c
PSRC = $(addprefix $(SRC_DIR), $(SRC))
OBJ = $(subst $(SRC_DIR), $(OBJ_DIR), $(PSRC:%.c=%.o))

.PHONY = all clean fclean re lib run

all : $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

re: fclean
	$(MAKE) all

debug:
	$(MAKE) re FLAGS="$(DEBUG_FLAGS)"
	$(MAKE) clean

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)| $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_DIR)libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(MATRIX_DIR)libmatrix.a:
	$(MAKE) -C $(MATRIX_DIR) LIBFT_DIR="../libft"

$(NAME): $(LIBFT_DIR)libft.a $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBS) $(INCS) -o $(NAME)


# === DEBUG === #

run: all
	./fdf maps/pyramide.fdf
