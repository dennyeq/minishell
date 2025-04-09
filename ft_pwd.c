#include "minishell.h"

int	ft_pwd(void)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}
