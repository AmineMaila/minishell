# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 13:42:04 by mmaila            #+#    #+#              #
#    Updated: 2024/01/29 16:33:10 by nazouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc

FLAGS= -Wall -Werror -Wextra

SRCS= main.c

OBJS= $(SRCS:.c=.o)

NAME= minishell

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
