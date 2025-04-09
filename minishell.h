/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:27:38 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:27:41 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include "libft/include/libft.h"
# include <sys/types.h>

# ifndef READ
#  define READ 0
# endif

# ifndef WRITE
#  define WRITE 1
# endif

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_tree_dir
{
	TD_LEFT,
	TD_RIGHT
}	t_tree_dir;
typedef enum e_node_type
{
	N_PIPE,
	N_CMD,
}	t_node_type;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_io_type;

typedef struct s_io_list
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	int					here_doc[2];
	struct s_io_list	*prev;
	struct s_io_list	*next;
}	t_io_list;

typedef enum e_token_type
{
	T_ALPANUMERIC,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_NL,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_node
{
	t_node_type		type;
	t_io_list			*io_list;
	char				*args;
	char				**structed_args;
	struct s_node		*left;
	struct s_node		*right;
	int fd_heredoc;
}	t_node;

typedef struct s_shdata
{
	char		*line;
	char		**env;
	char		*io_error;
	t_token		*tokens;
	t_token		*curr_token;
	t_node	*tree;
	int			state_exit;
	bool		is_child;
	int			parse_err;
	t_env		*envlst;
}	t_shdata;

int  setup_heredoc(const char *del);
int run_others(char **args);
void	update_env(char *key, char *value, bool add);
void	append_env(t_env *new);
char	*get_env_val(char *key);
bool	is_env(char *key);
void	append_env(t_env *new);
void	update_env(char *key, char *value, bool add);
void    structure_env(void);
char    *getvalue(char *line);
char    *getkey(char *line);
void			struct_args(t_node *branch);
int run_builtin(char **args, t_shdata *shell);
bool    		isbuiltin(char *arg);
void    		run_tree(t_node *node);
int			env_command(void);
t_shdata		*get_shdata(void);
void			solve_signal(void);
void			ft_exit(char **args);
void			run_minishell();
t_token			*tokenizing(void);
int				appendseparator(t_token_type type,
					char **line_ptr, t_token **token_list);
int				appendidentifier(char **line_ptr,
					t_token **token_list);
int				solve_separator(char **line_ptr, t_token **token_list);
t_token			*tokenizer(void);
t_token			*newtoken(char *value, t_token_type type);
void			appendtoken(t_token **lst, t_token *new_token);
void			clear_tokens(t_token **lst);
int				is_quote(char c);
int				is_separator(char *s);
void			skip_spaces(char **line);
bool			skip_quotes(char *line, size_t *i);
void			pquote_err(char c);
t_node		*get_term(void);
t_node		*get_sequence(void);
t_node		*join_node(t_token_type type_op, t_node *left,
					t_node *right);
t_node		*parsing(void);
void			following_token(void);
bool			ctoken_is_pipe(void);
t_node_type	get_t_node(t_token_type type);
t_io_type		get_io_type(t_token_type type);
t_node		*new_node(t_node_type type);
t_io_list		*new_io_list(t_token_type type, char *value);
void			append_io_list(t_io_list **lst, t_io_list *new);
bool			set_io_list(t_io_list **io_list);
bool			join_args(char **args);
t_node		*get_simple_node(void);
void			ft_free_char2(char **tofree);
void			ft_free_char3(char ***tofree);
void			parse_err(int type);
void			solve_parse_err(t_shdata *shdata);
bool			isredir(t_token_type type);
char			*ft_strjoin_with(char const *s1, char const *s2, char c);
const char		*token_type_to_string(t_token_type type);
void			print_readline(void);
const char		*oken_type_to_string(t_token_type type);
void			print_node(t_node *node, int depth);
void			print_io_list(t_io_list *io_list, int depth);
void			print_t_node(t_node *node);
void			ft_recursive_print_ast(t_node *node);
void			print_token(t_token *token);
char			*ft_strjoin_f(char *s1, char *s2);
char			**solve_args(char *s);
bool			validchar(char c);
char			*solve_str(char *str, size_t *i);
char			*solve_squotes(char *str, size_t *i);
char			*solve_dquotes(char *str, size_t *i);
char			**split_args(char const *s);
char			*rmquotes(char *str);
//built-in
int     ft_export(char **args, t_shdata *shell);
//void    update_env_var(char ***env, char *var);
//char  **sort_env(char **env);
int		ft_unset(char **args, t_shdata *sh);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_cd(char **args);

#endif
