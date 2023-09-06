# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 18:37:37 by hbechri           #+#    #+#              #
#    Updated: 2023/09/06 18:44:50 by hbechri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

READLINE = -lreadline -L/Users/hbechri/.brew/opt/readline/lib -I/Users/hbechri/.brew/opt/readline/include

SRCS = minishell.c parse/*.c libft/*.c libft_utilis/*.c execution/builtins/*.c execution/exec_cmd/*.c \
		execution/redirection/*.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)
		
$(NAME) : $(OBJS)
			$(CC) $(CFLAGS) $(READLINE) $(OBJS) -o $(NAME)

clean :
			rm -rf $(OBJS)
			
fclean :	clean
			rm -f $(NAME)

re :	fclean all
