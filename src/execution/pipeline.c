/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:37 by texenber          #+#    #+#             */
/*   Updated: 2026/04/26 18:26:10 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

// this function is meant to check whether the cmd exists and then
// it checks if it's executable
int	cmd_check(char *path, char *cmd)
{
	if (access(path, F_OK) != 0)
	{
		cmd_not_found(cmd);
		return (127);
	}
	if (access(path, X_OK) != 0)
	{
		file_no_access(cmd);
		return (126);
	}
	return (0);
}

// this function is used just to close prev_fd, and the array of fd[2]
void	close_all(int prev_fd, int fd[2])
{
	if (prev_fd != -1)
	{
		close(prev_fd);
		prev_fd = -1;
	}
	if (fd[0] != -1)
	{
		close(fd[0]);
		fd[0] = -1;
	}
	if (fd[1] != -1)
	{
		close(fd[1]);
		fd[1] = -1;
	}
}

// This function is meant to wait for every child and return the last status
// of the children only if it's the last_pid which means that there are no
// other commands after it
static int	wait_all(pid_t last_pid, int *last_status)
{
	int		status;
	pid_t	pid;
	int		last;

	last = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", 2);
				else if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
				last = 128 + WTERMSIG(status);
			}
		}
		pid = wait(&status);
	}
	*last_status = last;
	return (last);
}

void	exec_child(t_cmd *cmds, t_shell *shell, int prev_fd, int fd[2])
{
	char	*path;
	int		err;

	path = NULL;
	set_signals_for_child();
	if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (cmds->next)
		dup2(fd[1], STDOUT_FILENO);
	if (all_redirections(cmds) == 1)
	{
		close_all(prev_fd, fd);
		child_exit(cmds, shell, 1);
	}
	close_all(prev_fd, fd);
	if (cmds->is_builtin == 1)
		exec_builtin_child(cmds, shell);
	empty_cmd(cmds, shell);
	path = resolve_path(cmds->argv[0], shell->env);
	err = cmd_check(path, cmds->argv[0]);
	execve(path, cmds->argv, shell->env);
	free(path);
	path = NULL;
	child_exit(cmds, shell, err);
}

// this is the first process that starts the pipeline, forks and starts the
// child process, it also closses all fds that were not used by the parent
int	exec_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;

	prev_fd = -1;
	last_pid = -1;
	set_signals_for_parent();
	while (cmds)
	{
		if (!setup_pipe(cmds, shell, prev_fd, fd))
			return (1);
		pid = handle_fork(shell, prev_fd, fd);
		if (pid < 0)
			return (1);
		if (pid == 0)
			exec_child(cmds, shell, prev_fd, fd);
		if (!cmds->next)
			last_pid = pid;
		handle_fd(cmds, &prev_fd, fd);
		cmds = cmds->next;
	}
	wait_all(last_pid, &shell->last_status);
	setup_main_signals();
	return (0);
}
