# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 18:44:44 by hejang            #+#    #+#              #
#    Updated: 2022/06/10 13:28:54 by hejang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	ast.c command.c env.c lexer.c syntax.c tokenize.c tree_utils.c \
		./utils/*.c
		
OBJS = $(SRCS:.c=.o)

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror

LINKING_FLAGS = -lreadline -L/Users/hejang/.brew/opt/readline/lib
COMFILE_FLAGS = -I/Users/hejang/.brew/opt/readline/include

minishell : $(SRCS)
	$(CC) $(CFLAGS) -o $@ $<
