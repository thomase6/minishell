/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:30 by texenber          #+#    #+#             */
/*   Updated: 2026/04/06 11:16:23 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

// if the file doesn't exist it fails to open it in case of the infile which should lead to an error message with exit code 1.
void	set_infile_and_outfile(t_cmd *cmds)
{
	t_cmd	*current = cmds;
	while (current)
	{
		if (current->infile) // <
		{
			current->infile_fd = open(current->infile, O_RDONLY);
			if (current->infile_fd < 0) 
				perror(current->infile);
		}
		if (current->outfile) // >
		{
			if (current->append)
				current->outfile_fd = open(current->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				current->outfile_fd = open(current->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (current->outfile_fd < 0)
				perror(current->outfile);
		}
		current = current->next;
	}
}

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

// is_builtin = 0 so all we have to do is check and change if it is a builtin otherwise let it be.
void	set_builtin_flag(t_cmd *cmds)
{
	t_cmd	*current = cmds;

	while (current)
	{
		if (current->argv && current->argv[0])
		{
			if (cmd_is_builtin(current->argv[0]) == 1)
				current->is_builtin = 1;
		}
		current=current->next;
	}
}

void set_builtin_and_open(t_cmd *cmds)
{
	set_builtin_flag(cmds);
	set_infile_and_outfile(cmds);
}

//this function just determines whether we are execute a builtin or an external command.
int	execute_cmds(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return (0);
	set_builtin_and_open(cmds);
	// might have to add a way to catch an error early
	if (!cmds->next && cmds->is_builtin == 1) // it's not necessary to check for the next command because it should be ok to have a command after the built-in function
		return (exec_builtin_parent(cmds, shell));
	return (exec_pipeline(cmds, shell));
}
