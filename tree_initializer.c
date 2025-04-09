/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_initializer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:31:51 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:31:53 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	struct_args(t_node *node)
{
	if (!node)
		return ;
	if (node->type == N_PIPE)
	{
		struct_args(node->left);
		struct_args(node->right);
	}
	else if (node->args)
	{
		node->structed_args = solve_args(node->args);
	}
	if (node->io_list && (node->io_list->type == IO_HEREDOC))
		node->fd_heredoc = setup_heredoc(node->io_list->value);
}
