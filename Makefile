# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 13:42:04 by mmaila            #+#    #+#              #
#    Updated: 2024/02/22 19:15:34 by mmaila           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 		minishell

CC				= 		cc

CFLAGS			= 		-Wall -Werror -Wextra

LIBFT			=		./libft/libft.a

READLINEDIR		=		$(shell brew --prefix readline)

INCLUDE			=		./Includes/minishell.h ./libft/libft.h

SRCS			= 		\
						./parsing/tokenize.c \
						./parsing/tokenize_quotes.c \
						./parsing/tokenize_utils.c \
						./parsing/flag_utils.c \
						./parsing/flag.c \
						./parsing/command_table.c \
						./parsing/command_table_utils.c \
						./parsing/command_table_utils_2.c \
						./parsing/exit.c \
						./parsing/parse.c \
						./parsing/expand_utils.c \
						./parsing/expand.c \
						./parsing/set_fds.c \
						./utils/ft_lstadd_back.c \
						./utils/ft_lstnew.c \
						./utils/ft_lstclear.c \
						./utils/ft_lstdelone.c \
						./utils/ft_strcmp.c \
						./exec/execute.c \
						./exec/here_doc.c \
						./exec/command.c \
						./exec/get_next_line/get_next_line.c \
						./exec/get_next_line/get_next_line_utils.c \
						./builtins/echo.c \
						./builtins/builtin.c \
						./builtins/pwd.c \
						./builtins/unset.c \
						./builtins/env.c \
						./builtins/export.c \
						./builtins/cd.c \
						./builtins/exit.c \
						./env.c \
						./signals.c \
						./main.c

OBJS			= 		$(SRCS:.c=.o)

all : $(NAME)

%.o : %.c $(INCLUDE)
	@echo "\033[5;34mCompiling ${notdir $<}\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(READLINEDIR)/include

$(NAME) : $(LIBFT) $(OBJS) $(INCLUDE)
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME) -L$(READLINEDIR)/lib -lreadline
	@echo "\033[1;32mSUCCESS\033[0m"

$(LIBFT) :
	@echo "\033[1;33mBuilding LIBFT...\033[0m"
	@make -C ./libft
	@echo "\033[1;33mBuilding Minishell...\033[0m"

clean :
	@echo "\033[3;31mCleaning...\033[0m"
	@rm -rf $(OBJS)
	@make clean -C ./libft

fclean : clean
	@rm -rf $(NAME) $(OBJS)
	@rm -rf $(LIBFT)

re : fclean all
