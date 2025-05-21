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
        full_path = ft_strjoin(full_path, cmd->name);
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
    pid_t pid;
    int status;
    find_path(cmd);
    pid = fork();
    if (pid == 0)
    {
        if (execve(cmd->path, cmd->array_args, env) == -1)
        {
            ft_put_str_fd("minishell", 2);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        ft_put_str_fd("minishell", 2);
        return (-1);
    }
    else
        waitpid(pid, &status, 0); // Wait for the child process to finish (‼️ nao posso usar waitpid ‼️)
     if (cmd->output_fd != STDOUT_FILENO)
     {
         close(cmd->output_fd);
         cmd->output_fd = STDOUT_FILENO;
     }
    return (WEXITSTATUS(status));
}

void handle_pipes_and_redirections(t_exec *exec)
{
    if (!exec)
    {
        ft_put_str_fd("Error: exec is NULL in handle_pipes_and_redirections\n", 2);
        return;
    }
    if (exec->in_fd != STDIN_FILENO)
    {
        dup2(exec->in_fd, STDIN_FILENO);
        close(exec->in_fd);
    }
    if (exec->out_fd != STDOUT_FILENO)
    {
        dup2(exec->out_fd, STDOUT_FILENO);
        close(exec->out_fd);
    }
    if (exec->pipe_fd[1] != -1)
    {
        dup2(exec->pipe_fd[1], STDOUT_FILENO);
        close(exec->pipe_fd[1]);
    }
    if (exec->pipe_fd[0] != -1)
    {
        dup2(exec->pipe_fd[0], STDIN_FILENO);
        close(exec->pipe_fd[0]);
    }
}int start_executing(t_exec *exec, t_command_table *cmd_table)
{
    if (!exec)
    {
        fprintf(stderr, "Error: exec is NULL in start_executing\n");
        return (-1);
    }
    t_command_table *current_cmd = cmd_table;
    int status;

    while (current_cmd)
    {
        if (!current_cmd || !current_cmd->simplecommand)
        {
            fprintf(stderr, "Error: Null pointer in command table\n");
            return (-1);
        }

        if (current_cmd->next)
        {
            if (pipe(exec->pipe_fd) < 0)
            {
                perror("pipe failed");
                return (-1);
            }
            current_cmd->simplecommand->output_fd = exec->pipe_fd[1];
            current_cmd->next->simplecommand->input_fd = exec->pipe_fd[0];
        }

        handle_pipes_and_redirections(exec);

        status = execute_command(current_cmd->simplecommand, msh()->env);
        if (status == -1)
        {
            if (exec->pipe_fd[0] != -1) close(exec->pipe_fd[0]);
            if (exec->pipe_fd[1] != -1) close(exec->pipe_fd[1]);
            return (-1);
        }

        if (exec->pipe_fd[0] != -1) close(exec->pipe_fd[0]);
        if (exec->pipe_fd[1] != -1) close(exec->pipe_fd[1]);

        current_cmd = current_cmd->next;
    }

    return (0);
}