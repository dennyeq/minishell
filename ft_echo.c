#include "minishell.h"

int	ft_echo(char **args)
{
	int	i = 1;
	int	newline = 1;

	// Verifica se tem "-n", pode ser repetido
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		int j = 2;
		while (args[i][j] == 'n') // suporta "-nnnn"
			j++;
		if (args[i][j] != '\0')
			break;
		newline = 0;
		i++;
	}

	// Imprime os argumentos
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}

	// Adiciona newline, se for o caso
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
