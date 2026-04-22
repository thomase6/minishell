/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:26 by texenber          #+#    #+#             */
/*   Updated: 2026/04/22 09:58:04 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

//this function takes the path and then tries to find the full path of the cmd,
//then it tests them with access and lastly it returns that full path.
char	*resolve_cmd(char *cmd, char **dir_path)
{
	int		i;
	char	*tmp;
	char	*result;

	i = -1;
	result = NULL;
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

// this function finds the right part of the envp were we can find the
// cmd path then it sends it to resolve_cmd to find the cmd path
// make sure cmd is only a cmd without anything added to it
// like "ls" and not "ls -l"
char	*resolve_path(char *cmd, char **envp)
{
	char	*env_path;
	char	*result;
	char	**dir_path;
	int		i;

	i = 0;
	env_path = NULL;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
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
		return (ft_strdup(cmd));
	dir_path = ft_split(env_path, ':');
	if (!dir_path)
		return (ft_strdup(cmd));
	result = resolve_cmd(cmd, dir_path);
	if (dir_path)
		free_argv(dir_path);
	return (result);
}
