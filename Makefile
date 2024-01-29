# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 13:42:04 by mmaila            #+#    #+#              #
#    Updated: 2024/01/29 20:44:33 by nazouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= 		cc

CFLAGS			= 		-Wall -Werror -Wextra

INCLUDE			=		./minishell.h

SRCS			= 		\
						main.c

OBJS			= 		$(SRCS:.c=.o)

NAME			= 		minishell

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(shell brew --prefix readline)/include

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(shell brew --prefix readline)/lib -lreadline

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
