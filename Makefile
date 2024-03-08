CC = cc

SRCS = main.c

SRCS_OBJ = ${SRCS:.c=.o}

NAME = Fdf

CFLAGS = -Wall -Wextra -Werror

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
else
	INCLUDES = -I/opt/X11/include -Imlx
endif
 
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif
 
# [...]
 
all: $(MLX_LIB) $(NAME)
 
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
 
$(NAME): $(SRCS_OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS_OBJ) $(MLX_FLAGS)
 
$(MLX_LIB):
	@make -C $(MLX_DIR)
 
# [...]
clean :
		rm -rf *.o

fclean : clean
		rm -rf Fdf