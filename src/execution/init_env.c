/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:33 by texenber          #+#    #+#             */
/*   Updated: 2026/04/26 17:20:56 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

char	*build_shlvl(int shlvl)
{
	char	*shlvl_str;
	char	*res;

	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		return (NULL);
	res = ft_strjoin("SHLVL=", shlvl_str);
	free (shlvl_str);
	shlvl_str = NULL;
	return (res);
}

void	update_shlvl(t_shell *shell)
{
	int		i;
	int		shlvl;
	char	*tmp;
	char	**new_env;

	i = find_env_var(shell->env, "SHLVL");
	if (i >= 0)
		shlvl = (ft_atoi(shell->env[i] + 6)) + 1;
	else
		shlvl = 1;
	tmp = build_shlvl(shlvl);
	if (!tmp)
		return ;
	if (i >= 0)
	{
		free(shell->env[i]);
		shell->env[i] = tmp;
	}
	else
	{
		new_env = add_env_var(shell->env, tmp);
		free(tmp);
		if (new_env)
			shell->env = new_env;
	}
}

//this function is meant to copy the envp and make a version that
//I can edit if needed.
char	**copy_env(char **envp)
{
	char	**new_env;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
			return (free_partial_env(new_env, i), NULL);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	init_env(t_shell *shell, char **envp)
{
	shell->env = copy_env(envp);
	if (!shell->env)
		return (-1);
	shell->last_status = 0;
	update_shlvl(shell);
	return (0);
}
