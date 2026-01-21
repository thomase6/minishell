/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:01:00 by texenber          #+#    #+#             */
/*   Updated: 2026/01/21 10:01:01 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//test main for the executor.
int main(int argc, char **argv, char **envp)
{
    t_cmd a;
    t_cmd b;
    t_cmd c;
    t_shell shell; //this will hold our tmp env and last status used.
    char *cmd1[] = {"ls",NULL};
    char *cmd2[] = {"wsc","-l", NULL};
    char *cmd3[] = {"pwd", NULL};
    int status;

    a.argv = cmd1;
    a.infile = -1;
    a.outfile = -1;
    a.is_builtin = 0;
    a.next = &b;
    // a.next = NULL;

    b.argv = cmd2;
    b.infile = -1;
    b.outfile = -1;
    b.is_builtin = 0;
    // b.next = &c;
    b.next = NULL;

    c.argv = cmd3;
    c.infile = -1;
    c.outfile = -1;
    c.is_builtin = 1;
    c.next = NULL;

    if (init_env(&shell, envp) == -1)
    {
        ft_putstr_fd("Error: failed to initialize\n", 2);
	    return (1);
    }
    execute_cmds(&a, &shell); // **NEW**
    free_argv(shell.env);
    return (shell.last_status);
    // printf("exit status: %d\n", shell.last_status);
}


