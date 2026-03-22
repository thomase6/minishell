/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:01:00 by texenber          #+#    #+#             */
/*   Updated: 2026/03/22 10:21:42 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/minishell.h"

// // test main for the executor.
// int main(int argc, char **argv, char **envp)
// {
//     t_cmd a;
//     t_cmd b;
//     t_cmd c;
//     t_shell shell; //this will hold our tmp env and last status used.
//     char *cmd1[] = {"export",NULL};
//     char *cmd2[] = {"wsc","-l", NULL};
//     char *cmd3[] = {"pwd", NULL};
//     int status;

//     a.argv = cmd1;
//     a.infile = -1;
//     a.outfile = -1;
//     a.is_builtin = 1;
//     // a.next = &b;
//     a.next = NULL;

//     b.argv = cmd2;
//     b.infile = -1;
//     b.outfile = -1;
//     b.is_builtin = 0;
//     // b.next = &c;
//     b.next = NULL;

//     c.argv = cmd3;
//     c.infile = -1;
//     c.outfile = -1;
//     c.is_builtin = 1;
//     c.next = NULL;

//     if (init_env(&shell, envp) == -1)
//     {
//         ft_putstr_fd("Error: failed to initialize\n", 2);
// 	    return (1);
//     }
//     execute_cmds(&a, &shell); // **NEW**
//     free_argv(shell.env);
//     return (shell.last_status);
//     // printf("exit status: %d\n", shell.last_status);
// }


//testing the export helper functions
// int main(int argc, char **argv, char **envp)
// {
//     t_shell shell;
//     if (init_env(&shell, envp) == -1)
//     {
//         ft_putstr_fd("Error: failed to initialize\n", 2);
// 	    return (1);
//     }
//     test();
// }


// testing export //

// int main(int argc, char **argv, char **envp)
// {
//     t_cmd cmd;
//     t_shell shell;
    
//     // Initialize shell
//     if (init_env(&shell, envp) == -1)
//     {
//         ft_putstr_fd("Error: failed to initialize\n", 2);
//         return (1);
//     }
    
//     printf("=== Test 1: Add new variable ===\n");
//     char *test1[] = {"export", "MYVAR=hello", NULL};
//     cmd.argv = test1;
//     cmd.infile = -1;
//     cmd.outfile = -1;
//     cmd.is_builtin = 1;
//     cmd.next = NULL;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 2: Check it was added (print export) ===\n");
//     char *test2[] = {"export", NULL};
//     cmd.argv = test2;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 3: Update existing variable ===\n");
//     char *test3[] = {"export", "MYVAR=world", NULL};
//     cmd.argv = test3;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 4: Check it was updated ===\n");
//     cmd.argv = test2;  // export with no args
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 5: Add multiple variables ===\n");
//     char *test5[] = {"export", "VAR1=a", "VAR2=b", "VAR3=c", NULL};
//     cmd.argv = test5;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 6: Verify with env command ===\n");
//     char *test6[] = {"env", NULL};
//     cmd.argv = test6;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 7: Invalid identifiers ===\n");
//     char *test7[] = {"export", "123=bad", NULL};
//     cmd.argv = test7;
//     execute_cmds(&cmd, &shell);
    
//     char *test8[] = {"export", "MY-VAR=bad", NULL};
//     cmd.argv = test8;
//     execute_cmds(&cmd, &shell);
    
//     char *test9[] = {"export", "NOEQUALS", NULL};
//     cmd.argv = test9;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 8: Update PATH ===\n");
//     char *test10[] = {"export", "PATH=/new/path", NULL};
//     cmd.argv = test10;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 9: Verify PATH was updated ===\n");
//     cmd.argv = test2;  // export with no args
//     execute_cmds(&cmd, &shell);
    
//     // Cleanup
//     free_argv(shell.env);
//     return (0);
// }

//testing unset

// int main(int argc, char **argv, char **envp)
// {
//     t_cmd cmd;
//     t_shell shell;
    
//     if (init_env(&shell, envp) == -1)
//         return (1);
    
//     printf("=== Test 1: Add some variables ===\n");
//     char *test1[] = {"export", "VAR1=a", "VAR2=b", "VAR3=c", NULL};
//     cmd.argv = test1;
//     cmd.infile = -1;
//     cmd.outfile = -1;
//     cmd.is_builtin = 1;
//     cmd.next = NULL;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 2: Show all variables ===\n");
//     char *test2[] = {"export", NULL};
//     cmd.argv = test2;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 3: Remove VAR1 ===\n");
//     char *test3[] = {"unset", "VAR1", NULL};
//     cmd.argv = test3;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 4: Verify VAR1 is gone ===\n");
//     cmd.argv = test2;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 5: Remove multiple ===\n");
//     char *test5[] = {"unset", "VAR2", "VAR3", NULL};
//     cmd.argv = test5;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 6: Verify they're gone ===\n");
//     cmd.argv = test2;
//     execute_cmds(&cmd, &shell);
    
//     printf("\n=== Test 7: Unset non-existent (should not error) ===\n");
//     char *test7[] = {"unset", "DOESNOTEXIST", NULL};
//     cmd.argv = test7;
//     execute_cmds(&cmd, &shell);
//     printf("Status: %d (should be 0)\n", shell.last_status);
    
//     free_argv(shell.env);
//     return (0);
// }