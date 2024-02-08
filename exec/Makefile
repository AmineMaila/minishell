# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/24 17:21:21 by mmaila            #+#    #+#              #
#    Updated: 2023/12/29 14:13:50 by mmaila           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
FLAGS= -Wall -Werror -Wextra

OBJS= main.o

UTILS= exit.o command.o srcs/utils/ft_put_fd.o srcs/utils/ft_split.o \
		srcs/utils/ft_strcmp.o srcs/utils/ft_strjoin.o srcs/utils/ft_strlcpy.o srcs/utils/ft_strncmp.o \
		srcs/utils/ft_putendl_fd.o srcs/get_next_line/get_next_line.o srcs/get_next_line/get_next_line_utils.o

OBJS_BONUS= here_doc_bonus.o main_bonus.o

NAME= pipex
NAME_BONUS= pipex_bonus

all : $(NAME)

bonus : $(NAME_BONUS)

$(NAME) : $(OBJS) $(UTILS)
	$(CC) $(FLAGS) $(OBJS) $(UTILS) -o $(NAME)

$(NAME_BONUS) : $(OBJS_BONUS) $(UTILS)
	$(CC) $(FLAGS) $(OBJS_BONUS) $(UTILS) -o $(NAME_BONUS)

%.o : %.c Includes/pipex.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS) $(OBJS_BONUS) $(UTILS)

fclean : clean
	rm -rf $(NAME) $(NAME_BONUS)

re : fclean all