/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:27:29 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:27:31 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_shdata	*init_shdata()
{
	t_shdata	*shdata;
	extern char	**environ;
	shdata = (t_shdata *)ft_calloc(1, sizeof(t_shdata));
	if (!shdata)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	ft_memset(shdata, 0, sizeof(t_shdata));
	shdata->env = environ;
	shdata->state_exit = 0;
	return (shdata);
}

t_shdata *get_shdata(void)
{
	static t_shdata *gvar;
	if (!gvar)
		gvar = init_shdata();
	return (gvar);
}

void print_indent(int depth)
{
	for (int i = 0; i < depth; i++)
		printf("    ");
}

void print_io_list(t_io_list *io_list, int depth)
{
	while (io_list)
	{
		print_indent(depth);
		printf("IO Type: %d, Value: %s\n", io_list->type, io_list->value);
		io_list = io_list->next;
	}
}

void print_node(t_node *node, int depth)
{
	if (!node)
		return;

	print_indent(depth);
	if (node->type == N_PIPE)
		printf("Branch Type: N_PIPE\n");
	else if (node->type == N_CMD)
		printf("Branch Type: N_CMD\n");
	else
		printf("Branch Type: %d\n", node->type);

	if (node->args)
	{
		print_indent(depth);
		printf("Args: %s\n", node->args);
	}

	if (node->io_list)
	{
		print_indent(depth);
		printf("IO List:\n");
		print_io_list(node->io_list, depth + 1);
	}

	if (node->left)
	{
		print_indent(depth);
		print_node(node->left, depth + 1);
	}

	if (node->right)
	{
		print_indent(depth);
		print_node(node->right, depth + 1);
	}
}

bool	tokenize_parsing()
{
	t_shdata *shdata;

	shdata = get_shdata();
	shdata->tokens = tokenizing();
	if (!shdata->tokens)
		return (false);
	shdata->tree = parsing();
	if (shdata->parse_err)
	{
		solve_parse_err(shdata);
		return (false);
	}
	return (true);
}

void	run_minishell()
{
	t_shdata *shdata;

	shdata = get_shdata();
	structure_env();
	solve_signal();
	while (1)
	{
		shdata->line = readline("reborners> ");
		if (!shdata->line)
		{
			ft_putstr_fd("exit\n", 1);
			exit(shdata->state_exit);
		}
		if (shdata->line[0])
			add_history(shdata->line);
		if (!tokenize_parsing())
			continue ;
		struct_args(shdata->tree);
		run_tree(shdata->tree);
		//print_node(shdata->tree, 0);
	}
}

int	main(int argc, char **argv)
{
	t_shdata	*shdata;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("bash : too many arguments", 2);
		return (1);
	}
	shdata = get_shdata();
	run_minishell();
	ft_free_collector();
	return (shdata->state_exit);
}
