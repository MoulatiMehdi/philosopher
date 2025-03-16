
CC = cc 

CCFLAGS = -Wall -Wextra #-g -fsanitize=address

NAME = philo 
SRCS = $(wildcard *.c) 
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) 
	$(CC) $(CCFLAGS) $^ -o $@ -lc -pthread

%.o : %.c 
	$(CC) $(CCFLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJS)

fclean : clean 
	rm -rf $(NAME)

re : fclean all
