/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:30:00 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:30:03 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_newline(int sig)
{
    (void)sig;
    ft_printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    process_sinal(int sig)
{
    (void)sig;
    ft_printf("\n");
}

void    solve_signal(void)
{
    if (get_shdata()->is_child)
        signal(SIGINT, process_sinal);
    else
        signal(SIGINT, signal_newline);
    signal(SIGQUIT, SIG_IGN);
}