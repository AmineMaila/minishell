# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 13:42:04 by mmaila            #+#    #+#              #
#    Updated: 2024/01/30 12:34:14 by nazouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 		minishell

CC				= 		cc

CFLAGS			= 		-Wall -Werror -Wextra

LIBFT			=		./libft/libft.a

INCLUDE			=		./minishell.h

SRCS			= 		\
						./parsing/tokenize.c \
						./helpers.c \
						main.c

OBJS			= 		$(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(shell brew --prefix readline)/include

$(NAME) : $(OBJS)
	@ cd ./libft && make
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -L$(shell brew --prefix readline)/lib -lreadline

clean :
	rm -rf $(OBJS)
	@ cd ./libft && make clean

fclean : clean
	rm -rf $(NAME) $(OBJS)
	@ cd ./libft && make fclean

re : fclean all
