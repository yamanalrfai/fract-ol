CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L. -lmlx -lXext -lX11 -lm
SRC = main.c functions.c
OBJ = $(SRC:.c=.o)
TARGET = fractol

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_FLAGS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re