CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -lX11 -lXext -lm

NAME = cub3D

SRCS = src/main.c src/utils.c src/check.c src/set_data.c src/ft_move.c src/free.c src/minimap.c src/cub3D.c

all: $(NAME)

$(NAME):
	@make all -C $(LIBFT_DIR)
	@make all -C $(MLX_DIR)
	@$(CC) -fPIE $(CFLAGS) $(SRCS) $(MLX) $(MLXFLAGS) $(LIBFT) -o $(NAME)
	@echo "Let's play !!"

clean:
	make clean -C $(LIBFT_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	@rm -f $(NAME)

re: fclean all

fast: re
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	clear

.PHONY: all clean fclean re fast
