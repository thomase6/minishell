/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:57 by texenber          #+#    #+#             */
/*   Updated: 2026/03/27 13:56:04 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	free(cwd);
	return (0);
}

// note in bash pwd still works even if PATH has been unset