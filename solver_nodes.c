/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:29:42 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:29:44 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_type	get_t_node(t_token_type type)
{
	(void)type;
	return (N_PIPE);
}

t_io_type	get_io_type(t_token_type type)
{
	if (type == T_LESS)
		return (IO_IN);
	if (type == T_GREAT)
		return (IO_OUT);
	if (type == T_DLESS)
		return (IO_HEREDOC);
	return (IO_APPEND);
}

t_node	*new_node(t_node_type type)
{
	t_node	*new_branch;

	new_branch = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_branch)
		return (NULL);
	new_branch->type = type;
	return (new_branch);
}

t_io_list	*new_io_list(t_token_type type, char *value)
{
	t_io_list	*new_io;

	new_io = ft_calloc(1, sizeof(t_io_list));
	if (!new_io)
		return (NULL);
	new_io->type = get_io_type(type);
	new_io->value = ft_strdup(value);
	if (!new_io->value)
		return (NULL);
	return (new_io);
}

void	append_io_list(t_io_list **lst, t_io_list *new)
{
	t_io_list	*curr_branch;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr_branch = *lst;
	while (curr_branch && curr_branch->next)
		curr_branch = curr_branch->next;
	curr_branch->next = new;
}
