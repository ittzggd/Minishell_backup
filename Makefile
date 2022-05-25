# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hejang <hejang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 18:44:44 by hejang            #+#    #+#              #
#    Updated: 2022/05/25 19:00:48 by hejang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror

LINKING_FLAGS = -lreadline -L/Users/hejang/.brew/opt/readline/lib
COMFILE_FLAGS = -I/Users/hejang/.brew/opt/readline/include