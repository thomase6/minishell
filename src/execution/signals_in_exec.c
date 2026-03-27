/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_in_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:04:01 by texenber          #+#    #+#             */
/*   Updated: 2026/03/27 10:05:29 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_signals_for_child(void) // SIG_DFL is used to inform the kernel that there is no handler for this signal and to use the default action.
{
	signal(SIGINT, SIG_DFL); 
	signal(SIGQUIT, SIG_DFL);
}

void	set_signals_for_parent(void)
{
	signal(SIGINT, SIG_IGN); 
	signal(SIGQUIT, SIG_IGN);
}