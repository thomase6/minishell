/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:47 by texenber          #+#    #+#             */
/*   Updated: 2026/03/22 09:29:30 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

void	handle_sigint(int sig)
{
	(void) sig;
	write(1, "\n", 1);	  // Have to test how necessary this line is.
	rl_on_new_line();				// Tells realine we are on a newline.
	rl_replace_line("", 0);			// Clear current input buffer.
	rl_redisplay();					// Redisplay prompt. 
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);		
}