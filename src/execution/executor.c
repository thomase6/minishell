/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:30 by texenber          #+#    #+#             */
/*   Updated: 2026/03/16 16:06:13 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//this function just determines whether we are execute a builtin or an external command.
//builtins are working with the flag being set to true and false. should only work with the flag being set to true.
int		execute_cmds(t_cmd *cmds, t_shell *shell) // ** NEW **
{
	if (!cmds)
		return (0);
	if (!cmds->next && cmds->is_builtin == 1) // it's not necessary to check for the next command because it should be ok to have a command after the built-in function
		return (exec_builtin_parent(cmds, shell)); // ** NEW **
	return (exec_pipeline(cmds, shell)); // ** NEW **
}