/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:47 by texenber          #+#    #+#             */
/*   Updated: 2026/03/26 13:09:49 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

int signal_main_hook(void)
{
	if (g_signal == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 0;
	}
	return (0);
}

void siginthandler(int sig)
{
	(void)sig;
	g_signal = SIGINT;	
}

void	setup_main_signals(struct sigaction *sa)
{
	sa->sa_handler = siginthandler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = SA_RESTART;
	sigaction(SIGINT, sa, NULL);
	signal(SIGQUIT, SIG_IGN); //when ignoring the signal it is ok to use signal instead of sigaction	
}