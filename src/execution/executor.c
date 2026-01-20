#include "../../inc/minishell.h"

//this function just determines whether we are execute a builtin or an external command.
int		execute_cmds(t_cmd *cmds, t_shell *shell) // ** NEW **
{
	if (!cmds)
		return (0);
	if (!cmds->next && cmds->is_builtin)
		return (exec_builtin_parent(cmds, shell)); // ** NEW **
	return (exec_pipeline(cmds, shell)); // ** NEW **
}