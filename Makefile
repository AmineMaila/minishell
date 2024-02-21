# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 13:42:04 by mmaila            #+#    #+#              #
#    Updated: 2024/02/21 15:39:37 by nazouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 		minishell

CC				= 		cc

CFLAGS			= 		-Wall -Werror -Wextra

AR				=		ar crs

LIBFT			=		./libft/libft.a

READLINEDIR		=		$(shell brew --prefix readline)

INCLUDE			=		./Includes/minishell.h ./libft/libft.h

SRCS_LIBFT		=		\
						./libft/ft_isalnum.c \
						./libft/ft_isalpha.c \
						./libft/ft_isascii.c \
						./libft/ft_isdigit.c \
						./libft/ft_isprint.c \
						./libft/ft_tolower.c \
						./libft/ft_toupper.c \
						./libft/ft_atoi.c \
						./libft/ft_atoll.c \
						./libft/ft_calloc.c \
						./libft/ft_strchr.c \
						./libft/ft_strdup.c \
						./libft/ft_strlcat.c \
						./libft/ft_strlcpy.c \
						./libft/ft_strlen.c \
						./libft/ft_strncmp.c \
						./libft/ft_strnstr.c \
						./libft/ft_strrchr.c \
						./libft/ft_bzero.c \
						./libft/ft_memchr.c \
						./libft/ft_memcmp.c \
						./libft/ft_memcpy.c \
						./libft/ft_memmove.c \
						./libft/ft_memset.c \
						./libft/ft_itoa.c \
						./libft/ft_split.c \
						./libft/ft_strjoin.c \
						./libft/ft_strtrim.c \
						./libft/ft_substr.c \
						./libft/ft_putchar_fd.c \
						./libft/ft_putstr_fd.c \
						./libft/ft_putendl_fd.c \
						./libft/ft_putnbr_fd.c \
						./libft/ft_strmapi.c \
						./libft/ft_striteri.c

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
OBJS_LIBFT		= 		$(SRCS_LIBFT:.c=.o)

all : $(NAME)

%.o : %.c $(INCLUDE)
	@echo "\033[5;34mCompiling ${notdir $<}\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(READLINEDIR)/include

$(LIBFT) : $(OBJS_LIBFT)
	@$(AR) $(LIBFT) $(OBJS_LIBFT)

$(NAME) : $(LIBFT) $(OBJS) $(INCLUDE)
	@echo "\033[1;33mBuilding Minishell...\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -L$(READLINEDIR)/lib -lreadline
	@echo "\033[1;32mSUCCESS\033[0m"

clean :
	@echo "\033[3;31mCleaning...\033[0m"
	@rm -rf $(OBJS) $(OBJS_LIBFT)

fclean : clean
	@rm -rf $(NAME) $(OBJS)
	@rm -rf $(LIBFT) $(OBJS_LIBFT)

re : fclean all
