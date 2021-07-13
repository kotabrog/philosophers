SRCDIR	= ./srcs/
SRCNAME	=	main.c

SRCS	= $(addprefix $(SRCDIR), $(SRCNAME))
OBJS	= $(SRCS:.c=.o)

NAME	= philo
LDFLAGS = -lpthread
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
