/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dud.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:19 by texenber          #+#    #+#             */
/*   Updated: 2026/04/19 16:54:44 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

int	exec_builtin(t_cmd *cmds, t_shell *shell)
{
	if (ft_strcmp(cmds->argv[0], "echo") == 0)
		return (builtin_echo(cmds->argv));
	else if (ft_strcmp(cmds->argv[0], "cd") == 0)
		return (builtin_cd(cmds->argv, shell)); // shell->env doesn't fully work need to further test cd to see if I need to change it back to char **envp. testing once merging is done.
	else if (ft_strcmp(cmds->argv[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmds->argv[0], "env") == 0)
		return (builtin_env(shell->env));
	else if (ft_strcmp(cmds->argv[0], "export") == 0)
		return (builtin_export(cmds->argv, shell));
	else if (ft_strcmp(cmds->argv[0], "unset") == 0)
		return (builtin_unset(cmds->argv, shell));
	else if (ft_strcmp(cmds->argv[0], "exit") == 0)
		return (builtin_exit(cmds->argv, shell->last_status));	
	return (0);
}

int	exec_builtin_parent(t_cmd *cmds, t_shell *shell)
{
	int	res;
	int	fd;
	
	fd = dup(STDOUT_FILENO);
	if (cmds->outfile)
		dup2(cmds->outfile_fd, STDOUT_FILENO);
	res = exec_builtin(cmds, shell);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (cmds->outfile_fd != -1)
		close(cmds->outfile_fd);
	shell->last_status = res;
	return (res);
}
