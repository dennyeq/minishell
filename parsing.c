/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:27:52 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:27:57 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*get_term()
{
	t_shdata *shdata;

	shdata = get_shdata();
	if (shdata->parse_err)
		return (NULL);
	if (ctoken_is_pipe())
	{
		parse_err(1);
		return (NULL);
	}
	else
		return (get_simple_node());
}

t_node	*join_node(t_token_type type_op,
	t_node *left, t_node *right)
{
	t_node	*node;
	t_shdata *shdata;

	shdata = get_shdata();
	if (shdata->parse_err)
		return (NULL);
	node = new_node(get_t_node(type_op));
	if (!node)
		return (parse_err(1), NULL);
	node->left = left; 
	node->right = right;
	return (node); 
}

t_node	*iterator_seq(t_node *left)
{
	t_token_type	op;
	t_node	*right;
	t_shdata *shdata;

	shdata = get_shdata();
	while (ctoken_is_pipe())
	{
		op = shdata->curr_token->type;
		following_token();
		if (!shdata->curr_token)
			return (parse_err(1), left);
		right = get_sequence();
		if (!right)
			return (left);
		left = join_node(op, left, right);
		if (!left) 
			return (NULL);
	}
	return (left);
}

t_node	*get_sequence(void)
{
	t_node *node;
	t_shdata *shdata;

	shdata = get_shdata();
	if (shdata->parse_err || !shdata->curr_token)
		return (NULL);
	node = get_term();
	if (!node)
		return (NULL);
	node = iterator_seq(node);
	return (node);
}

t_node	*parsing(void)
{
	t_node	*tree;
	t_shdata *shdata;

	shdata = get_shdata();

	shdata->curr_token = shdata->tokens;
	tree = get_sequence();
	if (shdata->curr_token)
		return (parse_err(1), tree);
	return (tree);
}
