/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:53 by texenber          #+#    #+#             */
/*   Updated: 2026/04/26 18:00:36 by texenber         ###   ########.fr       */
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
		if (!new_env[i])
			return (free_partial_env(new_env, i), NULL);
		i++;
	}
	new_env[count] = ft_strdup(var);
	if (!new_env[count])
		return (free_partial_env(new_env, count), NULL);
	new_env[count + 1] = NULL;
	return (free_argv(env), new_env);
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

	if (!argv[1])
		return (print_export(shell->env), 0);
	i = 1;
	err = 0;
	while (argv[i])
	{
		res = process_export(argv[i], shell);
		if (res == 1 || res == -1)
			return (1);
		if (!is_valid_export(argv[i]))
			err = 1;
		i++;
	}
	return (err);
}
