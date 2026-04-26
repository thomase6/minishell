/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:51:19 by texenber          #+#    #+#             */
/*   Updated: 2026/04/26 18:00:58 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

// first we identify if the var string exists in the envp, if it does we update
// that variable with the new information and if it doesn't exist we create it
// at the bottom of the envp
int	set_env_var(t_shell *shell, char *var)
{
	char	**new_env;
	int		index;

	index = find_env_var(shell->env, var);
	if (index >= 0)
		return (update_env_var(shell->env, index, var));
	else
	{
		new_env = add_env_var(shell->env, var);
		if (!new_env)
			return (1);
		shell->env = new_env;
		return (0);
	}
}

// this function finds the key string in the env pointer and check to see if
// it's the one we are looking for
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

void	invalid_identifier(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	process_export(char	*arg, t_shell *shell)
{
	char	*var_with_equal;
	int		res;

	if (!is_valid_export(arg))
		return (invalid_identifier(arg), 0);
	if (ft_strchr(arg, '='))
		return (set_env_var(shell, arg));
	var_with_equal = ft_strjoin(arg, "=");
	if (!var_with_equal)
		return (-1);
	res = set_env_var(shell, var_with_equal);
	free(var_with_equal);
	var_with_equal = NULL;
	return (res);
}

void	free_partial_env(char **env, int i)
{
	while (i > 0)
	{
		free(env[--i]);
		env[i] = NULL;
	}
	free(env);
}
