/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:01:13 by texenber          #+#    #+#             */
/*   Updated: 2026/04/10 09:35:31 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "./minishell.h"

typedef struct s_shell t_shell;

///     execution	///
int		execute_cmds(t_cmd *cmds, t_shell *shell); // **NEW**
int		exec_pipeline(t_cmd *cmds, t_shell *shell); // **NEW**
void	exec_child(t_cmd *cmds, t_shell *shell, int prev_fd, int fd[2]); // **NEW**
char	*resolve_path(char *cmd, char **envp); // CHANGE: add t_shell *shell
int		exec_builtin_parent(t_cmd *cmds, t_shell *shell); // **NEW**
int     exec_builtin(t_cmd *cmds, t_shell *shell); // **NEW**

///		inbuilt flag, infile_fd and outfile_fd set	///
void	set_builtin_and_open(t_cmd *cmds);
void	set_builtin_flag(t_cmd *cmds);
bool	cmd_is_builtin(char *cmd);
void	set_infile_and_outfile(t_cmd *cmds);


///		builtin functions	///

int     builtin_echo(char **argv);
int		builtin_cd(char **argv, t_shell *shell);
int     builtin_pwd(void);
int     builtin_env(char **envp); // CHANGE: add t_shell *shell
int     builtin_export(char **argv, t_shell *shell);
int     builtin_unset(char **argv, t_shell *shell);
int     builtin_exit(char **argv, int last_status);

///		export and unset helpers	///

int     find_env_var(char **env, char *key);
int     update_env_var(char **env, int i, char *var);
char	**add_env_var(char **env, char *var);
void	print_export(char **env);
int		set_env_var(t_shell *shell, char *var);

///		builtin helper functions	///

bool	long_long_overflow(const char *str);

///		exit and free	///
void	free_argv(char **av);
void	free_cmds(t_cmd *cmds);

#endif //EXECUTION_H