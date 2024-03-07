CC = cc

SRCS = main.c

SRCS_OBJ = ${SRCS:.c=.o}

NAME = Fdf

CFLAGS = -Wall -Wextra -Werror

all : ${NAME}

$(NAME): $(SRCS_OBJ)
	$(CC) $(SRCS_OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

clean :
		rm -rf *.o

fclean : clean
		rm -rf Fdf