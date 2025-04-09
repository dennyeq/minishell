#include "minishell.h"
bool	is_env(char *key)
{
	t_env	*envlst;

	envlst = get_shdata()->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (true);
		envlst = envlst->next;
	}
	return (false);
}

static	t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

char	*get_env_val(char *key)
{
	t_env	*envlst;

	envlst = get_shdata()->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

void	append_env(t_env *new)
{
	t_env	*curr;

	if (!get_shdata()->envlst || ft_strcmp(new->key, get_shdata()->envlst->key) < 0)
	{
		new->next = get_shdata()->envlst;
		get_shdata()->envlst = new;
		return ;
	}
	curr = get_shdata()->envlst;
	while (curr && curr->next && ft_strcmp(new->key, curr->next->key) > 0)
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
}

void	update_env(char *key, char *value, bool add)
{
	t_env	*envlst;

	envlst = get_shdata()->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
		{
			if (value)
				envlst->value = ft_strdup(value);
			return ;
		}
		envlst = envlst->next;
	}
	if (add)
		append_env(new_env(key, value));
}
