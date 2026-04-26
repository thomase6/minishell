/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 04:13:59 by texenber          #+#    #+#             */
/*   Updated: 2026/04/26 17:56:06 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_fd(t_cmd *cmds, int *prev_fd, int *fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmds->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

pid_t	handle_fork(t_shell *shell, int prev_fd, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		if (fd[0] != -1)
			close(fd[0]);
		if (fd[1] != -1)
			close(fd[1]);
		if (prev_fd != -1)
			close(prev_fd);
		shell->last_status = 1;
		return (-1);
	}
	return (pid);
}

int	setup_pipe(t_cmd *cmds, t_shell *shell, int prev_fd, int *fd)
{
	fd[0] = -1;
	fd[1] = -1;
	if (cmds->next && pipe(fd) < 0)
	{
		if (prev_fd != -1)
			close(prev_fd);
		shell->last_status = 1;
		return (0);
	}
	return (1);
}

void	cmd_not_found(char *cmd)
{
	char	*msg;

	msg = ft_strjoin(cmd, ": command not found\n");
	if (!msg)
		return ;
	ft_putstr_fd(msg, 2);
	free (msg);
	msg = NULL;
}

void	file_no_access(char *cmd)
{
	char	*msg;

	msg = ft_strjoin(cmd, ": permission denied\n");
	if (!msg)
		return ;
	ft_putstr_fd(msg, 2);
	free (msg);
	msg = NULL;
}
