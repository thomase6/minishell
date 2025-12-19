#include "../inc/minishell.h"

int main(void)
{
	char *input;

	while (1)
	{
		if (!(input = readline("input: ")))
			return (1);
		char **av = ft_split(input, ' ');
		int i = 0;
		while (av[i])
		{
			printf("av[%d]: %s\n", i, av[i]);
			i++;
		}
	}
}



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