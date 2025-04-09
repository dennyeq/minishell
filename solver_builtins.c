#include "minishell.h"
bool isbuiltin(char *arg)
{
    return (arg && (!ft_strcmp(arg, "env")
        || !ft_strcmp(arg, "cd")
        || !ft_strcmp(arg, "exit")
        || !ft_strcmp(arg, "unset")
        || !ft_strcmp(arg, "pwd")
        || !ft_strcmp(arg, "echo")
        || !ft_strcmp(arg, "export"))); // Corrigido aqui
}

int run_builtin(char **args, t_shdata *sh)
{
	if (!ft_strcmp(args[0], "env"))
		return (env_command(), 0);
	if (!ft_strcmp(args[0], "export"))
		return (ft_export(args, sh), 0);
	if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, sh), 0);
    if (!ft_strcmp(args[0], "echo"))
        return (ft_echo(args), 0);
    if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd());    
    if (!ft_strcmp(args[0], "exit"))
		ft_exit(args);
    return (1);
}


