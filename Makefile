CC = cc

SRCS = main.c get_next_line.c get_next_line_utils.c

SRCS_OBJ = ${SRCS:.c=.o}

NAME = fdf

UNAME = ${shell uname}

CFLAGS = -Wall -Wextra -Werror

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
	MLX_LIB = ./mlx/libmlx_$(UNAME).a
else
	INCLUDES = -Imlx
endif

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
else
	MLX_FLAGS =  -lmlx -framework OpenGL -framework AppKit
endif

all: $(NAME)

%.o: %.c fdf.h get_next_line.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(NAME): $(SRCS_OBJ)
	$(CC) $(CFLAGS)  $(SRCS_OBJ) $(MLX_FLAGS) -o $(NAME) -fsanitize=address -g
 
$(MLX_LIB):
	@make -C /usr/library/
 
clean :
		rm -rf *.o

fclean : clean
		rm -rf Fdf