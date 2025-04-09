#include "minishell.h"

static void	update_pwd(char *oldpwd)
{
	char	newpwd[PATH_MAX];

	if (getcwd(newpwd, sizeof(newpwd)) == NULL)
		return ;

	update_env("OLDPWD", oldpwd, true);
	update_env("PWD", newpwd, true);
}

int	ft_cd(char **args)
{
	char	*target;
	char	oldpwd[PATH_MAX];

	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		oldpwd[0] = '\0';

	if (!args[1]) // cd sem argumentos → vai para $HOME
	{
		target = get_env_val("HOME");
		if (!target)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = get_env_val("OLDPWD");
		if (!target)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (1);
		}
		ft_putendl_fd(target, 1); // igual ao Bash: imprime o novo path
	}
	else
		target = args[1];

	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}

	update_pwd(oldpwd);
	return (0);
}
