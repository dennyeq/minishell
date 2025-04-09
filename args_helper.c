/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:27:03 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:27:06 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	validchar(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*solve_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*solve_dquote_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
	{
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

char	*solve_squotes(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*solve_dquotes(char *str, size_t *i)
{
	char	*result;

	result = ft_strdup("\"");
	(*i)++;
	while (str[*i] != '"')
	{
		result = ft_strjoin_f(result, solve_dquote_str(str, i));
	}
	(*i)++;
	return (ft_strjoin_f(result, ft_strdup("\"")));
}
