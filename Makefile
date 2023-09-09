# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 18:37:37 by hbechri           #+#    #+#              #
#    Updated: 2023/09/08 23:03:38 by hbechri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

RLIB = -lreadline -L /Users/$(USER)/goinfre/homebrew/opt/readline/lib

RINCLUDES = -I /Users/$(USER)/goinfre/homebrew/opt/readline/include

SRCS = libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_toupper.c libft/ft_tolower.c libft/ft_isprint.c libft/ft_isascii.c libft/ft_atoi.c libft/ft_strlen.c libft/ft_memcpy.c libft/ft_memset.c libft/ft_bzero.c libft/ft_strchr.c \
libft/ft_strrchr.c libft/ft_strncmp.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_strlcpy.c libft/ft_calloc.c libft/ft_strdup.c libft/ft_substr.c libft/ft_strjoin.c libft/ft_strnstr.c libft/ft_memmove.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c \
libft/ft_strlcat.c libft/ft_strmapi.c libft/ft_striteri.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft_utilis/delete_node.c \
libft_utilis/free_list.c libft_utilis/ft_lstadd_back.c libft_utilis/ft_lstnew.c libft_utilis/ft_lstsize.c libft_utilis/ft_strcmp.c libft_utilis/ft_strcpy.c execution/builtins/echo_bt.c execution/builtins/cd_bt.c execution/builtins/env_bt.c execution/builtins/exit_bt.c \
execution/builtins/export_bt.c execution/builtins/pwd_bt.c execution/builtins/unset_bt.c execution/builtins/utilis_bt.c execution/exec_cmd/exec_cmd.c execution/redirections/heredoc.c execution/redirections/redirections.c execution/redirections/redirect_input.c execution/redirections/redirect_output.c \
execution/redirections/redirect_output_append.c parse/env.c parse/expand.c parse/lexer.c parse/parse_cmd.c parse/redirection.c parse/syntax_error.c parse/token.c parse/utilis.c parse/utilis1.c minishell.c parse/utilis2.c execution/execution.c \


OBJS = $(SRCS:.c=.o)

all : $(NAME)
		
$(NAME) : $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(RLIB) $(RINCLUDES) -o $(NAME)

clean :
			rm -rf $(OBJS)
			
fclean :	clean
			rm -f $(NAME)

re :	fclean all
