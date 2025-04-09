/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:29:15 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:29:21 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_f(char *s1, char *s2)
{
	char	*joined;
	size_t	total_length;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	total_length = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = ft_calloc(total_length, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = 0;
	return (joined);
}

static char	*expand_vars(char *str)
{
	char	*ret;
	size_t	i;

	ret = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = ft_strjoin_f(ret, solve_squotes(str, &i));
		else if (str[i] == '"')
			ret = ft_strjoin_f(ret, solve_dquotes(str, &i));
		else
			ret = ft_strjoin_f(ret, solve_str(str, &i));
	}
	return (ret);
}

char	**solve_args(char *s)
{
	char	**expanded;
	size_t	i;

	s = expand_vars(s);
	if (!s || !*s)
	{
		return (NULL);
	}
	
	if (!s)
		return (NULL);
	expanded = split_args(s);
	if (!expanded)
		return (NULL);
	i = 0;
	while (expanded[i])
	{
		expanded[i] = rmquotes(expanded[i]);
		i++;
	}
	return (expanded);
}
