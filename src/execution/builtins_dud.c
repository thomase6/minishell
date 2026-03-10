/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dud.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:19 by texenber          #+#    #+#             */
/*   Updated: 2026/03/10 16:26:43 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_builtin(t_cmd *cmds, t_shell *shell) // **NEW**
{
	// I think strcmp would be better but the example of "echo123" does not pass strncmp which means that it's working correctly so idk
	if (ft_strncmp(cmds->argv[0], "echo", 4) == 0)
		return(builtin_echo(cmds->argv));
	else if (ft_strncmp(cmds->argv[0], "cd", 2) == 0)
		return(builtin_cd(cmds->argv, shell->env)); // shell->env doesn't fully work need to further test cd to see if I need to change it back to char **envp
	else if (ft_strncmp(cmds->argv[0], "pwd", 3) == 0)
		return(builtin_pwd());
	else if (ft_strncmp(cmds->argv[0], "env", 3) == 0)
		return(builtin_env(shell->env));
	else if (ft_strncmp(cmds->argv[0], "export", 6) == 0)
		return(builtin_export(cmds->argv, shell));
	else if (ft_strncmp(cmds->argv[0], "unset", 5) == 0)
		return(builtin_unset(cmds->argv, shell));
	else if (ft_strncmp(cmds->argv[0], "exit", 4) == 0)
		return(builtin_exit(cmds->argv, shell->last_status));	
	return (0);
}

int	exec_builtin_parent(t_cmd *cmds, t_shell *shell) // **NEW**
{
	int res;
	res = exec_builtin(cmds, shell);
	shell->last_status = res;
	return (res);
}
//part of exec_builtin
	// (void)cmds;
	// (void)envp;
	// return (0);


//builtins that should be handled by exec_builtin
	// echo with -n flag
	// cd with relative or absolute path
	// pwd
	// export
	// unset
	// env
	// exit

	