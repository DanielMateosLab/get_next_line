CC = cc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=10

NAME = gnl
BONUS_NAME = gnl_bonus

SRCS = $(filter-out %_bonus.c, $(wildcard *.c))
OBJS = $(SRCS:.c=.o)

BONUS_SRCS = $(wildcard *_bonus.c)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -g3 -fsanitize=address $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) -g3 $(BONUS_SRCS) main.c -o gnl_bonus

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) gnl_bonus

re: fclean all
