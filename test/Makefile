# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 18:44:44 by hejang            #+#    #+#              #
#    Updated: 2022/06/15 15:32:38 by hejang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	./*.c \
		../command.c
		
OBJS = $(SRCS:.c=.o)

CC = gcc -g3
CC_FLAGS = -Wall -Wextra -Werror

LINKING_FLAGS = -lreadline -L .brew/opt/readline/lib
COMFILE_FLAGS = -I .brew/opt/readline/include

minishell : $(SRCS)
	$(CC) $(SRCS) -o minishell $(LINKING_FLAGS) $(COMFILE_FLAGS) $(CFLAGS)
