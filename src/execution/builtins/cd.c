/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:49 by texenber          #+#    #+#             */
/*   Updated: 2026/04/09 14:31:35 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

int	builtin_cd(char **argv, t_shell *shell) // CHANGE: change **envp for t_shell *shell 
{
	char	*path;
	char	*home;
	// char	*old_pwd; //work in progress.
	// char	*cwd;
	int		i;

	if (argv[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	// if (getcwd(cwd, sizeof(cwd)) == NULL) // if we fail to get the cwd then we set it to NULL-terminator //work in progress.
	// 	cwd[i] = '\0';
		
	if (!argv[1])
	{
		home = NULL;
		i = 0;
		while (shell->env[i])
		{
			if (ft_strncmp(shell->env[i], "HOME=", 5) == 0)
			{
				home = shell->env[i] + 5;
				break ;
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
	// else if (ft_strcmp(argv[1], "-") == 0) //work in progress.
	// {
	// 	old_pwd = NULL;
	// 	i = 0;
	// }
	else
		path = argv[1];
	// make sure to add the perror message afterwards.
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
