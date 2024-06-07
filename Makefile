CC = cc
CFLAGS = -Wall -Wextra -Werror -g -D X_PIXEL=
B_CFLAGS = -Wall -Wextra -Werror -g -D BONUS=1 -D X_PIXEL=

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -lX11 -lXext -lm

NAME = cub3D

SRCS = src/main.c src/utils.c src/check.c src/set_data.c src/ft_move.c src/render_img.c src/range_lst_utils.c src/free.c src/minimap.c src/cub3D.c src/raycast.c
OBJS = $(SRCS:.c=.o)
B_OBJS = src/main.o src/utils.o src/check.o src/set_data.o src/ft_move.o src/render_img.o src/range_lst_utils.o src/free.o src/minimap.o src/cub3D.o src/raycast.o
X = 1600

all: $(NAME)

$(NAME): $(OBJS)
	@make all -C $(LIBFT_DIR)
	@make all -C $(MLX_DIR)
	@$(CC) -fPIE $(OBJS) $(MLX) $(MLXFLAGS) $(LIBFT) -o $(NAME)
	@echo "Let's play !!"

%.o: %.c
	@$(CC) $(CFLAGS)$(X) -c $< -o $@

$(B_OBJS): %.o: %.c
	@$(CC) $(B_CFLAGS)$(X) -c $< -o $@

bonus: $(B_OBJS)
	@make all -C $(LIBFT_DIR)
	@make all -C $(MLX_DIR)
	@$(CC) -fPIE $(B_OBJS) $(MLX) $(MLXFLAGS) $(LIBFT) -o $(NAME)
	@echo "Let's play !!"

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	@rm -f $(NAME)

re: fclean all

fast: fclean bonus
	rm -f $(OBJS)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	clear

.PHONY: all clean fclean re fast
