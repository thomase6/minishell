/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:53 by texenber          #+#    #+#             */
/*   Updated: 2026/04/25 12:58:01 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include "../../../inc/execution.h"

// this function changes the value of a string in the env double pointer at
// position i with the string var
int	update_env_var(char **env, int i, char *var)
{
	char	*new_str;

	new_str = ft_strdup(var);
	if (!new_str)
		return (-1);
	free(env[i]);
	env[i] = NULL;
	env[i] = new_str;
	return (0);
}

char	**add_env_var(char **env, char *var)
{
	char	**new_env;
	int		count;
	int		i;

	count = 0;
	while (env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[count] = ft_strdup(var);
	if (!new_env[count])
	{
		free(new_env);
		return (NULL);
	}
	new_env[count + 1] = NULL;
	free_argv(env);
	return (new_env);
}
// this function is supposed to print onto standard output the env with
// "export"

void	print_export(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
// this function is basically just checking that the first character is a
// letter or an underscore and that everything after is either a number, letter
// or an underscore until the '='.

int	is_valid_export(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if ((!ft_isalnum(arg[i])) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_export(char **argv, t_shell *shell)
{
	int		i;
	int		res;
	int		err;
	char	*var_with_equal;

	if (!argv[1])
	{
		print_export(shell->env);
		return (0);
	}
	i = 1;
	err = 0;
	while (argv[i])
	{
		if (!is_valid_export(argv[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			err = 1;
		}
		else
		{
			if (ft_strchr(argv[i], '='))
			{
				res = set_env_var(shell, argv[i]);
				if (res == -1)
					return (1);
			}
			else
			{
				var_with_equal = ft_strjoin(argv[i], "=");
				if (!var_with_equal)
					return (1);
				res = set_env_var(shell, var_with_equal);
				free(var_with_equal);
				var_with_equal = NULL;
				if (res == 1)
					return (1);
			}
		}
		i++;
	}
	if (err == 1)
		return (1);
	else
		return (0);
}
