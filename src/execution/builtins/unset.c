/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:22:44 by texenber          #+#    #+#             */
/*   Updated: 2026/03/27 13:57:28 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include "../../../inc/execution.h"

// this function is meant to remove the line in the env that we are trying to remove and then it rewrites the other env pointers as if the line didn't exist in the first place
char	**rem_env_var(char **env, int index)
{
	char	**new_env;
	int		i;
	int		j;
	int		count;

	count = 0;
	while (env[count])
		count++;
	// after identifying the index calling this function with a single line will cause it to delete the line and return an empty env
	if (count == 1)
	{
		new_env = malloc(sizeof(char *) * 1);
		if (!new_env)
			return (NULL);
		new_env[0] = NULL;
		free(env[index]);
		free(env);
		return (new_env);
	}
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (i == index)
			free(env[i]);
		else
		{
			new_env[j] = env[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free(env);
	return (new_env);
}

int	builtin_unset(char **argv, t_shell *shell)
{
	char	**new_env;
	int		i;
	int		index;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		index = find_env_var(shell->env, argv[i]);
		if (index >= 0)
		{
			new_env = rem_env_var(shell->env, index);
			if (!new_env)
				return (1);
			shell->env = new_env;
		}
		i++;
	}
	return (0);
}
