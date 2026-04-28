/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:29 by texenber          #+#    #+#             */
/*   Updated: 2026/04/28 08:45:58 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

int	get_sign(char **str)
{
	int	neg;

	neg = 0;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			neg = 1;
		(*str)++;
	}
	return (neg);
}

bool	long_long_overflow(const char *str)
{
	int		len;
	int		neg;
	char	*tmp;

	len = 0;
	tmp = (char *)str;
	neg = get_sign(&tmp);
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

void	numeric_error(char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	is_valid_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_cmd *cmds, t_shell *shell, int *fd)
{
	int			exit_code;
	char		*trimmed;

	ft_putstr_fd("exit\n", 1);
	if (!cmds->argv[1])
		exit_and_cleanup(shell, cmds, fd, shell->last_status);
	trimmed = ft_strtrim(cmds->argv[1], " \t");
	if (!is_valid_num(trimmed) || long_long_overflow(trimmed))
	{
		numeric_error(cmds->argv[1]);
		free(trimmed);
		exit_and_cleanup(shell, cmds, fd, 2);
	}
	if (cmds->argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		free(trimmed);
		exit_and_cleanup(shell, cmds, fd, 1);
	}
	exit_code = ft_atoll(trimmed);
	free(trimmed);
	exit_and_cleanup(shell, cmds, fd, exit_code % 256);
	return (0);
}
