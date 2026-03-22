/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:18 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/19 15:50:33 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


typedef struct s_parser_intern
{
	t_token		**token;
	t_cmd		**cmds;
	int		last_exit;
	t_token_type	*expect;
}	t_parser_intern;

/* ===================== Helpers ===================== */

// Handle word tokens (commands/arguments)
static t_cmd	*handle_command_token(t_cmd *current, t_token *token)
{
	if (!token || !current)
		return (NULL);
	if (!add_args_cmd(current, token->value))
		return (NULL);
	return (current);
}

// Handle pipe tokens
static t_cmd	*handle_pipe_token(t_cmd *current, t_cmd **cmds)
{
	if (!current || !current->argv || !current->argv[0])
	{
		free_cmds(*cmds);
		return (NULL);
	}
	current = handle_pipe(current);
	if (!current)
		free_cmds(*cmds);
	return (current);
}

// Handle redirections and heredocs
static int	handle_redirection(t_cmd *current, t_token **token, int last_exit)
{
	if (!current || !token || !*token)
		return (-1);
	if ((*token)->type == TOKEN_REDIR_IN)
		return (handle_redir_in(current, token));
	if ((*token)->type == TOKEN_REDIR_OUT)
		return (handle_redir_out(current, token));
	if ((*token)->type == TOKEN_REDIR_OUT_APPEND)
		return (handle_redir_out_append(current, token));
	if ((*token)->type == TOKEN_HEREDOC)
		return (handle_heredoc(current, token, last_exit));
	return (0);
}

// Dispatch token to correct handler THE " BRAIN "
static t_cmd *handle_token(t_cmd *current, t_parser_intern *tmp)
{
	if (!*(tmp->token))
		return (current);

	if ((*(tmp->token))->type == TOKEN_WORD)
	{
		if (*(tmp->expect) != TOKEN_NONE)
		{
			*(tmp->expect) = TOKEN_NONE;
			*(tmp->token) = (*(tmp->token))->next;
			return (current);
		}
		current = handle_command_token(current, *(tmp->token));
		*(tmp->token) = (*(tmp->token))->next;
	}
	else if ((*(tmp->token))->type == TOKEN_PIPE)
	{
		current = handle_pipe_token(current, tmp->cmds);
		*(tmp->token) = (*(tmp->token))->next;
	}
	else if ((*(tmp->token))->type == TOKEN_REDIR_IN
		|| (*(tmp->token))->type == TOKEN_REDIR_OUT
		|| (*(tmp->token))->type == TOKEN_REDIR_OUT_APPEND
		|| (*(tmp->token))->type == TOKEN_HEREDOC)
	{
		*(tmp->expect) = (*(tmp->token))->type;
		if (handle_redirection(current, tmp->token, tmp->last_exit) == -1)
		{
			free_cmds(*(tmp->cmds));
			return (NULL);
		}
	}

	return (current);
}

/* ===================== Parser ===================== */

t_cmd *parser(t_token *tokens, char **argv, int last_exit)
{
    t_cmd           *cmds;
    t_cmd           *current;
    t_token_type    expect;
    t_parser_intern tmp;

    (void)argv;
    cmds = new_cmd();
    if (!tokens || !cmds)
        return (NULL);

    current = cmds;
    expect = TOKEN_NONE; // tracks if next word is a redirection target

    // initialize the struct
    tmp.token = &tokens;
    tmp.cmds = &cmds;
    tmp.last_exit = last_exit;
    tmp.expect = &expect;

    while (tokens)
    {
        current = handle_token(current, &tmp);
        if (!current)
            return (NULL);
    }

    if (!cmds->argv || !cmds->argv[0])
    {
        free_cmds(cmds);
        return (NULL);
    }

    return (cmds);
}
