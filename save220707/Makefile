# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 14:13:39 by yukim             #+#    #+#              #
#    Updated: 2022/07/04 19:22:02 by hejang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# 폴더에 필요없는 파일들 삭제, 주석 삭제, 헤더파일 주석 확인

# CC 플래그 확인!!!!!!!!! 
CC = gcc -g3
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror 
COMFILE_FLAGS = -lreadline -L/opt/homebrew/opt/readline/lib
OBJ_FLAGS = -I/opt/homebrew/opt/readline/include
# COMFILE_FALGS = -lreadline -L${HOME}/.brew/opt/readline/lib
# OBJ_FLAGS = -I${HOME}/.brew/opt/readline/include

AST_SRCS = ast/delete_astnode.c  ast/free_data_ast.c ast/init_ast.c \
			ast/postorder_travel_ast.c ast/postorder_travel_command.c \
			ast/tree_args.c ast/tree_cmd.c ast/tree_reds.c ast/tree_utils.c

BLT_SRCS = builtins/blt_cd.c builtins/blt_echo.c builtins/blt_env.c \
			builtins/blt_exit.c builtins/blt_export.c builtins/blt_nanoshell.c \
			builtins/blt_pwd.c builtins/blt_unset.c builtins/blt_utils.c

UTILS_SRCS = utils/delete_linked_list.c utils/exec_utils.c \
			utils/ft_bzero.c utils/ft_calloc.c utils/ft_error.c \
			utils/ft_lstadd_back.c utils/ft_lstnew.c utils/ft_memset.c \
			utils/ft_minishell_atoi.c utils/ft_minishell_split.c utils/ft_split_str_util.c \
			utils/ft_split.c utils/ft_strchr.c utils/ft_strdup.c utils/ft_strjoin.c \
			utils/ft_strlcat.c utils/ft_strlcpy.c utils/ft_strlen.c utils/ft_strncmp.c utils/ft_strnstr.c \
			utils/ft_wordcount.c utils/heredoc_utils.c utils/is_utils_01.c utils/is_utils_02.c \
			utils/quote_utils.c utils/remove_ll_element.c utils/replace_env_to_value.c utils/syntax_utils.c

MAIN_SRCS = main.c \
			init.c signal.c reset.c\
			redirections.c heredoc.c \
			token.c lexer.c syntax.c exec.c\
			data.c env.c path.c
			
MAIN_OBJS = $(MAIN_SRCS:.c=.o)
AST_OBJS = $(AST_SRCS:.c=.o)
BLT_OBJS = $(BLT_SRCS:.c=.o)
UTILS_OBJS = $(UTILS_SRCS:.c=.o)

OBJS = $(MAIN_OBJS) $(AST_OBJS) $(BLT_OBJS) $(UTILS_OBJS)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(COMFILE_FLAGS) $(OBJS) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS) 

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
