/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:28:09 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:28:12 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_err(int type)
{
	t_shdata *shdata;

	shdata = get_shdata();
	shdata->parse_err = type;
}

static void	print_error(char *types[], t_token_type token_type)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(types[token_type], 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd("\n", 2);
}

void	solve_parse_err(t_shdata *shdata)
{
	int		type;
	int		token_type;
	char	**types;

	types = (char *[]){"T_ALPANUMERIC",
		"<", ">", "<<", ">>", "|", "(", ")", "&&", "||", "newline"};
	type = shdata->parse_err;
	(void)token_type;
	(void)types;
	if (type)
	{
		if (type > 0)
		{
			if (!shdata->curr_token)
				token_type = T_NL;
			else
				token_type = shdata->curr_token->type;
			print_error(types, (t_token_type)token_type);
			shdata->state_exit = 258;
		}
		shdata->parse_err = 0;
	}
}
