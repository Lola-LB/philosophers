SRCS		= philo.c				\
			  thread.c				\
			  util.c				\
			  lib.c					\
			  free.c				\
			  init.c				\

SRCS_BONUS	= philo_bonus.c			\
			  process_bonus.c		\
			  util_bonus.c			\
			  lib_bonus.c			\
			  init_bonus.c			\

OBJS		= $(addprefix srcs/, $(SRCS:.c=.o))

OBJS_BONUS	= $(addprefix srcs_bonus/, $(SRCS_BONUS:.c=.o))

INC			= -I include/

DEP			= $(OBJS:.o=.d)			\
			  $(OBJS_BONUS:.o=.d)

CC			= cc -pthread -g3 -MMD

AR			= ar rcs

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

NAME		= philo

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

all:		$(NAME)

bonus:		$(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)_bonus

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) $(DEP)

fclean:		clean
	$(RM) $(NAME) $(NAME)_bonus

re:		fclean all

.PHONY:		all bonus clean fclean re

-include : $(DEP)
