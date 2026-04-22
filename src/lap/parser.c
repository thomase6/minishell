/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:18 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/22 09:13:15 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

static t_cmd	*handle_command_token(t_cmd *current, t_token **token)
{
	if (!current || !token || !*token)
		return (NULL);
	while (*token && (*token)->type == TOKEN_WORD)
	{
		if ((*token)->has_space_before || !current->argv)
		{
			if (!add_args_cmd(current, (*token)->value))
				return (NULL);
		}
		else if (!join_last_arg(current, (*token)->value))
			return (NULL);
		*token = (*token)->next;
	}
	return (current);
}

static t_cmd	*handle_pipe_token(t_cmd *current,
					t_cmd **cmds, t_token **token)
{
	t_cmd	*next_cmd;

	if (!current->argv && !current->infile && !current->outfile
		&& !current->exec_redirs)
	{
		free_cmds(*cmds);
		return (NULL);
	}
	next_cmd = new_cmd();
	if (!next_cmd)
	{
		free_cmds(*cmds);
		return (NULL);
	}
	current->next = next_cmd;
	*token = (*token)->next;
	return (next_cmd);
}

static int	handle_redirection(t_cmd *current, t_token **token, t_shell *shell)
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
		return (handle_heredoc(current, token, shell));
	return (0);
}

static t_cmd	*handle_token(t_cmd *current, t_parser_intern *tmp)
{
	if (!*(tmp->token))
		return (current);
	if ((*(tmp->token))->type == TOKEN_WORD)
		current = handle_command_token(current, tmp->token);
	else if ((*(tmp->token))->type == TOKEN_PIPE)
		current = handle_pipe_token(current, tmp->cmds, tmp->token);
	else if ((*(tmp->token))->type == TOKEN_REDIR_IN
		|| (*(tmp->token))->type == TOKEN_REDIR_OUT
		|| (*(tmp->token))->type == TOKEN_REDIR_OUT_APPEND
		|| (*(tmp->token))->type == TOKEN_HEREDOC)
	{
		*(tmp->expect) = (*(tmp->token))->type;
		if (handle_redirection(current, tmp->token, tmp->shell) == -1)
		{
			free_cmds(*(tmp->cmds));
			return (NULL);
		}
	}
	return (current);
}

/* ===================== Parser ===================== */

void	merge_adjacent_tokens(t_token *tokens)
{
	t_token	*tmp;
	t_token	*next;
	char	*joined;

	tmp = tokens;
	while (tmp && tmp->next)
	{
		next = tmp->next;
		if (tmp->type == TOKEN_WORD && next->type == TOKEN_WORD
			&& !next->has_space_before)
		{
			joined = ft_strjoin_lap(tmp->value, next->value);
			free(tmp->value);
			tmp->value = joined;
			tmp->next = next->next;
			free(next->value);
			free(next);
			continue ;
		}
		tmp = tmp->next;
	}
}

t_cmd	*parser(t_token *tokens, t_shell *shell)
{
	t_cmd			*cmds;
	t_cmd			*current;
	t_token_type	expect;
	t_parser_intern	tmp;

	merge_adjacent_tokens(tokens);
	cmds = new_cmd();
	if (!tokens || !cmds)
		return (NULL);
	current = cmds;
	expect = TOKEN_NONE;
	tmp = (t_parser_intern){&tokens, &cmds, shell, &expect};
	while (tokens)
	{
		current = handle_token(current, &tmp);
		if (!current)
			return (NULL);
	}
	if (!cmds->argv && !cmds->infile && !cmds->outfile && !cmds->exec_redirs)
	{
		free_cmds(cmds);
		return (NULL);
	}
	return (cmds);
}
