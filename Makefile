CC = cc

SRCS = main_bonus.c get_next_line.c get_next_line_utils.c \
		adjust_window_bonus.c dda_bonus.c free_bonus.c get_data_bonus.c \
		image_bonus.c isometric_bonus.c outils_bonus.c outils2_bonus.c \
		extra_key_bonus.c key_bonus.c

SRCS_OBJ = ${SRCS:.c=.o}

NAME = fdf

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Imlx

MLX_FLAGS =  -lmlx -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)


%.o: %.c fdf_bonus.h get_next_line.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(NAME): $(SRCS_OBJ)
	@$(CC) $(SRCS_OBJ) $(MLX_FLAGS) -o $(NAME)
	@echo "\033[1;32mProgram executed (./fdf)\033[0m"

clean :
		@rm -rf ${SRCS_OBJ} 
		@echo "\033[1;30mobject files deleted\033[0m"

fclean : clean
		@rm -rf ${NAME}
		@echo "\033[1;30m+ excutions deleted\033[0m"

re : fclean all