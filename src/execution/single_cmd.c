/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:51 by texenber          #+#    #+#             */
/*   Updated: 2026/01/21 10:00:52 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_argv(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free (av[i]);
		i++;
	}
	if (av)
		free (av);
}

static char	*resolve_cmd(char *cmd, char **dir_path)
{
	int		i;
	char	*tmp;
	char	*result;

	i = -1;
	result = NULL;
	if (!dir_path)
		return (ft_strdup(cmd));
	while (dir_path[++i])
	{
		tmp = ft_strjoin(dir_path[i], "/");
		result = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!result)
			return (NULL);
		if (access(result, X_OK) == 0)
			return (result);
		free (result);
	}
	return (ft_strdup(cmd));
}

static char *find_cmd_path(char **av, char **envp)
{
	char	*env_path;
	char	*result;
	char	**dir_path;
	int		i;

	
	i = 0;
	env_path = NULL;
	if (ft_strchr(av[0], '/'))
		return (ft_strdup(av[0]));
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!env_path)
		dir_path = NULL;
	else
	{
		dir_path = ft_split(env_path, ':');
		if (!dir_path)
			return (ft_strdup(av[0]));
	}
	result = resolve_cmd(av[0], dir_path);
	if (dir_path)
		free_argv(dir_path);
	return (result);
}

// this is more to just execute a single command so if I want to execute multiple ones I need a different function
// this function assumes that a argument vector with spaces is being passed to it which should only expect a list of the arguments 
// envp should also be handed from the main but it should be our own variable
// int single_cmd_execution(char *av, char **envp)
// {
// 	pid_t	pid;
// 	int		status;
// 	t_cmd	*cmd;
// 	char **args;

// 	cmd = malloc(sizeof(t_exec));
// 	if (!cmd)
// 		return (1);
// 	args = ft_split(av, ' ');
// 	// cmd->av = args;
// 	// cmd->is_builtin = false; //for this function, is_builtin should be false otherwise it shouldn't be in this function
// 	cmd->path = find_cmd_path(args, envp);
// 	pid = fork();
// 	if (pid < 0)
// 		return (1);
// 	if (pid == 0)
// 	{
// 		execve(cmd->path, args, envp);
// 		perror("execve");
// 		exit(127);
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 	}
// 	// free(cmd->path[0]);
// 	// free(cmd);
// 	return (0);
// }

//currently Im using a custom function to find the path of the command to be able to execute the provided command however I can use getcwd to just grab the absolute path of it instead
