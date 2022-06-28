NAME = nanoshell
CC = gcc
AR = ar
ARFLAGS = crs
COMFILE_FLAGS = -lreadline -L/opt/homebrew/opt/readline/lib
OBJ_FLAGS = -I/opt/homebrew/opt/readline/include
SRCS =  $(wildcard ${HOME}/P/42/cursus/minishell/220626/220625change_minishell_norm/*.c) \
		$(wildcard ${HOME}/P/42/cursus/minishell/220626/220625change_minishell_norm/*/*.c)
#MAIN_SRCS =  $(addprefix src/, main.c) src/install/execve.c src/install/fork.c
#PARSE_SRCS = $(addprefix src/parse/, ft_cmd_list.c ft_list.c ft_env_list.c ft_parser.c ft_string_list.c ft_check_type.c ft_env_parser.c)
#LIBFT_SRCS = $(addprefix src/libft/, ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_cmpstr.c ft_split.c ft_strlcpy.c)

#MAIN_OBJS = $(MAIN_SRCS:.c=.o)
#PARSE_OBJS = $(PARSE_SRCS:.c=.o)
#LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(COMFILE_FLAGS) $(OBJS) -o $(NAME) 

#%.o: %.c
#	$(CC) $(OBJ_FLAGS) -c $< -o $@

#$(NAME) : $(OBJS)

#		$(AR) $(ARFLAGS) $(COMFILE_FALGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(OBJ_FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS) 

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
