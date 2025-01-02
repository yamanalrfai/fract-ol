CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_PATH  = ./minilibx
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
SRC = main.c functions.c
OBJ = $(SRC:.c=.o)
TARGET = fractol

all: $(TARGET)

$(TARGET): $(OBJ) $(MLX_PATH)/libmlx.a
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_FLAGS)

$(MLX_PATH)/libmlx.a:
	make -C $(MLX_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(TARGET)
	make -C $(MLX_PATH) fclean

re: fclean all

.PHONY: all clean fclean re