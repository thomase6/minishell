/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dud.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:19 by texenber          #+#    #+#             */
/*   Updated: 2026/01/21 10:00:20 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_builtin(t_cmd *cmds, t_shell *shell) // **NEW**
{
	// gotta change all of this to strcmp not strncmp because currently "echo123" passes.
	if (ft_strncmp(cmds->argv[0], "echo", 4) == 0)
		return(builtin_echo(cmds->argv));
	else if (ft_strncmp(cmds->argv[0], "cd", 2) == 0)
		return(builtin_cd(cmds->argv, shell->env));
	else if (ft_strncmp(cmds->argv[0], "pwd", 3) == 0)
		return(builtin_pwd());
	else if (ft_strncmp(cmds->argv[0], "env", 3) == 0)
		return(builtin_env(shell->env));
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

// funtions that need to be added to exec_builtin


	// else if (ft_strncmp(cmds->argv[0], "export", 6)) //issues here with envp from the main because it's read-only
	// 	return(builtin_export());
	// else if (ft_strncmp(cmds->argv[0], "unset", 5)) //issues here with envp from the main because it's read-only
	// 	return(builtin_unset());
	