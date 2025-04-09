#include "minishell.h"

static bool is_valid_key(const char *str)
{
	int i = 0;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return false;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return false;
		i++;
	}
	return true;
}

static void print_export_list(t_env *envlst)
{
	t_env *env = envlst;

	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

static char *get_key_part(char *str)
{
	int len = 0;
	while (str[len] && str[len] != '=')
		len++;
	return ft_substr(str, 0, len);
}

static char *get_value_part(char *str)
{
	char *eq = ft_strchr(str, '=');
	if (eq)
		return ft_strdup(eq + 1);
	return NULL;
}

int ft_export(char **args, t_shdata *sh)
{
	int i = 1;

	if (!args[1])
	{
		print_export_list(sh->envlst);
		return 0;
	}

	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else
		{
			char *key = get_key_part(args[i]);
			char *value = get_value_part(args[i]);
			update_env(key, value, true); // já cuida de substituir se existir
			free(key);
			if (value)
				free(value);
		}
		i++;
	}
	return 0;
}
