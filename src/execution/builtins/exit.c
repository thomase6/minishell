/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:29 by texenber          #+#    #+#             */
/*   Updated: 2026/01/21 09:59:30 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

int	builtin_exit(char **argv, int last_status)
{
	int exit_code;
	int	i;

	ft_putstr_fd("exit\n", 2);

	if (!argv[1])
		exit(last_status);
	i = 0;
	if (argv[1][i] == '+' || argv[1][i] == '-')
		i++;
	if (!argv[1][i])
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit (2);
	}
	while (argv[1][i])
	{
		if(!ft_isdigit(argv[1][i]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit (2);
		}
		i++;
	}
	if (argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoll(argv[1]);
	exit(exit_code % 256);
}