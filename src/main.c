/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:57 by texenber          #+#    #+#             */
/*   Updated: 2026/01/21 10:00:58 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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