/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:57 by texenber          #+#    #+#             */
/*   Updated: 2026/03/27 10:29:48 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


volatile sig_atomic_t g_signal = 0; //global variable declaration and definition

void	cleanup_shell(t_shell *shell)
{
	if (shell->env)
		free_argv(shell->env);
	
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*line;
	t_cmd	*cmds = NULL; //this normally doesn't have to equal NULL, for now it is necessary to avoid crashes.
	(void)ac;
	(void)av;
	if (init_env(&shell, envp) == -1)
	{
		ft_putstr_fd("Error: failed to initialize shell\n", 2);
		return (1);
	}
	setup_main_signals();
	rl_signal_event_hook = signal_main_hook; // this is the proper way of handling functions that need to be executed after the signal is interrupted. 
	while(1)
	{
		g_signal = 0;		// signal reset before every prompt
		line = readline("Minishell: $");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		add_history(line);
		// cmds = parse_input(line, &shell);
		// this is temporary while the parsing is not available.
		t_cmd a;
		// t_cmd b;
    	char *cmd1[] = {"sleep", "10",NULL};
		// char *cmd2[] = {"wc",NULL};
    	// int status;

    	a.argv = cmd1;
    	a.infile = -1;
    	a.outfile = -1;
    	a.is_builtin = 0;
		// a.next = &b;
    	a.next = NULL;
		// b.argv = cmd2;
    	// b.infile = -1;
    	// b.outfile = -1;
    	// b.is_builtin = 0;
		// b.next = NULL;
		//temporary code execution while the parsing is not available
		execute_cmds(&a, &shell);
		// if (cmds)
		// {
		// 	execute_cmds(cmds, &shell);
		// 	free_cmds(cmds);// need to make this function
		// }
		free(line);
		if (g_signal == SIGINT)
			shell.last_status = 130;
	}
	//clean up SHELL
	cleanup_shell(&shell);
	return(shell.last_status);
}


// the main shell structure
// 1. Signals
// 2. Loop: Read the input -> Parse -> Execute -> Repeat.
// 3. Clean up on exit

// int main(int ac, char **av, char **envp)
// {
// 	char	*input;
// 	(void)ac;
// 	(void)av;

// 	while (1)
// 	{
// 		if (!(input = readline("input: ")))
// 			return (1);
// 		av = ft_split(input, '|'); // placeholder for parsing
// 		single_cmd_execution(av[0], envp);
// 	}
// }

// while (shell is running)
// {
//     input = readline()
//     tokens = tokenize(input)
//     commands = parse(tokens)
//     execute(commands)
//     cleanup()
// }


// minishell
// ├─inc
// |	├─minishell.h
// |	├─execution.h
// |	├─parsing.h
// ├─libft
// ├─src
// |	├─main.c
// |	├─execution
// |		├─execution.c
// |	├─parsing
// |		├─parsing.c
// |	├─lexer	
// |		├─lexer.c
// ├─Makefile