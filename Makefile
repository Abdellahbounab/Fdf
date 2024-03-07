CC = cc

SRCS = main.c

SRCS_OBJ = ${SRCS:.c=.o}

NAME = Fdf

CFLAGS = -Wall -Wextra -Werror

all : ${NAME}

${NAME} : ${SRCS_OBJ}
		${CC} ${CFLAGS} ${SRCS_OBJ} -o $@

$(NAME): $(SRCS_OBJ)
	$(CC) $(SRCS_OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


%.o: %.c
	$(CC) ${CFLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean :
		rm -rf *.o

fclean : clean
		rm -rf Fdf