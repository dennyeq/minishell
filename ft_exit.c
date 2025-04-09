#include "minishell.h"

static bool is_numeric(char *str)
{
	int i = 0;

	if (!str)
		return false;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}

void	ft_exit(char **args)
{
	int status = 0;

	ft_putendl_fd("exit", 1);

	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(255);
		}
		else if (args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			get_shdata()->state_exit = 1; // não sai
			return ;
		}
		else
			status = ft_atoi(args[1]);
	}
	exit((unsigned char)status); // cast garante que fique entre 0–255
}
