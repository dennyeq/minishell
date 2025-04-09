/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:31:31 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:31:33 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	is_separator(char *s)
{
	if (*s == ' ' || *s == '\t'
		|| *s == '<' || *s == '>' || *s == '|' || *s == '&')
		return (1);
	return (0);
}

void	skip_spaces(char **line)
{
	while (**line && ft_isspace(**line))
		(*line)++;
}

bool	skip_quotes(char *line, size_t *i)
{
	char	quote;

	quote = line[*i];
	if (ft_strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}

void	pquote_err(char c)
{
	t_shdata *shdata;

	shdata = get_shdata();
	ft_putstr_fd("minishell: unexpected EOF while looking for matching ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	shdata->state_exit = 258;
}
