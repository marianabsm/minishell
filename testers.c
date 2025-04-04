#include "includes/minishell.h"

void print_redirs(t_redirs_list *redirs)
{
    t_redirs_list * tmp;

    tmp = redirs;
    while (tmp)
    {
        printf("Redir type: %d\n", tmp->redir_type);
        printf("Redir file: %s\n", tmp->file ? tmp->file : "(NULL)");
        printf("Redir delimiter: %s\n", tmp->delimiter ? tmp->delimiter : "(NULL)");
        tmp = tmp->next;
    }
}

void print_simple_command(t_simple_command *simple_command)
{
    int i;

    if (!simple_command)
        return;
    printf("Simple command:\n");
    for (i = 0; i < simple_command->n_of_arg; i++)
    {
        printf("  Arg %d: %s\n", i + 1, simple_command->array_args[i]);
    }
}

void print_command_table(t_command_table *command_table)
{
    int command_index = 1;

    while (command_table)
    {
        printf("Command table:\n");
        printf("- Simple command %d:\n", command_index);
        for (int i = 0; i < command_table->simplecommand->n_of_arg; i++)
            printf("  - %s\n", command_table->simplecommand->array_args[i]);

        printf("- Redirs %d:\n", command_index);
        t_redirs_list *redir = command_table->redirs;
        while (redir)
        {
            if (redir->redir_type == R_OUT)
                printf("  - >%s\n", redir->file);
            else if (redir->redir_type == R_APP)
                printf("  - >>%s\n", redir->file);
            else if (redir->redir_type == R_IN)
                printf("  - <%s\n", redir->file);
            else if (redir->redir_type == HERE_DOC)
                printf("  - <<%s\n", redir->delimiter);
            redir = redir->next;
        }

        command_table = command_table->next;
        command_index++;
    }
}

void free_command_table(t_command_table *command_table)
{
    t_command_table *tmp;

    while (command_table)
    {
        tmp = command_table;
        free_redirs_list(command_table->redirs);
        free(command_table->simplecommand);
        command_table = command_table->next;
        free(tmp);
    }
}