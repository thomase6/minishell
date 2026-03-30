/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:09 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/23 10:21:58 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"
/*
int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_token	*tmp;

	input = "cat << EOF | grep \"hello\" > output.txt >> log.txt < input.txt";
	tokens = lexer(input);
	tmp = tokens;
	if (!tokens)
	{
		printf("Lexer failed or no tokens.\n");
		return (1);
	}
	while (tmp)
	{
		printf("Token type: %d, value: '%s'\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	free_tokens(tokens);
	return (0);
}



// Mock environment variable access for testing
char *get_env_var(const char *var)
{
    if (strcmp(var, "HOME") == 0)
        return "/home/testuser";
    if (strcmp(var, "?") == 0)
        return "0"; // last exit status
    return "";
}
*/

/* ===================== Helper: Token type names ===================== */
const char *token_type_name(t_token_type type)
{
    if (type == TOKEN_WORD) return "WORD";
    if (type == TOKEN_PIPE) return "PIPE";
    if (type == TOKEN_HEREDOC) return "HEREDOC";
    if (type == TOKEN_REDIR_IN) return "REDIR_IN";
    if (type == TOKEN_REDIR_OUT) return "REDIR_OUT";
    if (type == TOKEN_REDIR_OUT_APPEND) return "REDIR_OUT_APPEND";
    return "NONE";
}

/* ===================== Mock environment ===================== */
char *get_env_var(const char *var)
{
    if (strcmp(var, "HOME") == 0) return "/home/testuser";
    if (strcmp(var, "?") == 0) return "0";
    return "";
}
/*
int main(void)
{
    extern char **environ; // system environment
    int last_exit = 0;      // last exit status for $?

    char *tests[] = {
        // Heredoc test
        "cat << EOF\nline1 line2>> |\nline3 < >\nEOF",

        // Environment variable tests
        "echo $HOME",
        "echo '$HOME'",
        "echo $? $HOME",

        // Input/output redirections
        "sort < unsorted.txt > sorted.txt",
        "grep 'pattern' < input.txt >> output.log",

        // Pipes
        "ls -l | grep \".c\" | wc -l",

        // Combined features
        "cat << DELIM | grep pattern >> output.log",
        NULL
    };

    for (int i = 0; tests[i]; i++)
    {
        printf("=== Test %d ===\n", i + 1);
        printf("Input: %s\n", tests[i]);

        // Lexer
        t_token *tokens = lexer(tests[i]);
        if (!tokens)
        {
            printf("Lexer failed or returned no tokens.\n");
            continue;
        }

        // Print tokens
        printf("Tokens:\n");
        for (t_token *tmp = tokens; tmp; tmp = tmp->next)
            printf("  type: %d, value: '%s'\n", tmp->type, tmp->value);

        // Parser
        t_cmd *cmds = parser(tokens, environ, last_exit);
        if (!cmds)
        {
            printf("Parser failed or returned no commands.\n");
            free_tokens(tokens);
            continue;
        }

        // Print parsed commands
        printf("Parsed commands:\n");
        for (t_cmd *c = cmds; c != NULL; c = c->next)
        {
            if (c->argv && c->argv[0])
                printf("  Command: %s\n", c->argv[0]);

            if (c->argv)
            {
                printf("    Args:");
                for (int j = 0; c->argv[j]; j++)
                    printf(" %s", c->argv[j]);
                printf("\n");
            }

            if (c->infile)
                printf("    Input file: %s\n", c->infile);

            if (c->heredoc_delim)
                printf("    Heredoc delimiter: %s (quoted=%d)\n", c->heredoc_delim, c->heredoc_quoted);

            if (c->outfile)
                printf("    Output file: %s (append=%d)\n", c->outfile, c->append);
        }

        free_cmds_lap(cmds);
        free_tokens(tokens);
        printf("------\n\n");
    }

    return 0;
}
*/
int main(void)
{
    extern char **environ;   // Access environment
    int last_exit = 0;
    char *line;

    printf("Welcome to minishell test. Type Ctrl+D to exit.\n");

    while (1)
    {
        line = readline("$ ");        // Read input
        if (!line)                    // Ctrl+D
            break;

        if (*line)                    // Non-empty line
            add_history(line);

        // Lexical analysis
        t_token *tokens = lexer(line);
        if (!tokens)
        {
            printf("Lexer failed or returned no tokens.\n");
            free(line);
            continue;
        }

        // Expand environment variables
        if (expand_tokens(tokens, environ, last_exit) == -1)
            printf("Warning: token expansion failed\n");

        // Parse tokens into commands
        t_cmd *cmds = parser(tokens, environ, last_exit);
        if (!cmds)
        {
            printf("Parser failed or returned no commands.\n");
            free_tokens(tokens);
            free(line);
            continue;
        }

        // Print parsed commands (simulate execution)
        for (t_cmd *c = cmds; c; c = c->next)
        {
            printf("Command: %s\n", c->argv ? c->argv[0] : "(null)");
            if (c->argv)
            {
                printf("  Args:");
                for (int i = 0; c->argv[i]; i++)
                    printf(" %s", c->argv[i]);
                printf("\n");
            }
            if (c->infile)
                printf("  Input file: %s\n", c->infile);
            if (c->outfile)
                printf("  Output file: %s (append=%d)\n", c->outfile, c->append);
            if (c->heredoc_delim)
                printf("  Heredoc delimiter: %s (quoted=%d)\n", c->heredoc_delim, c->heredoc_quoted);
            if (c->heredoc_content)
                printf("  Heredoc content:\n%s", c->heredoc_content);
        }

        free_cmds(cmds);
        free_tokens(tokens);
        free(line);
    }

    printf("\nExiting minishell test.\n");
    return 0;
}
