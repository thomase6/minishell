/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dud.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:19 by texenber          #+#    #+#             */
/*   Updated: 2026/04/06 11:02:54 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

int	exec_builtin(t_cmd *cmds, t_shell *shell)
{
	if (ft_strcmp(cmds->argv[0], "echo") == 0)
		return (builtin_echo(cmds->argv));
	else if (ft_strcmp(cmds->argv[0], "cd") == 0)
		return (builtin_cd(cmds->argv, shell->env)); // shell->env doesn't fully work need to further test cd to see if I need to change it back to char **envp. testing once merging is done.
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

	res = exec_builtin(cmds, shell);
	shell->last_status = res;
	return (res);
}

//builtins that should be handled by exec_builtin
	// echo with -n flag
	// cd with relative or absolute path
	// pwd
	// export
	// unset
	// env
	// exit