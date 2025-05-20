/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:12:36 by marianamest       #+#    #+#             */
/*   Updated: 2025/05/20 15:36:50 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_builtin(char *command)
{
    // Check if the command is a built-in command
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
        //printf("full_path: %s\n", full_path);
        full_path = ft_strjoin(full_path, cmd->name);
        //printf("full_path2: %s\n", full_path);
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

void handle_pipes_and_redirections(t_simple_command *cmd)
{   
    
    if (cmd->input_fd != STDIN_FILENO)
    {   
       
        dup2(cmd->input_fd, STDIN_FILENO);
        close(cmd->input_fd);
    }
    if (cmd->output_fd != STDOUT_FILENO)
    {   
        
        dup2(cmd->output_fd, STDOUT_FILENO);
        close(cmd->output_fd);
    } 
}

int start_executing(t_command_table *cmd_table)
{
    t_command_table *current_cmd = cmd_table;
    int status;
    while (current_cmd)
    {
        handle_pipes_and_redirections(current_cmd->simplecommand);
        status = execute_command(current_cmd->simplecommand, msh()->env);
        if (status == -1)
            return (-1);
        current_cmd = current_cmd->next;
    }
    
    return (0);
}
