SRCDIR	= ./srcs/
SRCNAME	=	main.c\
			arg_parse.c\
			print_mutex.c\
			status.c\
			share.c\
			fork.c\
			philo.c\
			ft_malloc.c\
			mini_libft1.c\
			debug.c

SRCS	= $(addprefix $(SRCDIR), $(SRCNAME))
OBJS	= $(SRCS:.c=.o)

NAME	= philo
LDFLAGS = -pthread
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all		:	$(NAME)

.c.o	:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

sani	:	$(OBJS)
		$(CC) $(CFLAGS) -fsanitize=address $(OBJS) $(LDFLAGS) -o $(NAME)

clean	:
			$(RM) $(OBJS) $(OBJSBONUS)

fclean	:
			$(RM) $(NAME) $(OBJS) $(OBJSBONUS)

re		: fclean all

.PHONY	: all clean fclean re
