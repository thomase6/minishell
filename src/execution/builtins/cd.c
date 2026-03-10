/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:49 by texenber          #+#    #+#             */
/*   Updated: 2026/03/09 12:59:41 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

int	builtin_cd(char **argv, char **envp) // CHANGE: change **envp for t_shell *shell 
{
	char	*path;
	char	*home;
	int		i;

	if (!argv[1])
	{
		home = NULL;
		i = 0;
		while (envp[i])
		{
			if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			{
				home = envp[i] + 5;
				break;
			}
			i++;
		}
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
		path = home;
	}
	else
		path = argv[1];

	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
	return (0);
}
