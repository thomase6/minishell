/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:01:13 by texenber          #+#    #+#             */
/*   Updated: 2026/01/22 09:35:07 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/src/libft.h"

// typedef struct s_exec
// {
// 	char	*path;
// 	pid_t	*pids;
// 	size_t	ch_count;
// 	int		pipe_fd[2];
// 	int		*status;
// 	bool	is_builtin;
// }	t_exec;
typedef struct s_shell t_shell;

typedef struct s_cmd
{
    char            **argv;
    int             infile;
    int             outfile;
    int             is_builtin;
    struct s_cmd    *next;
} t_cmd;

// int single_cmd_execution(char *av, char **envp);
int		execute_cmds(t_cmd *cmds, t_shell *shell); // **NEW**
int		exec_pipeline(t_cmd *cmds, t_shell *shell); // **NEW**
void	exec_child(t_cmd *cmds, t_shell *shell, int prev_fd, int fd[2]); // **NEW**
char	*resolve_path(char *cmd, char **envp); // CHANGE: add t_shell *shell
int	    exec_builtin_parent(t_cmd *cmds, t_shell *shell); // **NEW**
int	exec_builtin(t_cmd *cmds, t_shell *shell); // **NEW**

///		builtin functions	///

int	builtin_echo(char **argv);
int	builtin_cd(char **av, char **envp); // CHANGE: add t_shell *shell
int	builtin_pwd(void);
int	builtin_env(char **envp); // CHANGE: add t_shell *shell
int	builtin_exit(char **argv, int last_status);
int	builtin_export(char **argv, t_shell *shell);

///		export and unset helpers	///

int     find_env_var(char **env, char *key);
int     update_env_var(char **env, int i, char *var);
char    **add_env_var(char **env, char *var);
void	print_export(char **env);
void    test(void); // this is just for testing

///		exit and free	///
void	free_argv(char **av);


#endif //EXECUTION_H