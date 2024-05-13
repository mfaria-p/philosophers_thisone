# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfaria-p <mfaria-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 19:27:32 by mfaria-p          #+#    #+#              #
#    Updated: 2024/05/13 14:46:23 by mfaria-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
       srcs/utils.c \
       srcs/init_all.c \
       srcs/monitor_routine.c \
       srcs/philo_routine.c \
       srcs/threads.c \
       srcs/time.c \

OBJS = $(SRCS:.c=.o)

NAME = philosophers
CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=thread

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(FLAGS)  $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all