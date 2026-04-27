/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:22:44 by texenber          #+#    #+#             */
/*   Updated: 2026/04/26 11:46:45 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include "../../../inc/execution.h"

char	**copy_env_except_i(char **env, int index, int count)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (i == index)
		{
			free(env[i]);
			env[i] = NULL;
		}
		else
		{
			new_env[j] = env[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (free(env), env = NULL, new_env);
}

// this function is meant to remove the line in the env that we are trying to
// remove and then it rewrites the other env pointers as if the line didn't
// exist in the first place
char	**rem_env_var(char **env, int index)
{
	char	**new_env;
	int		count;

	count = 0;
	while (env[count])
		count++;
	if (count == 1)
	{
		new_env = malloc(sizeof(char *) * 1);
		if (!new_env)
			return (NULL);
		new_env[0] = NULL;
		free(env[index]);
		env[index] = NULL;
		free(env);
		env = NULL;
		return (new_env);
	}
	new_env = copy_env_except_i(env, index, count);
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
