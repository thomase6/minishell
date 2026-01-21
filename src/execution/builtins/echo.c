/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:45 by texenber          #+#    #+#             */
/*   Updated: 2026/01/21 09:59:46 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

// this function is supposed to mimic the builtin command echo which prints to standard output the argument after echo unless that argument is the flag '-n'
// in that case we print the argument without a newline.
int	builtin_echo(char **argv)
{
	int i;
	int n_flag;
	int j;

	i = 1;
	n_flag = 0;
	while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] == '\0')
		{
			n_flag = 1;
			i++;
		}
		else 
			break;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i],1);
		if (argv[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n',1);
	return (0);
}
