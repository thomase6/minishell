/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:37 by texenber          #+#    #+#             */
/*   Updated: 2026/04/19 15:28:13 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

//this function is meant to check whether the cmd exists and then it checks if it's executable
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
	if (prev_fd != -1) //this could be an issue because there is the chance of a reuse bug causing a double close.
		close(prev_fd);
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

// This function is meant to wait for every child and return the last status of the children only if it's the last_pid which means that there are no other commands after it
// *** GOTTA FIX *** currently "sleep 10" | "env" doesn't print a space after the interruption happens ^C
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
	char	**envp;
	char	*path;
	int		err;

	set_signals_for_child();// signals reset to default action
	envp = shell->env;
	if (prev_fd != -1) //if the previous fd exists we are gonna duplicate it
		dup2(prev_fd, STDIN_FILENO);
	if (cmds->next) //if the previous fd exists we are gonna duplicate it
		dup2(fd[1], STDOUT_FILENO);
	if (all_redirections(cmds) == 1)
		exit (1);
	close_all(prev_fd, fd); //make sure to close the previous fd and the fd array.
	if (cmds->is_builtin == 1)
		exit(exec_builtin(cmds, shell));
	path = resolve_path(cmds->argv[0], envp);
	err = cmd_check(path, cmds->argv[0]);
	if (err != 0)
	{
		free(path);
		exit(err);
	}
	update_underscore(shell, path);
	execve(path, cmds->argv, envp);
	envp = shell->env; // refreshes the envp after updating it in the _= variable
	perror("minishell");
	free(path);
	exit(0);
}

// this is the first process that starts the pipeline, forks and starts the child process, it also closses all fds that were not used by the parent but the children needed
//we do this for every single cmd unless the cmd is a builtin.
// tracking the last pid of the last executable command.
// TOO MANY VARIABLES.
int	exec_pipeline(t_cmd *cmds, t_shell *shell)
{
	char	**envp;
	int		*last_status;
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;
	int		status;

	prev_fd = -1;
	last_pid = -1; //set to -1 because 0 is a valid pid 
	envp = shell->env;
	last_status = &shell->last_status;
	set_signals_for_parent();
	while (cmds)
	{
		fd[0] = -1;
		fd[1] = -1;
		if (cmds->next && pipe(fd) < 0)
		{
			if (prev_fd != -1)
				close(prev_fd);
			*last_status = 1;
			return (-1);
		}
		pid = fork();
		if (pid < 0)
		{
			if (fd[0] != -1)
				close(fd[0]);
			if (fd[1] != -1)
				close(fd[1]);
			if (prev_fd != -1)
				close(prev_fd);
			*last_status = 1;
			return (-1);
		}
		if (pid == 0)
			exec_child(cmds, shell, prev_fd, fd);
		if (!cmds->next) // this is a check to find the last pid to make sure that we can use this in the wait afterwards
			last_pid = pid;
		if (cmds->infile_fd != -1)
			close(cmds->infile_fd);
		if (cmds->outfile_fd != -1)
			close(cmds->outfile_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmds->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmds = cmds->next;
	}
	status = wait_all(last_pid, last_status);
	setup_main_signals();
	return (0);
}
