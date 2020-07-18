# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sako <sako@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/17 22:26:56 by sako              #+#    #+#              #
#    Updated: 2020/07/18 18:17:50 by sako             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c print.c setup.c thread.c diner.c util.c string.c
OBJS		= $(SRCS:.c=.o)

GCC			= gcc
RM			= rm -f
CFLAGS		= -Wextra -Werror -Wall -I.
LIBS		= -lpthread

NAME		= philo_three

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re