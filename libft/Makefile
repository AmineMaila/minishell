# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 20:13:46 by nazouz            #+#    #+#              #
#    Updated: 2023/11/03 20:13:46 by nazouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			=	libft.a

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

INCLUDES		=	libft.h

AR				=	ar crs

RM				=	rm -f

SRCS_PART1		=	\
					./ft_isalnum.c \
					./ft_isalpha.c \
					./ft_isascii.c \
					./ft_isdigit.c \
					./ft_isprint.c \
					./ft_tolower.c \
					./ft_toupper.c \
					./ft_atoi.c \
					./ft_calloc.c \
					./ft_strchr.c \
					./ft_strdup.c \
					./ft_strlcat.c \
					./ft_strlcpy.c \
					./ft_strlen.c \
					./ft_strncmp.c \
					./ft_strnstr.c \
					./ft_strrchr.c \
					./ft_bzero.c \
					./ft_memchr.c \
					./ft_memcmp.c \
					./ft_memcpy.c \
					./ft_memmove.c \
					./ft_memset.c

SRCS_PART2		=	\
					./ft_itoa.c \
					./ft_split.c \
					./ft_strjoin.c \
					./ft_strtrim.c \
					./ft_substr.c \
					./ft_putchar_fd.c \
					./ft_putstr_fd.c \
					./ft_putendl_fd.c \
					./ft_putnbr_fd.c \
					./ft_strmapi.c \
					./ft_striteri.c

SRCS_BONUS		=	\
					./ft_lstnew_bonus.c \
					./ft_lstadd_front_bonus.c \
					./ft_lstsize_bonus.c \
					./ft_lstlast_bonus.c \
					./ft_lstadd_back_bonus.c \
					./ft_lstdelone_bonus.c \
					./ft_lstclear_bonus.c \
					./ft_lstiter_bonus.c \
					./ft_lstmap_bonus.c

SRCS			=	\
					$(SRCS_PART1) \
					$(SRCS_PART2)

OBJS			=	$(SRCS:.c=.o)

OBJS_BONUS		=	$(SRCS_BONUS:.c=.o)

all : $(NAME)

%.o : %.c $(INCLUDES)
	@ $(CC) -c $(CFLAGS) $< -o $@

bonus : $(OBJS_BONUS) $(OBJS)
	@ $(AR) $(NAME) $(OBJS_BONUS) $(OBJS)

$(NAME) : $(OBJS)
	@ $(AR) $(NAME) $(OBJS)

clean :
	@ $(RM) $(OBJS) $(OBJS_BONUS)

fclean : clean
	@ $(RM) $(NAME)

re : fclean all
