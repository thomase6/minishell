/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:30 by texenber          #+#    #+#             */
/*   Updated: 2026/04/22 15:43:42 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

bool	cmd_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

// is_builtin = 0 so all we have to do is check and change if it
// is a builtin otherwise let it be.
void	set_builtin_flag(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (current->argv && current->argv[0])
		{
			if (cmd_is_builtin(current->argv[0]) == 1)
				current->is_builtin = 1;
		}
		current = current->next;
	}
}

// this function just determines whether we are execute a builtin or
// an external command.
int	execute_cmds(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return (0);
	set_builtin_flag(cmds);
	if (!cmds->next && cmds->is_builtin == 1)
		return (exec_builtin_parent(cmds, shell));
	return (exec_pipeline(cmds, shell));
}
