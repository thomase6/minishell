/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 18:07:09 by texenber          #+#    #+#             */
/*   Updated: 2026/04/26 18:26:56 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void	child_exit(t_cmd *cmds, t_shell *shell, int code)
{
	if (cmds)
		free_cmds(cmds);
	if (shell)
		cleanup_shell(shell);
	exit (code);
}

void	exec_builtin_child(t_cmd *cmds, t_shell	*shell)
{
	int	ret;

	ret = exec_builtin(cmds, shell, NULL);
	child_exit(cmds, shell, ret);
}

void	empty_cmd(t_cmd *cmds, t_shell *shell)
{
	if (!cmds->argv || !cmds->argv[0] || cmds->argv[0][0] == '\0')
		child_exit(cmds, shell, 0);
}
