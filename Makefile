
CC = cc 

CCFLAGS = -Wall -Wextra -Werror -g -fsanitize=address


NAME = philosopher 
SRCS = $(wildcard *.c) 
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) 
	$(CC) $(CCFLAGS) $^ -o $@ -lc

%.o : %.c 
	$(CC) $(CCFLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJS)

fclean : clean 
	rm -rf $(NAME)

re : fclean all
