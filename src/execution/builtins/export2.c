/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:51:19 by texenber          #+#    #+#             */
/*   Updated: 2026/04/22 12:07:51 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

// first we identify if the var string exists in the envp, if it does we update that variable with the new information and if it doesn't exist we create it at the bottom of the envp
int	set_env_var(t_shell *shell, char *var)
{
	char	**new_env;
	int		index;

	//first we search for the variable , if we do find it we return the index in which we found the variable
	index = find_env_var(shell->env, var);
	//if we find it we update the variable with the new information that needs to be updated or the value in it
	if (index >= 0)
		return (update_env_var(shell->env, index, var));
	// otherwise we add the variable to our env and that's it 
	else
	{
		new_env = add_env_var(shell->env, var);
		if (!new_env)
			return (1);
		shell->env = new_env;
		return (0);
	}
}

//this function finds the key string in the env pointer and check to see if it's the one we are looking for
int	find_env_var(char **env, char *key)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return (-1);
	key_len = 0;
	i = 0;
	while (key[key_len] && key[key_len] != '=')
		key_len++;
	while (env[i])
	{
		if ((ft_strncmp(env[i], key, key_len) == 0) && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
