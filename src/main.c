/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:57 by texenber          #+#    #+#             */
/*   Updated: 2026/03/12 16:06:39 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	//signal handler
	//setup_signals(); need to make this function
	while(1)
	{
		line = readline("PLEASE WRITE SOMETHING$");
		printf("%s\n", line);
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			break;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue; //gotta change this because I don't want to use continue.
		}
		add_history(line);
		// cmds = parse_input(line, &shell);
		// this is temporary while the parsing is not available.
		t_cmd a;
		// t_cmd b;
    	char *cmd1[] = {"export", "hoyo",NULL};
		// char *cmd2[] = {"env",NULL};
    	int status;

    	a.argv = cmd1;
    	a.infile = -1;
    	a.outfile = -1;
    	a.is_builtin = 1;
		// a.next = &b;
    	a.next = NULL;
		// b.argv = cmd2;
    	// b.infile = -1;
    	// b.outfile = -1;
    	// b.is_builtin = 1;
		// b.next = NULL;
		//temporary code execution while the parsing is not available
		execute_cmds(&a, &shell);
		// if (cmds)
		// {
		// 	execute_cmds(cmds, &shell);
		// 	free_cmds(cmds);// need to make this function
		// }
		free(line);
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