#include "minishell.h"

char    *getkey(char *line)
{
    size_t  i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '=')
            return (ft_substr(line, 0, i));
        i++;
    }
    return (ft_strdup(line));
}

char    *getvalue(char *line)
{
    size_t i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '=')
        {
            i++;
            return (ft_substr(line, i, ft_strlen(line) - i));
        }
        i++;
    }
    return (NULL);
}

void    structure_env(void)
{
    int         i;
    char    *key;
    char    *value;
    if (!get_shdata()->env)
        return ;
    i = 0;
    while (get_shdata()->env[i])
    {
        key = getkey(get_shdata()->env[i]);
        value = getvalue(get_shdata()->env[i]);
        update_env(key, value, true);
        i++;
    }
}

int			env_command(void)
{
	t_env	*envs;

	envs = get_shdata()->envlst;
	while (envs)
	{
		if (envs->value != NULL)
			ft_printf("%s=%s\n", envs->key, envs->value);
        envs = envs->next;
	}
	return (0);
}