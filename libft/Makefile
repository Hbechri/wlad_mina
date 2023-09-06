# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 16:22:56 by amakhrou          #+#    #+#              #
#    Updated: 2022/11/07 18:14:12 by amakhrou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_toupper.c ft_tolower.c ft_isprint.c ft_isascii.c ft_atoi.c ft_strlen.c ft_memcpy.c ft_memset.c ft_bzero.c ft_strchr.c \
ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strlcpy.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strnstr.c ft_memmove.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_strlcat.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
		
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
			ar -rc $(NAME) $(OBJS)
clean :
			rm -rf $(OBJS)
fclean :	clean
			rm -f $(NAME)				
re :	fclean all