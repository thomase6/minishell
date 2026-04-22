/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:01:13 by texenber          #+#    #+#             */
/*   Updated: 2026/04/22 13:01:52 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "./minishell.h"

typedef struct s_shell t_shell;

///     execution	///
int		execute_cmds(t_cmd *cmds, t_shell *shell);
int		exec_pipeline(t_cmd *cmds, t_shell *shell);
void	exec_child(t_cmd *cmds, t_shell *shell, int prev_fd, int fd[2]);
char	*resolve_path(char *cmd, char **envp);
int		exec_builtin_parent(t_cmd *cmds, t_shell *shell);
int     exec_builtin(t_cmd *cmds, t_shell *shell);

///		inbuilt flag, infile_fd and outfile_fd set	///
void	set_builtin_and_open(t_cmd *cmds);
void	set_builtin_flag(t_cmd *cmds);
bool	cmd_is_builtin(char *cmd);
void	set_infile_and_outfile(t_cmd *cmds);
void	setup_heredoc(t_cmd	*cmd);

///		builtin functions	///

int     builtin_echo(char **argv);
int		builtin_cd(char **argv, t_shell *shell);
int     builtin_pwd(void);
int     builtin_env(char **argv, char **envp);
int     builtin_export(char **argv, t_shell *shell);
int     builtin_unset(char **argv, t_shell *shell);
int     builtin_exit(char **argv, int last_status);

///		builtin helper functions	///

bool	long_long_overflow(const char *str);
void	update_underscore(t_shell *shell, char *path);
int     find_env_var(char **env, char *key);
int     update_env_var(char **env, int i, char *var);
char	**add_env_var(char **env, char *var);
void	print_export(char **env);
int		set_env_var(t_shell *shell, char *var);
void	no_such_argument(char *arg);
void	update_shlvl(t_shell *shell);

///		redirections				///
t_exec_redir *new_redir(int type, char *filename);
void add_redirs(t_cmd *cmds, t_exec_redir *node);
int	all_redirections(t_cmd *cmds);
int	apply_redirections(t_exec_redir *r);
int	apply_in(t_exec_redir *r);
int	apply_out(t_exec_redir *r);
int	apply_append(t_exec_redir *r);
int	apply_heredoc(t_cmd *cmds);

///		pipeline helper functions	///

void	cmd_not_found(char *cmd);
void	file_no_access(char *cmd);

///		Execution Cleanup	///
void	free_argv(char **av);
void	free_cmds(t_cmd *cmds);
void	free_redirs(t_exec_redir *redir);

#endif //EXECUTION_H