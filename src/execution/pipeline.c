/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:37 by texenber          #+#    #+#             */
/*   Updated: 2026/01/21 10:00:38 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

//this function is meant to check whether the cmd exists and then it checks if it's executable
int	cmd_check(char *path, char *cmd)
{
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(path);
		return (127);
	}
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": permission denied\n", 2);
		free(path);
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
// This function is meant to wait for every child and return the last status of the children
int wait_all(int *last_status) //rewrite this to a simpler version // CHANGE: shell->last_status
{
	int		status;
	pid_t	pid;
	int		last;

	last = 0;
	while((pid = wait(&status)) > 0) 
	{
		if (WIFEXITED(status)) //this should be the normal exit when an error terminates the program
			last = WEXITSTATUS(status);
		else if (WIFSIGNALED(status)) //this is for signal termination like Ctrl + C
			last = 128 + WTERMSIG(status);
	}
	*last_status = last;
	return (last);
}

//this function is the actual child process that duplicates if necessary, closes the fds that are not used, then finds the path of the cmd in the child.
// after it has found the path it checks to see if it's executable and then it executes it.
void	exec_child(t_cmd *cmds, t_shell *shell, int prev_fd, int fd[2]) // **NEW**
{
	// set_signals_for_child();// no clue what this is for yet
	char	**envp;
	char	*path;
	int		err;

	envp = shell->env;
	if (cmds->infile != -1)
	{
		dup2(cmds->infile, STDIN_FILENO);
		close(cmds->infile);
	}
	else if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (cmds->outfile != -1)
	{
		dup2(cmds->outfile, STDOUT_FILENO);
		close(cmds->outfile);
	}
	else if (cmds->next)
		dup2(fd[1], STDOUT_FILENO);

	close_all(prev_fd, fd);

	if (!cmds->argv || !cmds->argv[0] || cmds->argv[0][0] == '\0') //this is just necessary to make the executor work independently and to avoid parser bugs
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit(127);
	}
	if (cmds->is_builtin)
		exit(exec_builtin(cmds, shell));
	path = resolve_path(cmds->argv[0], envp); 
	err = cmd_check(path, cmds->argv[0]);
	if (err != 0)
		exit(err);
	execve(path, cmds->argv, envp);
	perror("minishell");
	free(path);
	exit(126);
}	
// this is the first process that starts the pipeline, forks and starts the child process, it also closses all fds that were not used by the parent but the children needed
//we do this for every single cmd unless the cmd is a builtin.
int	exec_pipeline(t_cmd *cmds, t_shell *shell) // **NEW**
{
	char	**envp;
	int		*last_status;
	int		fd[2];
	int		prev_fd = -1;
	pid_t	pid;

	envp = shell->env;
	last_status = &shell->last_status;
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
			exec_child(cmds, shell, prev_fd, fd); // **NEW**
		if (cmds->infile != -1)
			close(cmds->infile);
		if (cmds->outfile != -1)
			close(cmds->outfile);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmds->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmds = cmds->next;
	}
	return (wait_all(last_status));
}

