/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:57 by texenber          #+#    #+#             */
/*   Updated: 2026/04/24 08:51:17 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/execution.h"
#include "../inc/lap.h"

volatile sig_atomic_t	g_signal = 0; //global variable declaration and definition

void	cleanup_shell(t_shell *shell)
{
	rl_clear_history();
	if (shell->env)
		free_argv(shell->env);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*line;
	t_cmd	*cmds;
	t_token	*tokens;
	(void)ac;
	(void)av;
	if (init_env(&shell, envp) == -1)
	{
		ft_putstr_fd("Error: failed to initialize shell\n", 2);
		return (1);
	}
	setup_main_signals();
	rl_signal_event_hook = signal_main_hook; // this is the proper way of handling functions that need to be executed after the signal is interrupted. 
	while (1)
	{
		g_signal = 0;// signal reset before every prompt
		line = readline("Minishell:$ ");
		if (!line)
			break ;
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		tokens = process_input(line, &shell);
		free(line);
		if (!tokens)
				continue;
		cmds = parser(tokens, &shell);
		free_tokens(tokens);
		if (cmds)
		{
			execute_cmds(cmds, &shell);
			free_cmds(cmds);
		}
		if (g_signal == SIGINT)
			shell.last_status = 130;
	}
	cleanup_shell(&shell);
	return (shell.last_status);
}
