/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equaresm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:25:08 by equaresm          #+#    #+#             */
/*   Updated: 2025/03/24 15:25:15 by equaresm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int is_numeric(char *arg)
{
    while (*arg)
        if (!ft_isdigit(*(arg++)))
            return (false);
    return (true);    
}

void    ft_exit(char **args)
{
    int status;

    if (args)
    {
        status = 0;
        ft_printf("exit\n");
        if (args[1] != NULL && !is_numeric(args[1]))
        {
            ft_printf("reborners: exit: %s: numeric argument required\n", args[1]);
            status = 2;
            (rl_clear_history(), ft_free_collector(), exit(get_shdata()->state_exit));
        }
        else if (args[1] != NULL && args[2] != NULL)
        {
            ft_printf("reborners: exit: too many arguments\n");
        }
        else
        {
            if (args[1] != NULL)
                status = ft_atoi(args[1]);
            (rl_clear_history(), ft_free_collector(), exit(status));
        }
    }
}