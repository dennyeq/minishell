/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:28:35 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:28:37 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	following_token(void)
{
	t_shdata *shdata;

	shdata = get_shdata();
	shdata->curr_token = shdata->curr_token->next;
}

bool	ctoken_is_pipe()
{
	t_token_type	type;
	t_shdata *shdata;

	shdata = get_shdata();
	if (!shdata->curr_token)
		return (false);
	type = shdata->curr_token->type;
	if (type == T_PIPE)
		return (true);
	return (false);
}

bool	isredir(t_token_type type)
{
	if (type == T_LESS || type == T_GREAT
		|| type == T_DLESS || type == T_DGREAT)
		return (true);
	return (false);
}
