/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:12:36 by marianamest       #+#    #+#             */
/*   Updated: 2025/05/21 14:15:07 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_builtin(char *command)
{
    if (strcmp(command, "cd") == 0 || strcmp(command, "echo") == 0 ||
        strcmp(command, "exit") == 0 || strcmp(command, "export") == 0 ||
        strcmp(command, "unset") == 0 || strcmp(command, "env") == 0)
        return (1);
    return (0);
}

int find_path(t_simple_command *cmd)
{
    char *path_env = getenv("PATH");
    char **paths;
    char *full_path;
    int i;

    if (!path_env)
        return (-1);
    paths = ft_split(path_env, ':');
    for (i = 0; paths[i]; i++)
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, cmd->array_args[0]);
        if (access(full_path, X_OK) == 0)
        {
            cmd->path = full_path;
            free_matrix(paths);
            return (0);
        }
        free(full_path);
    }
    free_matrix(paths);
    return (-1);
}

int execute_command(t_simple_command *cmd, char **env)
{
    int     status;

    printf("Cmd %d: fd in -> %d fd out -> %d\n", msh()->exec->index, cmd->input_fd, cmd->output_fd);
    msh()->exec->pid[msh()->exec->index] = fork();
    if (msh()->exec->pid[msh()->exec->index] < 0)
    {
        ft_putstr_fd("minishell", STDERR_FILENO);
        return (-1);
    }
    if (msh()->exec->pid[msh()->exec->index++] == 0)
    {
        if (cmd->input_fd > 0)
            dup2(cmd->input_fd, STDIN_FILENO);
        else if (msh()->exec->in_pipe_fd[0] > -1)
            close(msh()->exec->in_pipe_fd[0]);
        if (cmd->output_fd > 1)
            dup2(cmd->output_fd, STDOUT_FILENO);
        else if (msh()->exec->out_pipe_fd[1] > -1)
            close(msh()->exec->out_pipe_fd[1]);
        if (msh()->exec->in_pipe_fd[1] > -1)
            close(msh()->exec->in_pipe_fd[1]);
        if (msh()->exec->out_pipe_fd[0] > -1)
            close(msh()->exec->out_pipe_fd[0]);
        find_path(cmd);
        printf("Path -> %s\n", cmd->path);
        if (execve(cmd->path, cmd->array_args, env) == -1)
        {
            ft_putstr_fd("minishell", STDERR_FILENO);
            exit(EXIT_FAILURE);
        }
    }
    return (WEXITSTATUS(status));
}

int start_executing(t_exec *exec, t_command_table *cmd_table)
{
    t_command_table *current_cmd;
    int             status;

    current_cmd = cmd_table;
    while (current_cmd)
    {
        if (current_cmd->next)
        {
            if (pipe(exec->out_pipe_fd) < 0)
            {
                perror("pipe failed");
                return (-1);
            }
            if (current_cmd->simplecommand->output_fd == 1)
                current_cmd->simplecommand->output_fd = exec->out_pipe_fd[1];
        }
        if (current_cmd->simplecommand->input_fd == 0 && exec->in_pipe_fd[0] != -1)
                current_cmd->simplecommand->input_fd = exec->in_pipe_fd[0];
        status = execute_command(current_cmd->simplecommand, msh()->env);
        if (status == -1)
        {
            if (exec->out_pipe_fd[0] != -1)
                close(exec->out_pipe_fd[0]);
            if (exec->out_pipe_fd[1] != -1)
                close(exec->out_pipe_fd[1]);
            if (exec->in_pipe_fd[0] != -1)
                close(exec->out_pipe_fd[0]);
            if (exec->in_pipe_fd[1] != -1)
                close(exec->out_pipe_fd[1]);
            return (-1);
        }
        if (exec->in_pipe_fd[0] != -1)
            close(exec->in_pipe_fd[0]);
        if (exec->in_pipe_fd[1] != -1)
            close(exec->in_pipe_fd[1]);
        exec->in_pipe_fd[0] = exec->out_pipe_fd[0];
        exec->out_pipe_fd[0] = -1;
        exec->in_pipe_fd[1] = exec->out_pipe_fd[1];
        exec->out_pipe_fd[1] = -1;
        current_cmd = current_cmd->next;
    }
    exec->index = -1;
    while (++exec->index < exec->nbr_cmds)
    {
        printf("Waiting for cmd %d\n", exec->index);
        waitpid(exec->pid[exec->index], &status, 0);
    }
    printf("Finished Waiting\n");
    return (0);
}
