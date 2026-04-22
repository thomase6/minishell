/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 04:13:59 by texenber          #+#    #+#             */
/*   Updated: 2026/04/22 09:50:26 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cmd_not_found(char *cmd)
{
	char	*msg;

	msg = ft_strjoin(cmd, ": command not found\n");
	if (!msg)
		return ;
	ft_putstr_fd(msg, 2);
	free (msg);
}

void	file_no_access(char *cmd)
{
	char	*msg;

	msg = ft_strjoin(cmd, ": permission denied\n");
	if (!msg)
		return ;
	ft_putstr_fd(msg, 2);
	free (msg);
}
