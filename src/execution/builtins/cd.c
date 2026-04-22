/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:49 by texenber          #+#    #+#             */
/*   Updated: 2026/04/22 15:20:17 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

//uses find_env_var and adapts it to skip the key for both HOME and oldpwd
char	*get_env(char **env, char *key)
{
	int	i;
	int	len;

	i = find_env_var(env, key);
	if (i == -1)
		return (NULL);
	len = ft_strlen(key);
	return (env[i] + len + 1);
}

int	update_pwd_env(t_shell *shell, char *oldpwd, char *newpwd)
{
	char	*oldtmp;
	char	*newtmp;

	oldtmp = ft_strjoin("OLDPWD=", oldpwd);
	newtmp = ft_strjoin("PWD=", newpwd);
	if (!oldtmp || !newtmp)
		return (free(oldtmp), free(newtmp), 1);
	set_env_var(shell, oldtmp);
	set_env_var(shell, newtmp);
	free(oldtmp);
	free(newtmp);
	return (0);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	if (argv[1] && argv[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	oldpwd = getcwd(NULL, 0);
	if (!argv[1])
		path = get_env(shell->env, "HOME");
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		path = get_env(shell->env, "OLDPWD");
		if (!path)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), free(oldpwd), 1);
		printf("%s\n", path);
	}
	else
		path = argv[1];
	if (!path)
		return (ft_putstr_fd("cd: HOME not set\n", 2), free(oldpwd), 1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (free(oldpwd), 1);
	}
	newpwd = getcwd(NULL, 0);
	update_pwd_env(shell, oldpwd, newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
