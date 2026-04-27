/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:19 by texenber          #+#    #+#             */
/*   Updated: 2026/04/26 18:03:20 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	exec_builtin(t_cmd *cmds, t_shell *shell, int *fd)
{
	if (ft_strcmp(cmds->argv[0], "echo") == 0)
		return (builtin_echo(cmds->argv));
	else if (ft_strcmp(cmds->argv[0], "cd") == 0)
		return (builtin_cd(cmds->argv, shell));
	else if (ft_strcmp(cmds->argv[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmds->argv[0], "env") == 0)
		return (builtin_env(cmds->argv, shell->env));
	else if (ft_strcmp(cmds->argv[0], "export") == 0)
		return (builtin_export(cmds->argv, shell));
	else if (ft_strcmp(cmds->argv[0], "unset") == 0)
		return (builtin_unset(cmds->argv, shell));
	else if (ft_strcmp(cmds->argv[0], "exit") == 0)
		return (builtin_exit(cmds, shell, fd));
	return (0);
}

int	exec_builtin_parent(t_cmd *cmds, t_shell *shell)
{
	int	res;
	int	fd[2];

	res = 0;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (all_redirections(cmds) == 1)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		return (1);
	}
	res = exec_builtin(cmds, shell, fd);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	shell->last_status = res;
	return (res);
}
