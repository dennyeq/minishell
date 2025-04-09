/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:29:03 by cgama             #+#    #+#             */
/*   Updated: 2025/03/24 15:29:06 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool setup_pipe(int fds[2])
{
    if (pipe(fds) == -1)
    {
        ft_putstr_fd("pipe failed", 2);
        get_shdata()->state_exit = 1;
        return (false);
    }
    return (true);
}

static void redirect_fd(int old_fd, int new_fd)
{
    if (dup2(old_fd, new_fd) == -1)
    {
        ft_putstr_fd("dup2 failed", 2);
        exit(1);
    }
    close(old_fd);
}

int  setup_heredoc(const char *del)
{
    int     fds[2];
    char    *line;

    if (pipe(fds) == -1)
    {
        ft_putstr_fd("pipe failed", 2);
        return (-1);
    }
    while (1)
    {
        line = readline("> ");
        if (!line || !ft_strcmp(line, del))
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, fds[1]);
        ft_putstr_fd("\n", fds[1]);
        free(line);
    }
    close(fds[1]);
    return (fds[0]);
}

static void apply_redirs(t_node *node)
{
    int fd;
    t_io_list   *io_list;

    io_list = node->io_list;
    while (io_list)
    {
        if (io_list->type == IO_IN)
        {
            fd = open(io_list->value, O_RDONLY);
            if (fd == -1)
            {
                ft_putstr_fd(io_list->value, 2);
                exit(1);
            }
            redirect_fd(fd, STDIN_FILENO);
        }
        else if (io_list->type == IO_OUT)
        {
            fd = open(io_list->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                ft_putstr_fd(io_list->value, 2);
                exit(1);
            }
            redirect_fd(fd, STDOUT_FILENO);
        }
        else if (io_list->type == IO_APPEND)
        {
            fd = open(io_list->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                ft_putstr_fd(io_list->value, 2);
                exit(1);
            }
            redirect_fd(fd, STDOUT_FILENO);
        }
        else if(io_list->type == IO_HEREDOC)
        {
            fd = node->fd_heredoc;
            if (fd == -1)
                exit(1);
            redirect_fd(fd, STDIN_FILENO);
        }
        io_list = io_list->next;
    }
    
}

static void run_l_pipe(t_node *node, int write_fd)
{
    redirect_fd(write_fd, STDOUT_FILENO);
    get_shdata()->is_child = true;
    solve_signal();
    run_tree(node);
    exit(get_shdata()->state_exit);
}
 
static  void run_r_pipe(t_node *node, int read_fd)
{
    redirect_fd(read_fd, STDIN_FILENO);
    get_shdata()->is_child = true;
    solve_signal();
    run_tree(node);
    exit(get_shdata()->state_exit);
}

static void wait_for_children(pid_t pid1, pid_t pid2)
{
    int status;

    waitpid(pid1, &status, 0);
    if(WIFEXITED(status))
        get_shdata()->state_exit = WEXITSTATUS(status);
    waitpid(pid2, &status, 0);
    if(WIFEXITED(status))
        get_shdata()->state_exit = WEXITSTATUS(status);
    get_shdata()->is_child = false;
    solve_signal();
}

void    run_cmd(t_node *node)
{
    pid_t   pid;
    int     status;
    int     in_tmp;
    int     out_tmp;

    in_tmp = -1;
    out_tmp = -1;
    if (!node || node->type != N_CMD
            || !node->structed_args || !node->structed_args[0])
    {
        get_shdata()->state_exit = 0;
        return ;
    }
    
    if (isbuiltin(node->structed_args[0]))
    {
        if (node->io_list)
        {
            in_tmp = dup(STDIN_FILENO);
            out_tmp = dup(STDOUT_FILENO);
            apply_redirs(node);
        }
        get_shdata()->state_exit = run_builtin(node->structed_args, get_shdata());
        if (in_tmp != -1)
            redirect_fd(in_tmp, STDIN_FILENO);
        if (out_tmp != -1)
            redirect_fd(out_tmp, STDOUT_FILENO);
        return ;
    }
    pid = fork();
    if (pid == -1)
    {
        ft_putstr_fd("fork failed", 2);
        get_shdata()->state_exit = 1;
        return ;
    }
    if (pid == 0)
    {
        get_shdata()->is_child = true;
        solve_signal();
        apply_redirs(node);
        get_shdata()->state_exit = run_others(node->structed_args);
        exit(get_shdata()->state_exit);
    }
    waitpid(pid, &status, 0);
    get_shdata()->is_child = false;
    solve_signal();
    if (WIFEXITED(status))
        get_shdata()->state_exit = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        get_shdata()->state_exit = 128 + WTERMSIG(status);
}

void    run_tree(t_node *node)
{
    int fds[2];
    pid_t pid1;
    pid_t pid2;

    if (!node)
    {
        get_shdata()->state_exit = 1;
        return ;
    }
    if (node->type == N_PIPE)
    {
        if (!setup_pipe(fds))
            return ;
        pid1 = fork();
        if (pid1 == -1)
        {
            ft_putstr_fd("fork failed", 2);
            close(fds[READ]);
            close(fds[WRITE]);
            get_shdata()->state_exit = 1;
            return ;
        }
        if (pid1 == 0)
        {
            close(fds[READ]);
            run_l_pipe(node->left, fds[WRITE]);
        }
        pid2 = fork();
        if (pid2 == -1)
        {
            ft_putstr_fd("fork failed", 2);
            close(fds[READ]);
            close(fds[WRITE]);
            get_shdata()->state_exit = 1;
            return ;
        }
        if (pid2 == 0)
        {
            close(fds[WRITE]);
            run_r_pipe(node->right, fds[READ]);
        }
        close(fds[READ]);
        close(fds[WRITE]);
        wait_for_children(pid1, pid2);
    }
    else if (node->type == N_CMD)
        run_cmd(node);
}
