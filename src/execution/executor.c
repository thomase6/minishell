/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:30 by texenber          #+#    #+#             */
/*   Updated: 2026/04/05 09:38:20 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"


//this function just determines whether we are execute a builtin or an external command.
int	execute_cmds(t_cmd *cmds, t_shell *shell) // ** NEW **
{
	if (!cmds)
		return (0);
	// set is_builtin flag and open the infile file descriptor
	if (!cmds->next && cmds->is_builtin == 1) // it's not necessary to check for the next command because it should be ok to have a command after the built-in function
		return (exec_builtin_parent(cmds, shell)); // ** NEW **
	return (exec_pipeline(cmds, shell)); // ** NEW **
}
