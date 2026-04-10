/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:49 by texenber          #+#    #+#             */
/*   Updated: 2026/04/10 10:43:15 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

// ORIGINAL FUNCTION RETURN HERE IF YOU HAVE NO IDEA WHAT IS HAPPENING 
int	builtin_cd(char **argv, t_shell *shell) // CHANGE: change **envp for t_shell *shell 
{
	char	*path;
	char	*home;
	// char	*old_pwd;
	// char	*cwd;
	int		i;

	if (argv[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	// if (getcwd(cwd, sizeof(cwd)) == NULL) // if we fail to get the cwd then we set it to NULL-terminator
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
	// else if (ft_strcmp(argv[1], "-") == 0)
	// {
	// 	old_pwd = NULL;
	// 	i = 0;
	// }
	else
		path = argv[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
	return (0);
}

//uses find_env_var and adapts it to skip the key for both HOME and oldpwd
// char	*get_env(char **env, char *key)
// {

// 	return (NULL);
// }


// int	builtin_cd(char **argv, t_shell *shell) // CHANGE: change **envp for t_shell *shell 
// {
// 	char	*path;
// 	char	*oldpwd;
// 	char	*newpwd;

// 	if (argv[2])
// 		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);	
// 	if (!argv[1])
// 		path = get_env(shell->env, "HOME");
// 	else if (ft_strncmp(argv[1], "-"))
// 	else
// 		path = argv[1];
// 	if (chdir(path) != 0)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd("cd: ", 2);
// 		ft_putstr_fd(path, 2);
// 		ft_putstr_fd(": ", 2);
// 		perror("");
// 		return (1);
// 	}
// 	return (0);
// }

