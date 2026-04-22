/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:41 by texenber          #+#    #+#             */
/*   Updated: 2026/04/22 15:17:54 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

void	no_such_argument(char *arg)
{
	char *msg;

	msg = ft_strjoin(arg, ": No such file or directory\n");
	if (!msg)
		return ;
	ft_putstr_fd(msg, 2);
	free (msg);
}

int	builtin_env(char **argv, char **envp)
{
	int	i;

	if (argv[1])
	{
		no_such_argument(argv[1]);
		return (127);
	}
	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
