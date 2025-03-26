NAME = fdf
CC = cc
FLAGS = -Werror -Wextra -Wall -g
DEBUG_FLAGS = -g -fsanitize=address

OBJ_DIR = .obj/
SRC_DIR = src/
HEADER_DIR = inc/
LIBFT_DIR = libft/
MLX_DIR = minilibx-linux/
MLX = mlx
LIBS := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft
INCS = -I$(HEADER_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
HEADER = $(HEADER_DIR)fdf.h
SRC = main.c parsing.c bresenham.c error.c dynamic_array_utils.c
PSRC = $(addprefix $(SRC_DIR), $(SRC))
OBJ = $(subst $(SRC_DIR), $(OBJ_DIR), $(PSRC:%.c=%.o))

.PHONY = all clean fclean re lib

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

lib:
	$(MAKE) -C $(LIBFT_DIR)

debug:
	$(MAKE) re FLAGS="$(DEBUG_FLAGS)"
	$(MAKE) clean

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_DIR)libft.a:
	$(MAKE) lib

$(NAME): $(LIBFT_DIR)libft.a $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBS) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(HEADER_DIR) -o $(NAME)
