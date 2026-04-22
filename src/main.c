/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:57 by texenber          #+#    #+#             */
/*   Updated: 2026/04/22 18:46:02 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/execution.h"
#include "../inc/lap.h"

volatile sig_atomic_t	g_signal = 0; //global variable declaration and definition

// void print_redirs(t_exec_redir *r)
// {
// 	while (r)
// 	{
// 		printf("type: %d, file: %s\n", r->type, r->filename);
// 		r = r->next;
// 	}
// }

//this function is for testing
// static void print_cmds(t_cmd *cmds)
// {
// 	int	cmd_num = 1;
// 	t_cmd	*current = cmds;
	
// 	printf("\n===CMDS===\n");
// 	while(current)
// 	{
// 		printf("Command %d:\n", cmd_num);
// 		printf(" argv: ");
// 		int i = 0;
// 		if (current->argv)
// 		{
// 			while (current->argv[i])
// 			{
// 				printf("[%s] ", current->argv[i]);
// 				i++;
// 			}
// 		}		
// 		printf("\n");
// 		printf("argv: %s\n", current->argv[0]);
// 		printf("infile: %s\n", current->infile);
// 		printf("outfile: %s\n", current->outfile);
// 		printf("append: %d\n", current->append);
// 		printf("heredoc Delimiter: %s\n", current->heredoc_delim);
// 		printf("heredoc Quotes: %d\n", current->heredoc_quoted);
// 		printf("heredoc Content: %s\n", current->heredoc_content);
// 		printf("is_builtin: %d\n", current->is_builtin);
// 		printf("infile_fd: %d\n", current->infile_fd);
// 		printf("outfile_fd: %d\n", current->outfile_fd);
// 		printf("next: %s\n", current->next ? "yes" : "no");
// 		current = current->next;
// 		cmd_num++;
// 		i++;
// 	}
// 	printf("\n===END OF CMDS===\n");
// }

// //this function is for testing
// static void	print_tokens(t_token *tokens)
// {
// 	int	i = 0;
// 	t_token *current = tokens;
	
// 	printf("\n===TOKENS===\n");
// 	while (current)
// 	{
// 		printf("Token %d:\n", i);
// 		printf(" type: %d\n", current->type);
// 		printf(" value: [%s]\n", current->value);
// 		printf(" quoted: %d\n", current->quoted);
// 		printf(" next: %s\n", current->next ? "yes" : "no");
// 		printf("\n");
// 		current = current->next;
// 		i++;
// 	}
// 	printf("\n===END OF TOKENS===\n");
// }

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
		{
			// ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		// Lexer and Parser
		tokens = process_input(line, &shell);
        	if (!tokens)
       		{
            		free(line);
            		continue;
        	}
		// print_tokens(tokens); // REMOVE AFTER TESTING
		cmds = parser(tokens, &shell);
		free_tokens(tokens);
        	/*if (!cmds)
        	{
           	 	printf("Parser failed or returned no commands.\n");
           	 	free_tokens(tokens);
           	 	free(line);
           	 	continue;
        	}*/
		// expander goes here
		// set_builtin_and_open(cmds); // REMOVE AFTER TESTING
		// print_cmds(cmds); // REMOVE AFTER TESTING
		// print_redirs(cmds->exec_redirs); // REMOVE AFTER TESTING
		if (cmds)
		{
			execute_cmds(cmds, &shell);
			free_cmds(cmds);// need to make this function
		}
		free(line);
		if (g_signal == SIGINT)
			shell.last_status = 130;
	}
	//clean up SHELL
	cleanup_shell(&shell);
	// printf("%d", shell.last_status);
	return (shell.last_status);
}
