/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:29 by texenber          #+#    #+#             */
/*   Updated: 2026/04/25 10:44:50 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

bool	long_long_overflow(const char *str)
{
	int		len;
	int		i;
	int		neg;
	char	*tmp;

	len = 0;
	i = 0;
	neg = 0;
	tmp = (char *)str;
	if (tmp[0] == '+' || tmp[0] == '-')
	{
		if (tmp[0] == '-')
			neg = 1;
		tmp++;
	}
	while (*tmp == '0')
		tmp++;
	if (*tmp == '\0')
		return (0);
	len = ft_strlen(tmp);
	if (len > 19)
		return (1);
	else if (len == 19 && neg == 0
		&& ft_strcmp(tmp, "9223372036854775807") > 0)
		return (1);
	else if (len == 19 && neg == 1
		&& ft_strcmp(tmp, "9223372036854775808") > 0)
		return (1);
	return (0);
}

// make sure that the exit code is saved to the last_status to make sure that
// echo $? works with exit.
int	builtin_exit(t_cmd *cmds, t_shell *shell, int *fd)
{
	int			exit_code;
	int			i;
	char		*trimmed;

	ft_putstr_fd("exit\n", 1);
	if (!cmds->argv[1])
	{
		cleanup_shell(shell);
		free_cmds(cmds);
		close(fd[0]);
		close(fd[1]);
		exit(shell->last_status);
	}
	i = 0;
	trimmed = ft_strtrim(cmds->argv[1], " \t");
	if (trimmed[i] == '+' || trimmed[i] == '-')
		i++;
	if (!trimmed[i])
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmds->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		cleanup_shell(shell);
		free_cmds(cmds);
		close(fd[0]);
		close(fd[1]);
		exit (2);
	}
	while (trimmed[i])
	{
		if (!ft_isdigit(trimmed[i]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmds->argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free(trimmed);
			trimmed = NULL;
			cleanup_shell(shell);
			free_cmds(cmds);
			close(fd[0]);
			close(fd[1]);
			exit (2);
		}
		i++;
	}
	if (cmds->argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		free(trimmed);
		trimmed = NULL;
		cleanup_shell(shell);
		free_cmds(cmds);
		close(fd[0]);
		close(fd[1]);
		exit (1);
	}
	if (long_long_overflow(trimmed))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmds->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free(trimmed);
		trimmed = NULL;
		cleanup_shell(shell);
		free_cmds(cmds);
		close(fd[0]);
		close(fd[1]);
		exit (2);
	}
	exit_code = ft_atoll(trimmed);
	free(trimmed);
	trimmed = NULL;
	cleanup_shell(shell);
	free_cmds(cmds);
	close(fd[0]);
	close(fd[1]);
	exit(exit_code % 256);
}
