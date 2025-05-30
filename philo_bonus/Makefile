CC = cc CCFLAGS = -Wall - Wextra - Werror - g - fsanitize = thread

						SRCS = args.c main.c philo.c process.c process_philo.c thread.c time.c OBJS = $(SRCS
																										:
																											%.c =
																											%.o)

							NAME = philo_bonus

										all : $(NAME)

												$(NAME)
	: $(OBJS) philo.h $(CC) $(CCFLAGS) $(OBJS) -
		o $ @

			%.o : %.c $(CC) $(CCFLAGS) $ <
	-c - o $ @clean : rm -
						rf $(OBJS)

							fclean : clean rm -
									rf $(NAME) $(B_NAME)

										re : fclean all

												.PHONY : clean re fclean all.SECONDARY : $(OBJS)
