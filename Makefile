# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 13:42:04 by mmaila            #+#    #+#              #
#    Updated: 2024/02/10 13:18:44 by nazouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 		minishell

CC				= 		cc

CFLAGS			= 		-Wall -Werror -Wextra -g3

LIBFT			=		./libft/libft.a

INCLUDE			=		./minishell.h

SRCS			= 		\
						./parsing/tokenize.c \
						./parsing/tokenize_quotes.c \
						./parsing/tokenize_utils.c \
						./parsing/command.c \
						./parsing/command_table.c \
						./parsing/command_table_utils.c \
						./parsing/exit.c \
						./parsing/parse.c \
						./parsing/expand.c \
						./helpers.c \
						./utils/ft_lstadd_back.c \
						./utils/ft_lstnew.c \
						./utils/ft_lstclear.c \
						./utils/ft_lstdelone.c \
						./utils/ft_strcmp.c \
						./exec/execute.c \
						./exec/here_doc.c \
						./exec/get_next_line/get_next_line.c \
						./exec/get_next_line/get_next_line_utils.c \
						./env/env.c \
						main.c

OBJS			= 		$(SRCS:.c=.o)

all : $(NAME)

%.o : %.c Includes/minishell.h libft/libft.h
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
