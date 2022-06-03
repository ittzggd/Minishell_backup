# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 18:44:44 by hejang            #+#    #+#              #
#    Updated: 2022/06/03 15:00:56 by hejang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror

LINKING_FLAGS = -lreadline -L/Users/hejang/.brew/opt/readline/lib
COMFILE_FLAGS = -I/Users/hejang/.brew/opt/readline/include