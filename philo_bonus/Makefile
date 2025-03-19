CC = cc 
CCFLAGS = -Wall -Wextra -Werror

SRCS = main.c  philo.c  thread_monitor.c  thread_philo.c  threads.c  time.c

OBJS = $(SRCS:%.c=%.o) 

NAME = philo

all : $(NAME)

$(NAME) : $(OBJS) philo.h
	$(CC) $(CCFLAGS) $(OBJS) -o $@

%.o : %.c 
	$(CC) $(CCFLAGS) $< -c  -o $@ 
clean : 
	rm -rf $(OBJS) 

fclean : clean 
	rm -rf $(NAME) $(B_NAME)

re : fclean all

.PHONY : clean re fclean all 
.SECONDARY: $(OBJS)
