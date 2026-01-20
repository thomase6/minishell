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