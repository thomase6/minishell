/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:41 by texenber          #+#    #+#             */
/*   Updated: 2026/04/22 10:27:47 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

void	update_underscore(t_shell *shell, char *path)
{
	char	*var;

	var = ft_strjoin("_=", path);
	if (!var)
		return ;
	set_env_var(shell, var);
	free(var);
}

// in the env don't worry about _= because bash has a list of special
// variables in env
int	builtin_env(char **envp) // CHANGE: add t_shell *shell
{
	int	i;

	if (!envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
