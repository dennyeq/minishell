/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:31:40 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:31:42 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenizing(void)
{
	t_token	*tokens;
	t_shdata *shdata;

	shdata = get_shdata();

	tokens = tokenizer();
	shdata->line = NULL;
	return (tokens);
}

int	appendseparator(t_token_type type, char **line_ptr,
	t_token **token_list)
{
	t_token	*token;

	token = newtoken(NULL, type);
	if (!token)
		return (0);
	appendtoken(token_list, token);
	(*line_ptr)++;
	if (type == T_DLESS || type == T_DGREAT)
		(*line_ptr)++;
	return (1);
}

int	appendidentifier(
		char **line_ptr, t_token **token_list)
{
	char	*tmp_line;
	char	*value;
	t_token	*token;
	size_t	i;

	tmp_line = *line_ptr;
	i = 0;
	while (tmp_line[i] && !is_separator(tmp_line + i))
	{
		if (is_quote(tmp_line[i]))
		{
			if (!skip_quotes(tmp_line, &i))
				return (pquote_err(tmp_line[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = newtoken(value, T_ALPANUMERIC);
	if (!token)
		return (0);
	*line_ptr += i;
	return (appendtoken(token_list, token), 1);
}

int	solve_separator(char **line_ptr, t_token **token_list)
{
	if (!ft_strncmp(*line_ptr, "<<", 2))
		return (appendseparator(T_DLESS, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">>", 2))
		return (appendseparator(T_DGREAT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "<", 1))
		return (appendseparator(T_LESS, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">", 1))
		return (appendseparator(T_GREAT, line_ptr, token_list) && 1);
	else
		return (appendseparator(T_PIPE, line_ptr, token_list) && 1);
}

t_token	*tokenizer()
{
	char	*line;
	int		error;
	t_token	*token_list;
	t_shdata *shdata;

	shdata = get_shdata();
	error = 0;
	token_list = NULL;
	line = shdata->line;
	while (*line)
	{
		if (error)
			return (NULL);
		if (ft_isspace(*line))
			skip_spaces(&line);
		else if (is_separator(line))
		{
			error = (!solve_separator(&line, &token_list) && 1);
		}
		else
			error = (!appendidentifier(
						&line, &token_list) && 1);
	}
	return (token_list);
}
