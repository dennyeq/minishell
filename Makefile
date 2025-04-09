NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft
SRCS_FILES = solver_nodes.c \
	solver_tokens.c \
	parsing.c \
	parsing_error.c \
	parsing_helper.c \
	token_helper.c \
	parsing_utils.c \
	tokenizer.c \
	solve_args.c \
	args_helper.c \
	spliter_args.c \
	remove_quotes.c \
	tree_initializer.c \
	solver_signals.c \
	ft_exit.c \
	ft_env.c \
	run_commands.c \
	solver_builtins.c \
	run_other_cmds.c \
	env_utils.c \
	ft_export.c \
	ft_unset.c \
	ft_echo.c \
	ft_pwd.c
OBJS_FILES = solver_nodes.o \
	solver_tokens.o \
	parsing.o \
	parsing_error.o \
	parsing_helper.o \
	token_helper.o \
	parsing_utils.o \
	tokenizer.o \
	solve_args.o \
	args_helper.o \
	spliter_args.o \
	remove_quotes.o \
	tree_initializer.o \
	solver_signals.o \
	ft_exit.o \
	ft_env.o \
	run_commands.o \
	solver_builtins.o \
	run_other_cmds.o \
	env_utils.o \
	ft_export.o \
	ft_unset.o \
	ft_echo.o \
	ft_pwd.o 
all: $(NAME)

$(NAME): $(OBJS_FILES)
	make -C $(LIBFT) bonus
	$(CC) $(CFLAGS) $(OBJS_FILES) -o $(NAME) minishell.c $(LIBFT)/libft.a -lreadline


clean:
	rm -f $(OBJS_FILES)
	make -C $(LIBFT) fclean
	
fclean: clean
	rm -f minishell $(LIBFT)/libft.a

re: fclean all
