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