/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:28:19 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:28:23 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	set_io_list(t_io_list **io_list)
{
	t_token_type	redir_type;
	t_io_list		*tmp_io_list;
	t_shdata *shdata;
	
	shdata = get_shdata();
	if (shdata->parse_err)
		return (false);
	while (shdata->curr_token && isredir(shdata->curr_token->type))
	{
		redir_type = shdata->curr_token->type;
		following_token();
		if (!shdata->curr_token)
			return (parse_err(1), false);
		if (shdata->curr_token->type != T_ALPANUMERIC)
			return (parse_err(1), false);
		tmp_io_list = new_io_list(redir_type, shdata->curr_token->value);
		if (!tmp_io_list)
			return (parse_err(1), false);
		append_io_list(io_list, tmp_io_list);
		following_token();
	}
	return (true);
}

char	*ft_strjoin_with(char const *s1, char const *s2, char c)
{
	char	*joined;
	size_t	total_length;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	if (!c || !ft_strlen(s1) || !ft_strlen(s2))
		return (ft_strjoin(s1, s2));
	total_length = ft_strlen(s1) + ft_strlen(s2) + 1 + 1;
	joined = ft_calloc(total_length, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	joined[i++] = c;
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	return (joined);
}

bool	join_args(char **args)
{
	t_shdata *shdata;

	shdata = get_shdata();
	if (shdata->parse_err)
		return (false);
	if (!*args)
		*args = ft_strdup("");
	if (!*args)
		return (false);
	while (shdata->curr_token
		&& shdata->curr_token->type == T_ALPANUMERIC)
	{
		*args = ft_strjoin_with(*args, shdata->curr_token->value, ' ');
		if (!*args)
			return (false);
		following_token();
	}
	return (true);
}

t_node	*get_simple_node()
{
	t_node	*node;
	t_shdata *shdata;

	shdata = get_shdata();
	if (shdata->parse_err)
		return (NULL);
	node = new_node(N_CMD);
	if (!node)
		return (parse_err(1), NULL);
	while (shdata->curr_token
		&& (shdata->curr_token->type == T_ALPANUMERIC
			|| isredir(shdata->curr_token->type)))
	{
		if (shdata->curr_token->type == T_ALPANUMERIC)
		{
			if (!join_args(&(node->args)))
				return (parse_err(1), NULL);
		}
		else if (isredir(shdata->curr_token->type))
		{
			if (!set_io_list(&(node->io_list)))
				return (NULL);
		}
	}
	return (node);
}
