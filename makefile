CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
SRC = main.c fract.c alloc.c fun_for_mlx.c helper.c
OBJ = $(SRC:.c=.o)
TARGET = fractol

all: $(MLX_LIB) $(TARGET)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(TARGET): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re