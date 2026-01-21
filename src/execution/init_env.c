/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:33 by texenber          #+#    #+#             */
/*   Updated: 2026/01/21 10:00:34 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//this function is meant to copy the envp and make a version that I can edit if needed.
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
		{
			while(i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
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
	return (0);
}
