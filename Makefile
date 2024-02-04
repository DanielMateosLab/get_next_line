CC = cc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=8

NAME = test

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -g3 -fsanitize=address $(SRCS) -o test

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
