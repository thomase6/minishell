#include "../../inc/execution.h"

//this function just determines whether we are execute a builtin or an external command.
int execute_cmds(t_cmd *cmds, char **envp, int *last_status) // CHANGE: add t_shell *shell
{
	if (!cmds)
		return (0);
	if (!cmds->next && cmds->is_builtin)
		return (exec_builtin_parent(cmds, envp, last_status)); // CHANGE: add t_shell *shell
	return (exec_pipeline(cmds, envp, last_status)); // CHANGE: add t_shell *shell
}