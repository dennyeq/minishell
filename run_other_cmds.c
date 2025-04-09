#include "minishell.h"

int run_file(char **args)
{
    int                 status;
    pid_t           pid;
    struct stat     sfile;

    if (!stat(args[0], &sfile) && S_ISREG(
            sfile.st_mode) && (sfile.st_mode & S_IXUSR))
    {
        get_shdata()->is_child = true;
        solve_signal();
        pid = fork();
        if(!pid)
            execve(args[0], args, get_shdata()->env);
        else
        {
            waitpid(pid, &status, 0);
            get_shdata()->is_child = false;
            solve_signal();
            return (WEXITSTATUS(status));
        }
    }
    return (1);
}

int onfather()
{
    int status;

    waitpid(-1, &status, 0);
    get_shdata()->is_child = false;
    solve_signal();
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (WEXITSTATUS(status));
}

int run_others(char **args)
{
    char    *line;
    pid_t   pid;
    char    **paths;
    int     status;

    if (!run_file(args))
        return (0);
    line = get_env_val("PATH");
    if (!line)
        return (127);
    paths = ft_split(line, ':');
    get_shdata()->is_child = true;
    solve_signal();
    pid = fork();
    if (pid == -1)
    {
        ft_putstr_fd("fork failed", 1);
        get_shdata()->state_exit = 1;
        return (1);
    }
    if (pid == 0)
    {
        while (*paths)
        {
            if (pid)
                return (onfather());
            line = ft_strjoin_with(*paths, args[0], '/');
            execve(line, args, get_shdata()->env);
            paths++;
        }
        exit(127);
    }
    waitpid(pid, &status, 0);
    get_shdata()->is_child = true;
    solve_signal();
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if(WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (1);
}