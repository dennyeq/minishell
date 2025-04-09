#include "minishell.h"

static bool is_valid_identifier(char *str)
{
	int i = 0;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return false;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return false;
		i++;
	}
	return true;
}

static void remove_env_var(t_env **envlst, char *key)
{
	t_env *curr = *envlst;
	t_env *prev = NULL;

	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*envlst = curr->next;
			free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

int ft_unset(char **args, t_shdata *sh)
{
	int i = 1;

	if (!args || !args[1])
		return (0);

	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else
		{
			remove_env_var(&sh->envlst, args[i]);
		}
		i++;
	}
	return (0);
}
