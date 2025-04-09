/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:28:48 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:28:50 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_unquoted_strlen(char *str)
{
	size_t	i;
	size_t	len;
	char	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!quotes)
				quotes = str[i++];
			else if (str[i] == quotes)
				quotes = ((i++) && 0);
			else
				len += (i++ || 1);
		}
		else
			len += (i++ || 1);
	}
	return (len);
}

char	*ft_strjoin_auxi(char const *s1, char const *s2, char *c)
{
	char	*s3;
	char	*s4;

	s3 = ft_strjoin(s1, c);
	s4 = ft_strjoin(s3, s2);
	return (s4);
}

static void	ft_unquote_filler(char *str, size_t *i, char *ret, size_t *j)
{
	char	quotes;

	quotes = str[(*i)++];
	while (str[*i] != quotes)
		ret[(*j)++] = str[(*i)++];
	(*i)++;
}

char	*rmquotes(char *str)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ret = ft_calloc(1 + ft_unquoted_strlen(str), sizeof(char));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			(ft_unquote_filler(str, &i, ret, &j));
		else
			ret[j++] = str[i++];
	}
	return (free(str), ret);
}
